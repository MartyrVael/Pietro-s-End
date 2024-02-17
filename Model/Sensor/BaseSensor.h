#ifndef B_SENSOR_H
#define B_SENSOR_H
#include<QString>
#include"../Subject.h"
#include"SensorVisitor.h"
#include"../Reading/Reading.h"

class BaseSensor : public Subject{
private:
  static int counter;
  QString name;
  const int id;
protected:
  BaseSensor(const QString& n): name(n), id(++counter) {};
  BaseSensor(const BaseSensor& b): name(b.name), id(++counter) {};
  BaseSensor(const QString& n, int i);
public:
  QString getName() const;
  void setName(const QString& s);
  int getId() const;
  virtual Reading* simulate(const QString& name, int entries) const =0;
  virtual BaseSensor* clone() const =0;
  virtual ~BaseSensor() =default;
  virtual void accept(SensorVisitor& visitor) =0;
  virtual bool setMin(double) =0;
  virtual bool setMax(double) =0;
  virtual bool setMinMax(double low, double high) =0;
  virtual double getMin() const =0;
  virtual double getMax() const =0;
  virtual double getAbsoluteMax() const =0;
  virtual double getAbsoluteMin() const =0;
};

#endif