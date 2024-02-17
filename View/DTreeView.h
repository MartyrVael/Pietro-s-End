#ifndef DTREEVIEW_H
#define DTREEVIEW_H
#include<QTreeView>
#include<QMouseEvent>
#include"../Model/Observer.h"
#include"../Model/Tree/Tree.h"
class DTreeView : public QTreeView, public Observer{
public:
  virtual void setModel(Tree* tree);
  DTreeView(QWidget* parent =nullptr): QTreeView(parent){};
  virtual ~DTreeView(){};
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void observerUpdate() override;
};

#endif