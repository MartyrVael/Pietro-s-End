#include"ReadingFactory.h"

QMap<QString, ReadingFactory::constructorReading> ReadingFactory::constructor_map;

void ReadingFactory::registerType(const QString& typekey, constructorReading constructor){
  constructor_map.insert(typekey, constructor);
}

Reading* ReadingFactory::createReading(const QString& name, const QList<double>* list, const QString& type){
  QMap<QString, constructorReading>::iterator it = constructor_map.find(type);
  if(it == constructor_map.end())
    return nullptr;
  return (it.value())(name, list);
}