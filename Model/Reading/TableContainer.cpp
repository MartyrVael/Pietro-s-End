#include<iterator>
#include"TableContainer.h"
#include"ReadingTable.h"
#include"TypeReadingVisitor.h"

TableContainer* TableContainer::instance = nullptr;

TableContainer::TableContainer(){}

void TableContainer::insertReading(Reading* r){
  TypeReadingVisitor v;
  r->accept(v);
  QString type = v.getType();
  if(!tables.contains(type))
    addTable(type);
  tables.value(type)->append(r);
  notify();
}

void TableContainer::removeReading(Reading* r){
  for(ReadingTable* table : tables){
    table->remove(r);
  }
}

TableContainer* TableContainer::tablecontainer(){
  if(instance == nullptr)
    instance = new TableContainer();
  return instance;
}

ReadingTable* TableContainer::getTable(const QString& type) const{
  return tables.value(type);
}

ReadingTable* TableContainer::getTable(int index) const{
  if(index < 0 || index >= tables.count())
    return nullptr;
  auto pos = tables.begin();
  for(int i=0; i < index; i++){
    pos++;
  }
  return pos.value();
}

QString TableContainer::getKey(ReadingTable* value) const{
  return tables.key(value);
}

void TableContainer::addTable(const QString&  key){
  tables.insert(key, new ReadingTable());
  notify();
}

int TableContainer::count() const{
  return tables.count();
}