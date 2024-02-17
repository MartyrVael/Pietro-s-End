#ifndef OBSERVER_H
#define OBSERVER_H

class Observer{
public:
  virtual ~Observer(){};
  virtual void observerUpdate() =0;
};

#endif