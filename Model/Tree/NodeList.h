#ifndef NODELIST_H
#define NODELIST_H
#include<QAbstractListModel>
#include"TreeNode.h"
#include"LeafNode.h"

class NodeList : public QAbstractListModel{
private:
  QList<TreeNode*> results;
public:
  NodeList(const QString& q): query(q){};
  ~NodeList();
  QString query;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  void appendResult(TreeNode* node);
  TreeNode* getNode(const QModelIndex& index) const;
};

#endif