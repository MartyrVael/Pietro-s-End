#include"ReadingTable.h"

ReadingTable::~ReadingTable(){
  for(Reading* r : table){
    r->detach(this);
  }
};

Reading* ReadingTable::getReading(const QModelIndex& index) const{
  if(!index.isValid())
    return nullptr;
  Reading* reading = static_cast<Reading*>(index.internalPointer());
  if(reading)
    return reading;
  return nullptr;
}

QModelIndex ReadingTable::getIndex(Reading* reading) const{
  int row = table.indexOf(reading);
  return index(row, 0, QModelIndex());
}

QModelIndex ReadingTable::index(int row, int column, const QModelIndex& parent) const{
  if(column != 0 || row < 0)
    return QModelIndex();
  if(!parent.isValid()){
    (row < table.count())? createIndex(row, column, table.at(row)) : QModelIndex();
  }
  if(parent.isValid()){
    createIndex(row, column, table.at(row));
  }
}

QModelIndex ReadingTable::parent(const QModelIndex& index) const{
  if(!index.isValid())
    return QModelIndex();
  return getIndex(getReading(index));
}

int ReadingTable::rowCount(const QModelIndex& parent) const{
  if(parent == QModelIndex())
    return table.count();
  return getReading(parent)->getSize();
}

int ReadingTable::columnCount(const QModelIndex& parent) const{
  Q_UNUSED(parent);
  return 1;
}

QVariant ReadingTable::data(const QModelIndex& index, int role) const{
  if(role != Qt::DisplayRole || !index.isValid())
    return QVariant();
  if(index.parent() == QModelIndex())
    return getReading(index)->getName();
  if(index.parent() != QModelIndex())
    return getReading(index)->getValue(index.row());
}

bool ReadingTable::hasChildren(const QModelIndex& parent) const{
  if(!parent.isValid())
    return true;
  if(!parent.parent().isValid())
    return true;
  else
    return false;
}

void ReadingTable::append(Reading* reading){
  if(table.contains(reading) || reading == nullptr)
    return;
  reading->attach(this);
  beginInsertRows(QModelIndex(), table.size(), table.size());
  beginInsertRows(index(table.count(), 0, QModelIndex()), 0, reading->getSize()-1);
  table.append(reading);
  endInsertRows();
  endInsertRows();

  notify();
}

void ReadingTable::remove(Reading* reading){
  beginRemoveRows(QModelIndex(), table.indexOf(reading), table.indexOf(reading));
  beginRemoveRows(index(table.indexOf(reading), 0, QModelIndex()), 0, reading->getSize()-1);
  table.removeAll(reading);
  endRemoveRows();
  endRemoveRows();
  reading->detach(this);
  notify();
}

void ReadingTable::remove(const QModelIndex& index){
  if(index.parent().isValid())
    return;
  remove(getReading(index));
}

bool ReadingTable::contains(Reading* reading) const{
  return table.contains(reading);
}

int ReadingTable::row(Reading* r) const{
  if(contains(r))
    return table.indexOf(r);
  return table.size();
}

void ReadingTable::observerUpdate(){
  notify();
}


const QList<Reading*> ReadingTable::getTable() const{
  return table;
}