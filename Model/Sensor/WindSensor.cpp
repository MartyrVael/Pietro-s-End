#include<random>
#include"WindSensor.h"
#include"../Reading/WindReading.h"
#include"../Reading/ReadingList.h"


const double WindSensor::absolute_max = 180;
const double WindSensor::absolute_min = 0;

WindSensor* WindSensor::clone() const {
	return new WindSensor(*this);
}

void WindSensor::accept(SensorVisitor& v){
  v.visit(*this);
}

Reading* WindSensor::simulate(const QString& name, int numEntries) const{
  QList<double>* result = new QList<double>();
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<double> dis(min, max);
  for(int i=0; i < numEntries; i++){
    result->append(dis(gen));
  }
  Reading* reading = new WindReading(name, result);
  ReadingList::readinglist()->insert(getId(), reading);
  return reading;
}

bool WindSensor::setMax(double d){
  if(d >= min && d <= absolute_max){
    max = d;
    return true;
  }
  return false;
}

bool WindSensor::setMin(double d){
  if(d <= max && d >= absolute_min){
    min = d;
    return true;
  }
  return false;
}

bool WindSensor::setMinMax(double low, double high){
  if(low <= high && low >= absolute_min && high <= absolute_max){
    min = low;
    max = high;
    return true;
  }
  return false;
}

double WindSensor::getMin() const{
  return min;
}

double WindSensor::getMax() const{
  return max;
}

double WindSensor::getAbsoluteMax() const{
  return absolute_max;
}

double WindSensor::getAbsoluteMin() const{
  return absolute_min;
}