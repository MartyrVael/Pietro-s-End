#include"TreeNode.h"

TreeNode::~TreeNode(){
  for(TreeNode* c : children){
    delete c;
  }
}

int TreeNode::row() const{
  if(parent)
    return parent->children.indexOf(const_cast<TreeNode*>(this));
  return 0;
}

bool TreeNode::isLeaf() const{
  return false;
}

int TreeNode::childCount() const{
  return children.count();
}

TreeNode* TreeNode::getParent(){
  return parent;
}

TreeNode* TreeNode::getChild(int row){
  if(!isLeaf() && row < children.size())
    return children[row];
  return nullptr;
}

QVariant TreeNode::getData(int column) const{
  if(column == 0)
    return name;
  return QVariant();
};

bool TreeNode::setName(const QString& n){
  name = n;
  return true;
}

TreeNode* TreeNode::appendChild(TreeNode* child){
  children.append(child);
  child->parent = this;
  return child;
}

bool TreeNode::removeChildren(int pos, int count){
  if(!isLeaf()){
    if(pos < 0 || pos+count > children.size())
      return false;
    for(int i=0; i<count; ++i)
      delete children.takeAt(pos);
    return true;
  }
  return false;
}

QString TreeNode::getName() const{
  return name;
}