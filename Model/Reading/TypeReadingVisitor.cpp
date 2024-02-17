#include"TypeReadingVisitor.h"

void TypeReadingVisitor::visit(TemperatureReading& r){
  Q_UNUSED(r);
  type_name = "Temperature";
}

void TypeReadingVisitor::visit(WindReading& r){
  Q_UNUSED(r);
  type_name = "Wind";
}

void TypeReadingVisitor::visit(DustReading& r){
  Q_UNUSED(r);
  type_name = "Dust";
}

void TypeReadingVisitor::visit(HumidityReading& r){
  Q_UNUSED(r);
  type_name = "Humidity";
}

void TypeReadingVisitor::visit(RainReading& r){
  Q_UNUSED(r);
  type_name = "Rain";
}

QString TypeReadingVisitor::getType() const{
  return type_name;
}