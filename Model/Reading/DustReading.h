#ifndef D_READING_H
#define D_READING_H
#include"Reading.h"

class DustReading: public Reading {
public:
  DustReading(const QString& n, const QList<double>* v): Reading(n,v) {};
  virtual void accept(ReadingVisitor& v) override;
};

#endif