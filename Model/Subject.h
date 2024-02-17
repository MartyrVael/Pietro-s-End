#ifndef SUBJECT_H
#define SUBJECT_H
#include<QList>
#include"Observer.h"

class Subject{
private:
  QList<Observer*> observers;
public:
  Subject(){};
  virtual ~Subject(){};
  virtual void notify() const;
  virtual void attach(Observer* o);
  virtual void detach(Observer* o);
};

#endif