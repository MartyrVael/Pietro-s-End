#include"ReadingList.h"
#include<iterator>
#include"TypeReadingVisitor.h"

ReadingList* ReadingList::instance = nullptr;

ReadingList::~ReadingList(){
  for(Reading* r : map){
    delete r;
  }
}

int ReadingList::getKey(const QModelIndex& index) const{
  auto it = map.begin();
  for(int i=0; i < index.row(); ++i){
    ++it;
  }
  return it.key();
}

Reading* ReadingList::getValue(const QModelIndex& index) const{
  auto it = map.begin();
  for(int i=0; i < index.row(); ++i){
    ++it;
  }
  return it.value();
}

ReadingList* ReadingList::readinglist(){
  if(instance == nullptr)
    instance = new ReadingList();
  return instance;
}

int ReadingList::rowCount(const QModelIndex& parent) const{
  Q_UNUSED(parent);
  return map.count();
}

int ReadingList::columnCount(const QModelIndex& parent) const{
  Q_UNUSED(parent);
  return 3;
}

QVariant ReadingList::data(const QModelIndex& index, int role) const{
  if(!index.isValid())
    return QVariant();
  if(role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();
  switch(index.column()){
    case 0:
      return getValue(index)->getName();
      break;
    case 1:
      return getKey(index);
      break;
    case 2:
      return getValue(index)->getSize();
      break;
    default:
      return QVariant();
      break;
  }
}

QVariant ReadingList::headerData(int section, Qt::Orientation orientation, int role) const{
  if(orientation != Qt::Orientation::Horizontal || role != Qt::DisplayRole)
    return QVariant();
  switch(section){
    case 0:
      return QString("Name");
      break;
    case 1:
      return QString("Sensor ID");
      break;
    case 2:
      return QString("# of Entries");
      break;
    default:
      return QVariant();
      break;
  }
}

Qt::ItemFlags ReadingList::flags(const QModelIndex& index) const{
  if(!index.isValid())
    return Qt::NoItemFlags;
  Qt::ItemFlags result;
  if(index.column() ==0)
    result.setFlag(Qt::ItemIsEditable);
  result.setFlag(Qt::ItemIsSelectable);
  result.setFlag(Qt::ItemIsEnabled);
  return result;
}

bool ReadingList::setData(const QModelIndex& index, const QVariant& value, int role){
  if(role != Qt::EditRole || index.column() != 0)
    return false;
  getValue(index)->setName(value.toString());
  emit dataChanged(index, index);
  return true;
  notify();
}

void ReadingList::addToTable(const QModelIndex& index) const{
  if(map.contains(getKey(index), getValue(index)))
    TableContainer::tablecontainer()->insertReading(getValue(index));
}

void ReadingList::insert(int k, Reading* r){
  r->attach(this);
  int position = std::distance(map.begin(), map.contains(k)? map.upperBound(k) : map.lowerBound(k));
  beginInsertRows(QModelIndex(), position, position);
  map.insert(k, r);
  endInsertRows();
  notify();
}

void ReadingList::remove(int k){
  if(!map.contains(k))
    return;
  int first = std::distance(map.begin(), map.lowerBound(k));
  beginRemoveRows(QModelIndex(), first, first + map.count(k) -1);
  for(Reading* it : map.values(k)){
    TableContainer::tablecontainer()->removeReading(it);
    delete it;
  }
  map.remove(k);
  endRemoveRows();
  notify();
}

void ReadingList::remove(Reading* r){
  auto it = map.find(map.key(r), r);
  int position = std::distance(map.begin(), it);
  beginRemoveRows(QModelIndex(), position, position);
  TableContainer::tablecontainer()->removeReading(r);
  delete r;
  map.erase(it);
  endRemoveRows();
  notify();
}

void ReadingList::remove(const QModelIndex& index){
  remove(getValue(index));
}

void ReadingList::resetList(){
  for(int k : map.keys())
    remove(k);
  notify();
}

QModelIndex ReadingList::find(int key, Reading* value) const{
  int pos = -1;
  if(map.contains(key, value)){
    pos = std::distance(map.begin(), map.find(key, value));
  }
  return (pos >= 0)? index(pos, 0, QModelIndex()) : QModelIndex();
}

Reading* ReadingList::reading(const QModelIndex& index) const{
  if(index.isValid())
    return getValue(index);
  return nullptr;
}

QJsonObject ReadingList::entryToJson(int key, Reading* value) const{
  QJsonObject json;
  QJsonArray values_array;
  json.insert("id", key);
  json.insert("name", value->getName());
  TypeReadingVisitor v;
  value->accept(v);
  json.insert("type", v.getType());
  for(int i =0; i < value->getSize(); i++){
    values_array.append(value->getValue(i));
  }
  json.insert("values", values_array);
  return json;
}

void ReadingList::jsonToEntry(const QJsonObject& json){
  if(json.contains("name") && json["name"].isString() &&
     json.contains("id") && json["id"].isDouble() &&
     json.contains("type") && json["type"].isString() &&
     json.contains("values") && json["values"].isArray()){
    int id = json["id"].toDouble();
    QString name = json["name"].toString();
    QString type = json["type"].toString();
    QJsonArray json_values = json["values"].toArray();
    QList<double>* values = new QList<double>();
    for(QJsonValue j : json_values){
      if(j.isDouble())
        values->append(j.toDouble());
    }
    insert(id, ReadingFactory::createReading(name, values, type));
  }
}

QJsonObject ReadingList::toJson(){
  QJsonObject json;
  QJsonArray reading_array;
  for(auto it = map.begin(); it != map.end(); it++){
    reading_array.append(entryToJson(it.key(), it.value()));
  }
  json.insert("readings", reading_array);
  return json;
}

void ReadingList::fromJson(const QJsonObject& json){
  if(json.contains("readings") && json["readings"].isArray()){
    resetList();
    QJsonArray readings_array = json["readings"].toArray();
    for(QJsonValue j : readings_array){
      if(j.isObject())
        jsonToEntry(j.toObject());
    }
  }
}

QJsonObject ReadingList::exportReadings(QList<int>* ids) const{
  QJsonObject json;
  QJsonArray reading_array;
  for(auto it = map.begin(); it != map.end(); it++){
    if(ids->contains(it.key()))
      reading_array.append(entryToJson(it.key(), it.value()));
  }
  json.insert("readings", reading_array);
  return json;
}

void ReadingList::importReadings(const QJsonObject& json, QMap<int, int>* changed_ids){
  if(json.contains("readings") && json["readings"].isArray()){
    QJsonArray readings_array = json["readings"].toArray();
    for(QJsonValue j : readings_array){
      if(j.isObject())
        importEntry(j.toObject(), changed_ids);
    }
  }
}

void ReadingList::importEntry(const QJsonObject& json, QMap<int, int>* changed_ids){
  if( json.contains("name") && json["name"].isString() &&
      json.contains("id") && json["id"].isDouble() &&
      json.contains("type") && json["type"].isString() &&
      json.contains("values") && json["values"].isArray()){
    int id = changed_ids->find(json["id"].toDouble()).value();
    QString name = json["name"].toString();
    QString type = json["type"].toString();
    QJsonArray json_values = json["values"].toArray();
    QList<double>* values = new QList<double>();
    for(QJsonValue j : json_values){
      if(j.isDouble())
        values->append(j.toDouble());
    }
    insert(id, ReadingFactory::createReading(name, values, type));
  }
}

void ReadingList::observerUpdate(){
  notify();
}