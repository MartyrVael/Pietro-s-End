#include"ReadingSeries.h"
#include"Reading.h"

ReadingSeries::ReadingSeries(Reading* r): reading(r){
  reading->attach(this);
}

ReadingSeries::~ReadingSeries(){
  reading->detach(this);
}

void ReadingSeries::observerUpdate(){
  setName(reading->getName());
  notify();
}