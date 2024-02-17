#ifndef D_SENSOR_H
#define D_SENSOR_H
#include"BaseSensor.h"

class DustSensor: public BaseSensor{
private:
  static const unsigned int absolute_max;
  static const unsigned int absolute_min;
  unsigned int max;
  unsigned int min;
public:
  DustSensor(const QString& n): BaseSensor(n), max(80), min(absolute_min) {};
  DustSensor(const QString& n, int i): BaseSensor(n,i), max(80), min(absolute_min) {};
  virtual Reading* simulate(const QString& name, int entries) const override;
  virtual DustSensor* clone() const override;
  virtual void accept(SensorVisitor& visitor) override;
  virtual bool setMin(double d) override;
  virtual bool setMax(double d) override;
  virtual bool setMinMax(double low,  double high) override;
  virtual double getMin() const override;
  virtual double getMax() const override;
  virtual double getAbsoluteMax() const override;
  virtual double getAbsoluteMin() const override;
};

#endif