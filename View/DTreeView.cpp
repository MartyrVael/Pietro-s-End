#include"DTreeView.h"

void DTreeView::setModel(Tree* tree){
  tree->attach(this);
  QTreeView::setModel(tree);
}

void DTreeView::mousePressEvent(QMouseEvent* event){
  QModelIndex item = indexAt(event->pos());
  if(item.isValid())
    QTreeView::mousePressEvent(event);
  else{
    clearSelection();
    selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
  }
}

void DTreeView::observerUpdate(){
  QWidget::update();
}