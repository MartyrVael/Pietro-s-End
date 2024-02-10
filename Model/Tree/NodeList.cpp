#include"NodeList.h"

TreeNode* NodeList::getNode(const QModelIndex& index) const{
  if(index.isValid()){
    TreeNode* indexNode = static_cast<TreeNode*>(index.internalPointer());
    if(indexNode)
      return indexNode;
  }
  return nullptr;
}

QVariant NodeList::data(const QModelIndex& index, int role) const{
  if(!index.isValid() || role != Qt::DisplayRole)
    return QVariant();
  return results.at(index.row())->getName();
}

int NodeList::rowCount(const QModelIndex& parent) const{
  Q_UNUSED(parent);
  return results.count();
}

void NodeList::appendResult(TreeNode* node){
  beginInsertRows(QModelIndex(), results.size(), results.size());
  results.append(node);
  endInsertRows();
}