#ifndef ICONVISITOR_H
#define ICONVISITOR_H
#include<QPixmap>
#include"Model/Sensor/SensorVisitor.h"
#include"Model/Reading/ReadingVisitor.h"

class IconVisitor : public SensorVisitor, public ReadingVisitor{
private:
  QPixmap icon;
public:
  QPixmap getIcon() const;
  virtual void visit(const DustSensor&) override;
  virtual void visit(const RainSensor&) override;
  virtual void visit(const TemperatureSensor&) override;
  virtual void visit(const WindSensor&) override;
  virtual void visit(const HumiditySensor&) override;
  virtual void visit(DustReading&) override;
  virtual void visit(RainReading&) override;
  virtual void visit(TemperatureReading&) override;
  virtual void visit(WindReading&) override;
  virtual void visit(HumidityReading&) override;
};

#endif