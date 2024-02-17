#include"BaseSensor.h"

int BaseSensor::counter = 0;

BaseSensor::BaseSensor(const QString& n, int i): name(n), id(i){
  counter = counter>i? counter : id;
};

QString BaseSensor::getName() const{
  return name;
}

void BaseSensor::setName(const QString& s){
  name = s;
  notify();
}

int BaseSensor::getId() const{
  return id;
}