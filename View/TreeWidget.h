#ifndef TREEWIDGET_H
#define TREEWIDGET_H
#include<QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include<QMessageBox>
#include<QInputDialog>
#include<QLineEdit>
#include<QListView>
#include"DTreeView.h"
#include"../Model/Tree/Tree.h"
#include"../Model/Sensor/SensorFactory.h"
#include"../Model/Tree/NodeList.h"

class TreeWidget : public QWidget{
  Q_OBJECT
private:
  Tree* tree_model;
  QPushButton* create_node;
  QPushButton* create_sensor;
  QPushButton* remove_node;
  QTreeView* tree_view;

public:
  explicit TreeWidget(Tree* t, QWidget* parent =nullptr);
  TreeNode* selected() const;
signals:
  void leafSelected(BaseSensor* sensor);
  void leafDeselected();

public slots:
  void createNode();
  void createSensor();
  void removeNode();
  void selectNode(TreeNode* node);
  void handleSelection(const QModelIndex& current, const QModelIndex& previous);
};

#endif