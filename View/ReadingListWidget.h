#ifndef READINGLISTWIDGET_H
#define READINGLISTWIDGET_H
#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QTableView>
#include<QPushButton>
#include<QMessageBox>
#include"../Model/Observer.h"
#include"Model/Reading/ReadingList.h"

class ReadingListWidget : public QWidget, public Observer{
  Q_OBJECT
private:
  ReadingList* readinglist;
  QTableView* table_view;
  QPushButton* delete_reading;
  QPushButton* add_to_display;

public:
  ReadingListWidget(ReadingList* rl, QWidget* parent =nullptr);
  
signals:
  void displayReading(Reading* reading);

public slots:
  void findReading(int id, Reading* reading);
  void deleteReadingClicked();
  void addClicked();
  virtual void observerUpdate() override;
};

#endif