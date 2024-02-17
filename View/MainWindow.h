#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
#include"../Model/Environment.h"
#include"NodesWidget.h"
#include"SensorShow.h"
#include"ReadingListWidget.h"
#include"TableContainerWidget.h"

class MainWindow : public QMainWindow{
  Q_OBJECT
public:
  explicit MainWindow(Environment* e, QWidget* parent = nullptr);

private:
  QString savepath;
  Environment* environment;
  NodesWidget* nodes_view;
  SensorShow* sensor_show;
  ReadingListWidget* readinglist_widget;
  TableContainerWidget* tablecontainer_widget;
  
public slots:
  void loadEnvironment();
  void saveEnvironment();
  void saveAsEnvironment();
  void loadSection();
  void saveSection();
};

#endif