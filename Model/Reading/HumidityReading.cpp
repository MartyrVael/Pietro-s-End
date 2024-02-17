#include"HumidityReading.h"
#include"ReadingVisitor.h"

void HumidityReading::accept(ReadingVisitor& v){
  v.visit(*this);
}