#ifndef READINGSERIES_H
#define READINGSERIES_H
#include<QLineSeries>
#include"../Observer.h"
#include"../Subject.h"

class Reading;

class ReadingSeries : public QLineSeries, public Observer, public Subject{
private:
 Reading* reading;
public:
  ReadingSeries(Reading* r);
  virtual ~ReadingSeries();
  virtual void observerUpdate() override;
};

#endif