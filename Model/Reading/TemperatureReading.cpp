#include"TemperatureReading.h"
#include"ReadingVisitor.h"

void TemperatureReading::accept(ReadingVisitor& v){
  v.visit(*this);
}