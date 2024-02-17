#include"Reading.h"

Reading::~Reading(){
  delete reading;
}

void Reading::setName(QString n){
  this->name = n;
  notify();
};

QString Reading::getName() const{
  return this->name;
};

int Reading::getSize() const{
  return reading->count();
}

double Reading::getValue(int index) const{
  return reading->at(index);
}

ReadingSeries* Reading::toSeries() const{
  ReadingSeries* series = new ReadingSeries(const_cast<Reading*>(this));
  series->setName(name);
  for(int i=0; i < reading->count(); i++){
    series->append(i, reading->operator[](i));
  }
  return series;
}