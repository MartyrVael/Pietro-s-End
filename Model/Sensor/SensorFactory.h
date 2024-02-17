#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H
#include<QString>
#include<QMap>
#include"BaseSensor.h"

class SensorFactory{
  typedef BaseSensor* (*constructorSensor)(const QString&);
  typedef BaseSensor* (*loaderSensor)(const QString&, int id);
private:
  static QMap<QString, constructorSensor> constructor_map;
  static QMap<QString, loaderSensor> loader_map;
public:
  static QStringList concrete_sensor_types;
  static void registerType(const QString& typekey, constructorSensor constructor, loaderSensor loader);
  static BaseSensor* createSensor(const QString& name, const QString& type);
  static BaseSensor* loadSensor(const QString& name, int id, const QString& type);
};

#endif