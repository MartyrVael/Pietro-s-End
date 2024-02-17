#ifndef READINGFACTORY_H
#define READINGFACTORY_H
#include<QString>
#include<QMap>
#include"Reading.h"

class ReadingFactory{
  typedef Reading* (*constructorReading)(const QString&, const QList<double>*);
private:
  static QMap<QString, constructorReading> constructor_map;
public:
  static void registerType(const QString& typekey, constructorReading constructor);
  static Reading* createReading(const QString& name, const QList<double>* list, const QString& type);
};

#endif