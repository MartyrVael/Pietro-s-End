#ifndef READINGCHART_H
#define READINGCHART_H
#include<QMap>
#include<QChart>
#include"../Model/Observer.h"
#include"../Model/Subject.h"
#include"../Model/Reading/ReadingTable.h"
#include"../Model/Reading/ReadingSeries.h"

class ReadingChart : public QChart, public Observer, public Subject, public QMap<Reading*, ReadingSeries*>{
public:
  ReadingChart(){};
  ~ReadingChart();
  void addReading(Reading* reading);
  void removeReading(Reading* reading);
  virtual void observerUpdate() override;
};

#endif