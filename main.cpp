#include<QApplication>
#include<QIcon>
#include"Model/Environment.h"
#include"View/MainWindow.h"

//NB atm FilteredList sucks. Consider improving, or disarcing it

int main(int argc, char* argv[]){
  QApplication a(argc, argv);
  Environment* e = Environment::environment();
  MainWindow* v = new MainWindow(e);
  v->setWindowTitle("SensorSim");
  v->show();
  return a.exec();
}