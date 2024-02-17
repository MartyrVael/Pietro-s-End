#include<random>
#include"HumiditySensor.h"
#include"../Reading/HumidityReading.h"
#include"../Reading/ReadingList.h"

const unsigned int HumiditySensor::absolute_max = 100;
const unsigned int HumiditySensor::absolute_min = 0;

HumiditySensor* HumiditySensor:: clone() const {
	return new HumiditySensor(*this);
};

void HumiditySensor::accept(SensorVisitor& v){
  v.visit(*this);
}

Reading* HumiditySensor::simulate(const QString& name, int numEntries) const{
  QList<double>* result = new QList<double>();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<unsigned int> dis(min, max);
  for(int i=0; i < numEntries; i++){
    result->append(dis(gen));
  }
  Reading* reading = new HumidityReading(name, result);
  ReadingList::readinglist()->insert(getId(), reading);
  return reading;
}

bool HumiditySensor::setMax(double d){
  if(d < 0)
    return false;
  unsigned int i =(unsigned int) d;
  if(i >= min && i <= absolute_max){
    max = i;
    return true;
  }
  return false;
}

bool HumiditySensor::setMin(double d){
  if(d < 0)
    return false;
  unsigned int i = (unsigned int)d;
  if(i <= max && i >= absolute_min){
    min = i;
    return true;
  }
  return false;
}

bool HumiditySensor::setMinMax(double low, double high){
  if(low < 0 || high < 0)
    return false;
  unsigned int newmin =(unsigned int) low;
  unsigned int newmax =(unsigned int) high;
  if(newmin <= newmax && newmin >= absolute_min && newmax <= absolute_max){
    min = newmin;
    max = newmax;
    return true;
  }
  return false;
}

double HumiditySensor::getMin() const{
  return min;
}

double HumiditySensor::getMax() const{
  return max;
}

double HumiditySensor::getAbsoluteMax() const{
  return absolute_max;
}

double HumiditySensor::getAbsoluteMin() const{
  return absolute_min;
}