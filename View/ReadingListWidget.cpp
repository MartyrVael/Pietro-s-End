#include"ReadingListWidget.h"

ReadingListWidget::ReadingListWidget(ReadingList* rl, QWidget* parent): QWidget(parent), readinglist(rl){
  table_view = new QTableView();
  table_view->setModel(readinglist);
  delete_reading = new QPushButton("Delete Reading");
  add_to_display = new QPushButton("Add to display");

  QVBoxLayout* vbox = new QVBoxLayout(this);
  QHBoxLayout* buttonbox = new QHBoxLayout();
  vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  buttonbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  buttonbox->addWidget(add_to_display);
  buttonbox->addWidget(delete_reading);
  buttonbox->addStretch();
  vbox->addLayout(buttonbox);
  vbox->addWidget(table_view);
  vbox->addStretch();

  connect(delete_reading, &QPushButton::clicked, this, &ReadingListWidget::deleteReadingClicked);
  connect(add_to_display, &QPushButton::clicked, this, &ReadingListWidget::addClicked);
}

void ReadingListWidget::deleteReadingClicked(){
  QModelIndex index = table_view->selectionModel()->currentIndex();
  if(!index.isValid()){
    QMessageBox::StandardButton warn = QMessageBox::warning(this, "Invalid index", "Please select a Reading", QMessageBox::Ok);
    return;
  }
  readinglist->remove(index);
}

void ReadingListWidget::findReading(int id, Reading* reading){
  table_view->selectionModel()->select(readinglist->find(id, reading), QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Current);
}

void ReadingListWidget::addClicked(){
  QModelIndex index = table_view->selectionModel()->currentIndex();
  if(index.isValid()){
    readinglist->addToTable(index);
    emit displayReading(readinglist->reading(index));
  }
}

void ReadingListWidget::observerUpdate(){
  QWidget::update();
}