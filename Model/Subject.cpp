#include"Subject.h"

void Subject::notify() const{
  for(Observer* o : observers){
    o->observerUpdate();
  }
}

void Subject::attach(Observer* o){
  if(o != nullptr && !observers.contains(o))
    observers.append(o);
}

void Subject::detach(Observer* o){
  if(o != nullptr && observers.contains(o))
    observers.removeAll(o);
}