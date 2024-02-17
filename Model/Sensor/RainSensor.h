#ifndef R_SENSOR_H
#define R_SENSOR_H
#include"BaseSensor.h"

class RainSensor: public BaseSensor{
private:
  static const unsigned int absolute_max;
  static const unsigned int absolute_min;
  unsigned int min;
  unsigned int max;
public:
  RainSensor(const QString& n): BaseSensor(n), min(0), max(10) {};
  RainSensor(const QString& n, int i): BaseSensor(n,i), min(0), max(10) {};
  virtual Reading* simulate(const QString& name, int entries) const override;
  virtual RainSensor* clone() const override;
  virtual void accept(SensorVisitor& visitor) override;
  virtual bool setMax(double d) override;
  virtual bool setMin(double d) override;
  virtual bool setMinMax(double low, double high) override;
  virtual double getMin() const override;
  virtual double getMax() const override;
  virtual double getAbsoluteMax() const override;
  virtual double getAbsoluteMin() const override;
};
#endif