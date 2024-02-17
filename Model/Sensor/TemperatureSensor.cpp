#include<random>
#include"TemperatureSensor.h"
#include"../Reading/TemperatureReading.h"
#include"../Reading/ReadingList.h"

const double TemperatureSensor::absolute_min = -15;
const double TemperatureSensor::absolute_max = 55;

TemperatureSensor* TemperatureSensor:: clone() const {
	return new TemperatureSensor(*this);
}

void TemperatureSensor::accept(SensorVisitor& v){
  v.visit(*this);
}

Reading* TemperatureSensor::simulate(const QString& name, int numEntries) const{
  QList<double>* result = new QList<double>();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> dis(min, max);
  for(int i=0; i < numEntries; i++){
    result->append(dis(gen));
  }
  Reading* reading = new TemperatureReading(name, result);
  ReadingList::readinglist()->insert(getId(), reading);
  return reading;
}

bool TemperatureSensor::setMax(double d){
  if(d >= min && d <= absolute_max){
    max = d;
    return true;
  }
  return false;
}

bool TemperatureSensor::setMin(double d){
  if(d <= max && d >= absolute_min){
    min = d;
    return true;
  }
  return false;
}

bool TemperatureSensor::setMinMax(double low, double high){
  if(low <= high && low >= absolute_min && high <= absolute_max){
    min = low;
    max = high;
    return true;
  }
  return false;
}

double TemperatureSensor::getMin() const{
  return min;
}

double TemperatureSensor::getMax() const{
  return max;
}

double TemperatureSensor::getAbsoluteMax() const{
  return absolute_max;
}

double TemperatureSensor::getAbsoluteMin() const{
  return absolute_min;
}