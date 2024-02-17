#include"SensorFactory.h"

QMap<QString, SensorFactory::constructorSensor> SensorFactory::constructor_map;
QMap<QString, SensorFactory::loaderSensor> SensorFactory::loader_map;
QStringList SensorFactory::concrete_sensor_types;

void SensorFactory::registerType(const QString& typekey, constructorSensor constructor, loaderSensor loader){
  constructor_map.insert(typekey, constructor);
  loader_map.insert(typekey, loader);
  concrete_sensor_types.append(typekey);
}

BaseSensor* SensorFactory::createSensor(const QString& name, const QString& type){
  QMap<QString, constructorSensor>::iterator it =constructor_map.find(type);
  if(it == constructor_map.end())
    return nullptr;
  return (it.value())(name);
};

BaseSensor* SensorFactory::loadSensor(const QString& name, int id, const QString& type){
  QMap<QString, loaderSensor>::iterator it = loader_map.find(type);
  if(it == loader_map.end())
    return nullptr;
  return (it.value())(name, id);
}

