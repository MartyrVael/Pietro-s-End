#include"Tree.h"
#include"../Sensor/SensorFactory.h"
#include"../Sensor/TypeSensorVisitor.h"

Tree* Tree::instance =nullptr;


Tree::~Tree(){
  removeRows(0, root->childCount(), QModelIndex());
  removeColumns(0, 3, QModelIndex());
}

TreeNode* Tree::getNode(const QModelIndex& index) const{
  if(index.isValid()){
    TreeNode* indexNode = static_cast<TreeNode*>(index.internalPointer());
    if(indexNode)
      return indexNode;
  }
  return root;
}

QModelIndex Tree::getIndex(TreeNode* node) const{
  if(node == nullptr)
    return QModelIndex();
  int row;
  if(node->getParent() == nullptr)
    row = root->children.indexOf(node);
  else
    row = node->row();
  return index(row, 0, getIndex(node->getParent()));
}

void Tree::populateSearch(TreeNode* node, NodeList* results) const{
  if(node == nullptr)
    return;
  if(node->name.contains(results->query, Qt::CaseInsensitive))
    results->appendResult(node);
  if(!node->isLeaf()){
    for(TreeNode* const n : node->children){
      populateSearch(n, results);
    }
  }
}

Tree* Tree::tree(){
  if(instance == nullptr)
    instance = new Tree();
  return instance;
}

QModelIndex Tree::index(int row, int column, const QModelIndex& parent) const{
  if(parent.isValid() && parent.column() != 0)
    return QModelIndex();
  TreeNode* parentNode = getNode(parent);
  if(!parentNode)
    return QModelIndex();
  TreeNode* childNode = parentNode->getChild(row);
  if(childNode)
    return createIndex(row, column, childNode);
  return QModelIndex();
}

QModelIndex Tree::parent(const QModelIndex& index) const{
  if(!index.isValid())
    return QModelIndex();
  TreeNode* indexNode = getNode(index);
  TreeNode* parentNode = nullptr;
  if(indexNode)
    parentNode = indexNode->getParent();
  if(parentNode == root || !parentNode)
    return QModelIndex();
  return createIndex(parentNode->row(), 0, parentNode);
}

bool Tree::leaf(const QModelIndex& index) const{
  return leaf(getNode(index));
}

bool Tree::leaf(TreeNode* node) const{
  return node->isLeaf();
}

int Tree::rowCount(const QModelIndex& parent) const{
  if(parent.isValid() && parent.column() > 0)
    return 0;
  const TreeNode* parentNode = getNode(parent);
  if(parentNode)
    return parentNode->childCount();
  return 0;
}

int Tree::columnCount(const QModelIndex& parent) const{
  Q_UNUSED(parent);
  return 3;
}

QVariant Tree::data(const QModelIndex& index, int role) const{
  if(!index.isValid())
    return QVariant();
  if(role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();
  TreeNode* indexNode = getNode(index);
  return indexNode->getData(index.column());
}

QVariant Tree::headerData(int section, Qt::Orientation orientation, int role) const{
  if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
    return QVariant();
  switch(section){
    case 0:
      return QString("Name");
      break;
    case 1:
      return QString("ID");
      break;
    case 2:
      return QString("Type");
      break;
    default:
      return QVariant();
      break;
  }
}

Qt::ItemFlags Tree::flags(const QModelIndex& index) const{
  if(!index.isValid())
    return Qt::NoItemFlags;
  Qt::ItemFlags result;
  if(index.column() == 0)
    result.setFlag(Qt::ItemIsEditable);
  if(getNode(index)->isLeaf())
    result.setFlag(Qt::ItemNeverHasChildren);
  result.setFlag(Qt::ItemIsEnabled);
  result.setFlag(Qt::ItemIsSelectable);
  return result;
}

bool Tree::setData(const QModelIndex& index, const QVariant& value, int role){
  if(role != Qt::EditRole || index.column() !=0)
    return false;
  TreeNode* indexNode = getNode(index);
  bool result = indexNode->setName(value.toString());
  if(result){
    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
  }
  return result;
}

bool Tree::removeRows(int position, int count, const QModelIndex& parent){
  TreeNode* parentNode = getNode(parent);
  if(!parentNode)
    return false;
  beginRemoveRows(parent, position, position+count-1);
  const bool success = parentNode->removeChildren(position, count);
  endRemoveRows();
  notify();
  return success;
}

bool Tree::appendNode(const QString& name, const QModelIndex& parent){
  TreeNode* parentNode = getNode(parent);
  if(!parentNode->isLeaf()){
    beginInsertRows(parent, parentNode->childCount(), parentNode->childCount());
    TreeNode* child = parentNode->appendChild(new TreeNode(name, parentNode));
    if(parentNode == root)
      child->parent = nullptr;
    endInsertRows();
    notify();
    return child;
  }
  return false;
}

bool Tree::appendSensor(BaseSensor* sensor, const QModelIndex& parent){
  TreeNode* parentNode = getNode(parent);
  if(!parentNode->isLeaf() && sensor != nullptr){
    beginInsertRows(parent, parentNode->childCount(), parentNode->childCount());
    LeafNode* leaf = new LeafNode(sensor, parentNode);
    leaf->attach(this);
    TreeNode* child = parentNode->appendChild(leaf);
    if(parentNode == root)
      child->parent = nullptr;
    endInsertRows();
    notify();
    return child;
  }
  return false;
}

bool Tree::removeNode(const QModelIndex& index){
  bool result = removeRows(index.row(), 1, index.parent());
  return result;
}

BaseSensor* Tree::getSensor(const QModelIndex& index){
  TreeNode* index_node = getNode(index);
  if(index_node->isLeaf())
    return dynamic_cast<LeafNode*>(index_node)->sensor;
  return nullptr;
}

BaseSensor* Tree::getSensor(TreeNode* node){
  if(node != nullptr && node->isLeaf())
    return dynamic_cast<LeafNode*>(node)->sensor;
  return nullptr; 
}

NodeList* Tree::search(const QString& query) const{
  NodeList* results = new NodeList(query);
  //Cannot return root, iterating on its children
  for(TreeNode* const n : root->children){
    populateSearch(n, results);
  }
  return results;
}

void Tree::resetTree(){
  removeRows(0, root->children.count(), QModelIndex());
}

void Tree::jsonToNode(const QJsonObject& json, TreeNode* parent){
  if(!(json.contains("name") && json["name"].isString()))
    return;
  if(json.contains("type") && json["type"].isString() && json.contains("id") && json["id"].isDouble()){
    jsonToLeafNode(json, parent);
  }
  if(json.contains("children") && json["children"].isArray()){
    jsonToTreeNode(json, parent);
  }
};

void Tree::jsonToTreeNode(const QJsonObject& json, TreeNode* parent){
  QString name = json["name"].toString();
  QJsonArray children_array = json["children"].toArray();
  TreeNode* node;
  if(parent == nullptr){
    node = root->appendChild(new TreeNode(name));
    node->parent = nullptr;
  }
  else{
    node = parent->appendChild(new TreeNode(name));
  }
  for(QJsonValue j : children_array){
    if(j.isObject())
      jsonToNode(j.toObject(), node);
  }
}

void Tree::jsonToLeafNode(const QJsonObject& json, TreeNode* parent){
  QString name = json["name"].toString();
  QString type = json["type"].toString();
  int id = json["id"].toDouble();
  bool has_minmax = (json.contains("min") && json["min"].isDouble() && json.contains("max") && json["max"].isDouble());
  TreeNode* node;
  if(parent == nullptr){
    node = root->appendChild(new LeafNode(SensorFactory::loadSensor(name, id, type)));
    node->parent = nullptr;
  }
  else
    node = parent->appendChild(new LeafNode(SensorFactory::loadSensor(name, id, type)));
  LeafNode* leaf = dynamic_cast<LeafNode*>(node);
  leaf->attach(this);
  if(has_minmax)
    leaf->sensor->setMinMax(json["min"].toDouble(), json["max"].toDouble());
}

void Tree::fromJson(const QJsonObject& json){
  if(json.contains("name") && json["name"].toString() == "root"){
    resetTree();
    if(json.contains("children") && json["children"].isArray()){
      QJsonArray root_children = json["children"].toArray();
      for(QJsonValue j : root_children){
        if(j.isObject())
          jsonToNode(j.toObject(), nullptr);
      }
    }
  }
}

QJsonObject Tree::nodeToJson(TreeNode* node) const{
  if(node == nullptr)
    return QJsonObject();
  if(node->isLeaf())
    return leafNodeToJson(node);
  return treeNodeToJson(node);
}

QJsonObject Tree::treeNodeToJson(TreeNode* node) const{
  QJsonObject json;
  QJsonArray children_array;
  json.insert("name", node->name);
  for(TreeNode* n : node->children){
    children_array.append(nodeToJson(n));
  }
  json.insert("children", children_array);
  return json;
}

QJsonObject Tree::leafNodeToJson(TreeNode* node) const{
  LeafNode* leaf = dynamic_cast<LeafNode*>(node);
  QJsonObject json;
  TypeSensorVisitor v;
  leaf->sensor->accept(v);
  json.insert("name", leaf->sensor->getName());
  json.insert("type", v.getType());
  json.insert("id", leaf->sensor->getId());
  json.insert("min", leaf->sensor->getMin());
  json.insert("max", leaf->sensor->getMax());
  return json;
}

QJsonObject Tree::toJson() const{
  return treeNodeToJson(root);
}

void Tree::importSection(const QJsonObject& json, TreeNode* parent, QMap<int, int>* changed_ids){
  importNode(json, parent, changed_ids);
}

QJsonObject Tree::exportSection(TreeNode* head, QList<int>* ids) const{
  if(head != nullptr)
    return exportNode(head, ids);
  return exportNode(root, ids);
}

void Tree::importNode(const QJsonObject& json, TreeNode* parent, QMap<int,int>* changed_ids){
  if(!(json.contains("name") && json["name"].isString()))
    return;
  if(json.contains("type") && json["type"].isString() && json.contains("id") && json["id"].isDouble()){
    importLeafNode(json, parent, changed_ids);
  }
  if(json.contains("children") && json["children"].isArray()){
    importTreeNode(json, parent, changed_ids);
  }
}

void Tree::importTreeNode(const QJsonObject& json, TreeNode* parent, QMap<int,int>* changed_ids){
  QString name = json["name"].toString();
  QJsonArray children_array = json["children"].toArray();
  TreeNode* node = new TreeNode(name);
  if(parent == nullptr){
    root->appendChild(node);
    node->parent = nullptr;
  }
  else{
    node = parent->appendChild(node);
  }
  for(QJsonValue j : children_array){
    if(j.isObject())
      importNode(j.toObject(), node, changed_ids);
  }
}

void Tree::importLeafNode(const QJsonObject& json, TreeNode* parent, QMap<int,int>* changed_ids){
  QString name = json["name"].toString();
  QString type = json["type"].toString();
  BaseSensor* sensor = SensorFactory::createSensor(name, type);
  int old_id = json["id"].toDouble();
  bool has_minmax = (json.contains("min") && json["min"].isDouble() && json.contains("max") && json["max"].isDouble());
  TreeNode* node;
  changed_ids->insert(old_id, sensor->getId());
  if(parent == nullptr){
    node = root->appendChild(new LeafNode(sensor));
    node->parent = nullptr;
  }
  else
    node = parent->appendChild(new LeafNode(sensor));
  LeafNode* leaf = dynamic_cast<LeafNode*>(node);
  leaf->attach(this);
  if(has_minmax)
    leaf->sensor->setMinMax(json["min"].toDouble(), json["max"].toDouble());
}

QJsonObject Tree::exportNode(TreeNode* node, QList<int>* ids) const{
  if(node == nullptr)
    return QJsonObject();
  if(node->isLeaf())
    return exportLeafNode(node, ids);
  return exportTreeNode(node, ids);
};

QJsonObject Tree::exportTreeNode(TreeNode* node, QList<int>* ids) const{
  QJsonObject json;
  QJsonArray children_array;
  json.insert("name", node->name);
  for(TreeNode* n : node->children){
    children_array.append(exportNode(n, ids));
  }
  json.insert("children", children_array);
  return json;
};

QJsonObject Tree::exportLeafNode(TreeNode* node, QList<int>* ids) const{
  LeafNode* leaf = dynamic_cast<LeafNode*>(node);
  QJsonObject json;
  TypeSensorVisitor v;
  leaf->sensor->accept(v);
  json.insert("name", leaf->sensor->getName());
  json.insert("type", v.getType());
  int id = leaf->sensor->getId();
  ids->append(id);
  json.insert("id", id);
  json.insert("min", leaf->sensor->getMin());
  json.insert("max", leaf->sensor->getMax());
  return json;
};

void Tree::observerUpdate(){
  notify();
}