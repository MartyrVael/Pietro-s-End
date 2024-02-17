#ifndef R_READING_H
#define R_READING_H
#include"Reading.h"

class RainReading: public Reading {
public:
  RainReading(const QString& n, const QList<double>* v): Reading(n,v) {};
  virtual void accept(ReadingVisitor& rv) override;
};

#endif