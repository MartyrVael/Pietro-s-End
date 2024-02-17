#include"WindReading.h"
#include"ReadingVisitor.h"

void WindReading::accept(ReadingVisitor& v){
  v.visit(*this);
}