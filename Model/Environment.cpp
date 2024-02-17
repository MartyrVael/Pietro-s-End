#include"Environment.h"

Environment* Environment::instance = nullptr;

Environment::Environment(){
  tree_instance = Tree::tree();
  readinglist_instance = ReadingList::readinglist();
  tablecontainer_instance = TableContainer::tablecontainer();
}

Environment::~Environment(){
  delete tree_instance;
  delete readinglist_instance;
  delete tablecontainer_instance;
}

Environment* Environment::environment(){
  if(instance == nullptr)
    instance = new Environment();
  return instance;
}

Tree* Environment::tree() const{
  return tree_instance;
}

ReadingList* Environment::readinglist() const{
  return readinglist_instance;
}

TableContainer* Environment::tablecontainer() const{
  return tablecontainer_instance;
}

QJsonObject Environment::toJson() const{
  QJsonObject json;
  json["tree"] = tree_instance->toJson();
  json["readinglist"] = readinglist_instance->toJson();
  return json;
}

bool Environment::fromJson(const QJsonObject& json){
  if( json.contains("tree") && json["tree"].isObject() &&
      json.contains("readinglist") && json["readinglist"].isObject()){
    tree_instance->fromJson(json["tree"].toObject());
    readinglist_instance->fromJson(json["readinglist"].toObject());
    return true;
  }
  if(json.contains("section")){
    qWarning("Cannot load section as tree");
    return false;
  }
  qWarning("Invalid json file");
  return false;
}

QJsonObject Environment::exportSection(TreeNode* node) const{
  QList<int>* ids = new QList<int>();
  QJsonObject json;
  json.insert("section", tree_instance->exportSection(node, ids));
  json.insert("readinglist", readinglist_instance->exportReadings(ids));
  delete ids;
  return json;
}

bool Environment::importSection(const QJsonObject& json, TreeNode* parent){
  if( json.contains("section") && json["section"].isObject() &&
      json.contains("readinglist") && json["readinglist"].isObject()){
    QMap<int, int>* changed_ids = new QMap<int, int>();
    tree_instance->importSection(json["section"].toObject(), parent, changed_ids);
    readinglist_instance->importReadings(json["readinglist"].toObject(), changed_ids);
    delete changed_ids;
    return true;
  }
  else if(json.contains("tree")){
    qWarning("Cannot load environment as section");
  }
  else{
    qWarning("Invalid JSON file");
  }
  return false;
}

bool Environment::saveEnvironment(const QString& path) const{
  QFile save_file(path);
  if(!save_file.open(QIODevice::WriteOnly)){
    qWarning("Could not open file");
    return false;
  }
  QJsonObject environment(toJson());
  save_file.write(QJsonDocument(environment).toJson());
  return true;
}

bool Environment::loadEnvironment(const QString& path){
  QFile load_file(path);
  if(!load_file.open(QIODevice::ReadOnly)){
    qWarning("Could not open save file");
    return false;
  }
  QByteArray save_data = load_file.readAll();
  QJsonDocument jsondoc = QJsonDocument::fromJson(save_data);
  return fromJson(jsondoc.object());
}

bool Environment::saveSection(TreeNode* head, const QString& path) const{
  QFile save_file(path);
  if(!save_file.open(QIODevice::WriteOnly)){
    qWarning("Could not open file");
    return false;
  }
  QJsonObject environment(exportSection(head));
  save_file.write(QJsonDocument(environment).toJson());
  return true;
}

bool Environment::loadSection(TreeNode* parent, const QString& path){
  QFile load_file(path);
  if(!load_file.open(QIODevice::ReadOnly)){
    qWarning("Could not open save file");
    return false;
  }
  QByteArray save_data = load_file.readAll();
  QJsonDocument jsondoc = QJsonDocument::fromJson(save_data);
  return importSection(jsondoc.object(), parent);
}