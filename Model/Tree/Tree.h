#ifndef TREE_H
#define TREE_H
#include<QList>
#include<QAbstractItemModel>
#include<QString>
#include<QMap>
#include<QJsonObject>
#include<QJsonArray>
#include"../Observer.h"
#include"../Subject.h"
#include"TreeNode.h"
#include"LeafNode.h"
#include"NodeList.h"
#include"../Sensor/BaseSensor.h"

class Tree : public QAbstractItemModel, public Observer, public Subject{
  Q_OBJECT
  
private:
  static Tree* instance;
  explicit Tree(): root(new TreeNode("root")){};
  TreeNode* root;
  void populateSearch(TreeNode* node, NodeList* results) const;

  void jsonToNode(const QJsonObject& json, TreeNode* parent);
  void jsonToLeafNode(const QJsonObject& json, TreeNode* parent);
  void jsonToTreeNode(const QJsonObject& json, TreeNode* parent);
  QJsonObject nodeToJson(TreeNode* node) const;
  QJsonObject leafNodeToJson(TreeNode* node) const;
  QJsonObject treeNodeToJson(TreeNode* node) const;
  void importNode(const QJsonObject& json, TreeNode* parent, QMap<int,int>* changed_ids);
  void importTreeNode(const QJsonObject& json, TreeNode* parent, QMap<int, int>* changed_ids);
  void importLeafNode(const QJsonObject& json, TreeNode* parent, QMap<int, int>* changed_ids);
  QJsonObject exportNode(TreeNode* node, QList<int>* ids) const;
  QJsonObject exportTreeNode(TreeNode* node, QList<int>* ids) const;
  QJsonObject exportLeafNode(TreeNode* node, QList<int>* ids) const;
public:
  ~Tree();
  static Tree* tree();
  TreeNode* getNode(const QModelIndex& index) const;
  QModelIndex index(int row, int column, const QModelIndex& parent =QModelIndex()) const override;
  QModelIndex parent(const QModelIndex& index) const override;
  bool leaf(const QModelIndex& index) const;
  bool leaf(TreeNode* node) const;
  int rowCount(const QModelIndex& parent =QModelIndex()) const override;
  int columnCount(const QModelIndex& parent =QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role =Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;
  bool setData(const QModelIndex& index, const QVariant& value, int role =Qt::EditRole) override;
  bool removeRows(int position, int rows, const QModelIndex& parent =QModelIndex()) override;
  bool appendNode(const QString& name, const QModelIndex& parent =QModelIndex());
  bool appendSensor(BaseSensor* sensor, const QModelIndex& parent =QModelIndex());
  bool removeNode(const QModelIndex& index =QModelIndex());
  QModelIndex getIndex(TreeNode* node) const;
  BaseSensor* getSensor(const QModelIndex& index);
  BaseSensor* getSensor(TreeNode* t);
  NodeList* search(const QString& query) const;
  void resetTree();
  void fromJson(const QJsonObject& json);
  QJsonObject toJson() const;
  void importSection(const QJsonObject& json, TreeNode* parent, QMap<int, int>* changed_ids);
  QJsonObject exportSection(TreeNode* head, QList<int>* ids) const;
  virtual void observerUpdate() override;
};

#endif