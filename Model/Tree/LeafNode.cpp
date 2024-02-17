#include"LeafNode.h"
#include"../Sensor/TypeSensorVisitor.h"

LeafNode::LeafNode(BaseSensor* s, TreeNode* p): TreeNode(s->getName(), p), sensor(s){
  s->attach(this);
};

LeafNode::~LeafNode(){
  delete sensor;
}

bool LeafNode::isLeaf() const{
  return true;
}

int LeafNode::childCount() const{
  return 0;
}

QVariant LeafNode::getData(int column) const{
  TypeSensorVisitor t; //NOTE: Cannot be initialized within a switch clause, so has to be done before
  switch(column){
    case 0:
      return name;
      break;
    case 1:
      return sensor->getId();
      break;
    case 2:
      sensor->accept(t);
      return t.getType();
      break;
    default:
      return QVariant();
      break;
  }
}

bool LeafNode::setName(const QString& n){
  sensor->setName(n);
  name = n;
  return true;
}

void LeafNode::observerUpdate(){
  name = sensor->getName();
  notify();
}