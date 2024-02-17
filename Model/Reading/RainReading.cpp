#include"RainReading.h"
#include"ReadingVisitor.h"

void RainReading::accept(ReadingVisitor& v){
  v.visit(*this);
}