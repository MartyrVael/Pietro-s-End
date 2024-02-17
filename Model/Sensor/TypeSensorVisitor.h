#ifndef TYPESENSORVISITOR_H
#define TYPESENSORVISITOR_H
#include<QString>
#include"SensorVisitor.h"

class TypeSensorVisitor: public SensorVisitor{
private:
  QString type_name;
public:
  virtual ~TypeSensorVisitor(){};
  virtual void visit(const DustSensor&);
  virtual void visit(const RainSensor&);
  virtual void visit(const TemperatureSensor&);
  virtual void visit(const WindSensor&);
  virtual void visit(const HumiditySensor&);
  QString getType() const;
};

#endif