#ifndef TYPEREADINGVISITOR_H
#define TYPEREADINGVISITOR_H
#include<QString>
#include"ReadingVisitor.h"

class TypeReadingVisitor: public ReadingVisitor{
private:
  QString type_name;
public:
  virtual ~TypeReadingVisitor(){};
  virtual void visit(DustReading&);
  virtual void visit(RainReading&);
  virtual void visit(TemperatureReading&);
  virtual void visit(WindReading&);
  virtual void visit(HumidityReading&);
  QString getType() const;
};

#endif