#include"DustReading.h"
#include"ReadingVisitor.h"

void DustReading::accept(ReadingVisitor& v){
  v.visit(*this);
}