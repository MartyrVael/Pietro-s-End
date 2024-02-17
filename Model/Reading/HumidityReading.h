#ifndef H_READING_H
#define H_READING_H
#include"Reading.h"

class HumidityReading: public Reading {
public:
  HumidityReading(const QString& n, const QList<double>* v): Reading(n,v) {};
  virtual void accept(ReadingVisitor& rv) override;
};

#endif