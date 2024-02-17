#ifndef READINGVISITOR_H
#define READINGVISITOR_H

class DustReading;
class TemperatureReading;
class RainReading;
class HumidityReading;
class WindReading;

class ReadingVisitor{
public:
  virtual ~ReadingVisitor(){};
  virtual void visit(DustReading&) =0;
  virtual void visit(RainReading&) =0;
  virtual void visit(TemperatureReading&) =0;
  virtual void visit(WindReading&) =0;
  virtual void visit(HumidityReading&) =0;
};

#endif