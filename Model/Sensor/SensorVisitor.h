#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

class DustSensor;
class TemperatureSensor;
class RainSensor;
class HumiditySensor;
class WindSensor;

class SensorVisitor{
public:
  virtual ~SensorVisitor(){};
  virtual void visit(const DustSensor&) =0;
  virtual void visit(const RainSensor&) =0;
  virtual void visit(const TemperatureSensor&) =0;
  virtual void visit(const WindSensor&) =0;
  virtual void visit(const HumiditySensor&) =0;
};

#endif