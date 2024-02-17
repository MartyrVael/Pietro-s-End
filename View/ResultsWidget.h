#ifndef RESULTSWIDGET_H
#define RESULTSWIDGET_H
#include<QVBoxLayout>
#include<QStackedLayout>
#include<QListView>
#include<QLabel>
#include<QPushButton>
#include"../Model/Tree/NodeList.h"


class ResultsWidget : public QWidget{
  Q_OBJECT
private:
  NodeList* result_list;
  QListView* list_view;
  QLabel* no_results;
  QPushButton* close_widget;
  QWidget* empty_list;
  QWidget* widget_list;
  QStackedLayout* stack;
  QPushButton* go_button;
  
public:
  ResultsWidget(QWidget* parent = nullptr);
  void addList(NodeList* list);
  void removeList();

public slots:
  void nodeSelected();
  void closeButtonPressed();

signals:
  void selectedNode(TreeNode* node);
  void closePressed();
};

#endif