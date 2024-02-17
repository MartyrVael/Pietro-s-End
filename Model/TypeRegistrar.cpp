#include"TypeRegistrar.h"
#include"Sensor/SensorFactory.h"
#include"Reading/ReadingFactory.h"
#include"Sensor/DustSensor.h"
#include"Sensor/HumiditySensor.h"
#include"Sensor/TemperatureSensor.h"
#include"Sensor/WindSensor.h"
#include"Sensor/RainSensor.h"
#include"Reading/DustReading.h"
#include"Reading/HumidityReading.h"
#include"Reading/TemperatureReading.h"
#include"Reading/WindReading.h"
#include"Reading/RainReading.h"

TypeRegistrar::TypeRegistrar(){
  SensorFactory::registerType("Temperature", [](const QString& name)->BaseSensor*{return new TemperatureSensor(name);}, [](const QString& name, int id)->BaseSensor*{return new TemperatureSensor(name,id);});
  SensorFactory::registerType("Wind", [](const QString& name)->BaseSensor*{return new WindSensor(name);}, [](const QString& name, int id)->BaseSensor*{return new WindSensor(name,id);});
  SensorFactory::registerType("Humidity", [](const QString& name)->BaseSensor*{return new HumiditySensor(name);}, [](const QString& name, int id)->BaseSensor*{return new HumiditySensor(name,id);});
  SensorFactory::registerType("Dust", [](const QString& name)->BaseSensor*{return new DustSensor(name);}, [](const QString& name, int id)->BaseSensor*{return new DustSensor(name,id);});
  SensorFactory::registerType("Rain", [](const QString& name)->BaseSensor*{return new RainSensor(name);}, [](const QString& name, int id)->BaseSensor*{return new RainSensor(name,id);});
  ReadingFactory::registerType("Temperature", [](const QString& name, const QList<double>* list)->Reading*{return new TemperatureReading(name, list);});
  ReadingFactory::registerType("Wind", [](const QString& name, const QList<double>* list)->Reading*{return new WindReading(name, list);});
  ReadingFactory::registerType("Humidity", [](const QString& name, const QList<double>* list)->Reading*{return new HumidityReading(name, list);});
  ReadingFactory::registerType("Dust", [](const QString& name, const QList<double>* list)->Reading*{return new DustReading(name, list);});
  ReadingFactory::registerType("Rain", [](const QString& name, const QList<double>* list)->Reading*{return new RainReading(name, list);});
}

namespace{
  static TypeRegistrar r;
}