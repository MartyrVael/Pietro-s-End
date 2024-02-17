#ifndef LEAFNODE_H
#define LEAFNODE_H
#include"TreeNode.h"
#include"../Sensor/BaseSensor.h"
#include"../Observer.h"
#include"../Subject.h"

class Tree;

class LeafNode : public TreeNode, public Observer, public Subject{
  friend class Tree;
private:
  LeafNode(BaseSensor* s, TreeNode* p =nullptr);
  BaseSensor* const sensor;
  virtual ~LeafNode();
  virtual bool isLeaf() const override;
  virtual int childCount() const override;
  QVariant getData(int column) const;
  virtual bool setName(const QString& n) override;
  virtual void observerUpdate() override;
};

#endif