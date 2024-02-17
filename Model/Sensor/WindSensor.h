#ifndef W_SENSOR_H
#define W_SENSOR_H
#include"BaseSensor.h"

class WindSensor: public BaseSensor{
private:
  static const double absolute_min;
  static const double absolute_max;
  double min;
  double max;
public:
  WindSensor(const QString& n): BaseSensor(n), min(5), max(70) {};
  WindSensor(const QString& n, int i): BaseSensor(n,i), min(5), max(70) {};
  virtual Reading* simulate(const QString& name, int entries) const override;
  virtual WindSensor* clone() const override;
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