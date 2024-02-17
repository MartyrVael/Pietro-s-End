#include"MainWindow.h"
#include<QApplication>
#include<QSplitter>
#include<QVBoxLayout>
#include<QMenuBar>
#include<QAction>
#include<QFileDialog>

MainWindow::MainWindow(Environment* e, QWidget* parent): QMainWindow(parent), environment(e){
  QSplitter* splitter = new QSplitter(this);
  setCentralWidget(splitter);
  QSplitter* topsplit = new QSplitter();
  QSplitter* bottomsplit = new QSplitter();
  splitter->setOrientation(Qt::Vertical);
  nodes_view = new NodesWidget(environment->tree());
  readinglist_widget = new ReadingListWidget(environment->readinglist());
  tablecontainer_widget = new TableContainerWidget(environment->tablecontainer());
  sensor_show = new SensorShow();

  topsplit->addWidget(nodes_view);
  topsplit->addWidget(sensor_show);
  bottomsplit->addWidget(readinglist_widget);
  bottomsplit->addWidget(tablecontainer_widget);
  splitter->addWidget(topsplit);
  splitter->addWidget(bottomsplit);

  QAction* save_environment = new QAction("Save");
  save_environment->setShortcut(Qt::CTRL | Qt::Key_S);
  QAction* save_as_environment = new QAction("Save As...");
  save_as_environment->setShortcut(Qt::CTRL | Qt::Key_S | Qt::ShiftModifier);
  QAction* load_environment = new QAction("Load");
  load_environment->setShortcut(Qt::CTRL | Qt::Key_O);
  QAction* import_section = new QAction("Import section");
  QAction* export_section = new QAction("Export Section");
  
  QMenu* file = menuBar()->addMenu("&File");
  file->addAction(save_environment);
  file->addAction(save_as_environment);
  file->addAction(load_environment);
  QMenu* sections = menuBar()->addMenu("&Sections");
  sections->addAction(import_section);
  sections->addAction(export_section);

  connect(nodes_view, &NodesWidget::leafSelected, sensor_show, &SensorShow::addSensor);
  connect(nodes_view, &NodesWidget::leafDeselected, sensor_show, &SensorShow::removeSensor);
  connect(sensor_show, &SensorShow::simulated, readinglist_widget, &ReadingListWidget::findReading);
  connect(save_environment, &QAction::triggered, this, &MainWindow::saveEnvironment);
  connect(save_as_environment, &QAction::triggered, this, &MainWindow::saveAsEnvironment);
  connect(load_environment, &QAction::triggered, this, &MainWindow::loadEnvironment);
  connect(import_section, &QAction::triggered, this, &MainWindow::loadSection);
  connect(export_section, &QAction::triggered, this, &MainWindow::saveSection);
};

void MainWindow::loadSection(){
  TreeNode* parent = nodes_view->selected();
  if(environment->tree()->leaf(parent) || parent == nullptr){
    QMessageBox::StandardButton warn = QMessageBox::warning(this, "Invalid parent node", "Please select a different node", QMessageBox::StandardButton::Ok);
    Q_UNUSED(warn);
    return;
  }
  QString path = QFileDialog::getOpenFileName(this, "Import Section", "./", "JSON files (*.json)");
  if(!path.isEmpty())
    environment->loadSection(parent, path);
}

void MainWindow::saveSection(){
  QString path = QFileDialog::getSaveFileName(this, "Export Section", "./", "JSON files (*.json)");
  if(!path.isEmpty())
    environment->saveSection(nodes_view->selected(), path);
}

void MainWindow::loadEnvironment(){
  QString path = QFileDialog::getOpenFileName(this, "Load Environment", "./", "JSON files (*.json)");
  if(!path.isEmpty())
    environment->loadEnvironment(path);
}

void MainWindow::saveEnvironment(){
  if(savepath.isEmpty())
    savepath = QFileDialog::getSaveFileName(this, "Save Environment", "./", "JSON files (*.json)");
  environment->saveEnvironment(savepath);
}

void MainWindow::saveAsEnvironment(){
  QString path = QFileDialog::getSaveFileName(this, "Save Environment", "./", "JSON files (*.json)");
  environment->saveEnvironment(path);
}