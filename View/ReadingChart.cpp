#include"ReadingChart.h"

ReadingChart::~ReadingChart(){
  for(ReadingSeries* s : *this){
    delete s;
  }
}

void ReadingChart::addReading(Reading* reading){
  if(reading == nullptr)
    return;
  ReadingSeries* series = reading->toSeries();
  series->attach(this);
  QMap::insert(reading, series);
  QChart::addSeries(series);
  QChart::createDefaultAxes();
}

void ReadingChart::removeReading(Reading* reading){
  if(reading == nullptr || !QMap::contains(reading))
    return;
  ReadingSeries* series = QMap::value(reading);
  QChart::removeSeries(series);
  delete series;
  QMap::remove(reading);
}

void ReadingChart::observerUpdate(){
  notify();
  update();
}