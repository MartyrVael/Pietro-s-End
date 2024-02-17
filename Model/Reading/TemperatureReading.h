#ifndef T_READING_H
#define T_READING_H
#include "Reading.h"

class TemperatureReading: public Reading {
public:
  TemperatureReading(const QString& n, const QList<double>* v): Reading(n,v) {};
  virtual void accept(ReadingVisitor& rv) override;
};



#endif