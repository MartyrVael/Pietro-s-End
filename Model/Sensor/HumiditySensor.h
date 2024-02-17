#ifndef H_SENSOR_H
#define H_SENSOR_H
#include"BaseSensor.h"

class HumiditySensor: public BaseSensor{
private:
  static const unsigned int absolute_max;
  static const unsigned int absolute_min;
  unsigned int max;
  unsigned int min;
public:
  HumiditySensor(const QString& n): BaseSensor(n), max(30), min(0) {};
  HumiditySensor(const QString& n, int i): BaseSensor(n,i), max(30), min(0) {};
  virtual Reading* simulate(const QString& name, int entries) const override;
  virtual HumiditySensor* clone() const;
  virtual void accept(SensorVisitor& visitor);
  virtual bool setMax(double d) override;
  virtual bool setMin(double d) override;
  virtual bool setMinMax(double low, double high) override;
  virtual double getMin() const override;
  virtual double getMax() const override;
  virtual double getAbsoluteMax() const override;
  virtual double getAbsoluteMin() const override;
};
#endif