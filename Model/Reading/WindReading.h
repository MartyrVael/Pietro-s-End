#ifndef W_READING_H
#define W_READING_H
#include "Reading.h"

class WindReading: public Reading {
public:
  WindReading(const QString& n, const QList<double>* v): Reading(n,v) {};
  virtual void accept(ReadingVisitor& rv) override;
};



#endif