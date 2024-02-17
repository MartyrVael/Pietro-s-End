#include<random>
#include"DustSensor.h"
#include"../Reading/DustReading.h"
#include"../Reading/ReadingList.h"

const unsigned int DustSensor::absolute_max = 120;

const unsigned int DustSensor::absolute_min = 0;

DustSensor* DustSensor::clone() const {
	return new DustSensor(*this);
}

void DustSensor::accept(SensorVisitor& v){
  v.visit(*this);
}

Reading* DustSensor::simulate(const QString& name, int numEntries) const{
  QList<double>* result = new QList<double>();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<unsigned int> dis(min, max);
  for(int i=0; i < numEntries; i++){
    result->append(dis(gen));
  }
  Reading* reading = new DustReading(name, result);
  ReadingList::readinglist()->insert(getId(), reading);
  return reading;
}

bool DustSensor::setMin(double d){
  if(d < 0)
    return false;
  unsigned int i =(unsigned int) d;
  if(i >= absolute_min && i <= max){
    min = i;
    return true;
  }
  return false;
}

bool DustSensor::setMax(double d){
  if(d < 0)
    return false;
  unsigned int i =(unsigned int) d;
  if(i <= absolute_max && i >= min){
    max = i;
    return true;
  }
  return false;
}

bool DustSensor::setMinMax(double low, double high){
  if(low < 0 || high < 0)
    return false;
  unsigned int newmin = low;
  unsigned int newmax = high;
  if(newmax >= newmin && newmin >= absolute_min && newmax <= absolute_max){
    max = newmax;
    min = newmin;
    return true;
  }
  return false;
}

double DustSensor::getMin() const{
  return min;
}

double DustSensor::getMax() const{
  return max;
}

double DustSensor::getAbsoluteMax() const{
  return absolute_max;
}

double DustSensor::getAbsoluteMin() const{
  return absolute_min;
}