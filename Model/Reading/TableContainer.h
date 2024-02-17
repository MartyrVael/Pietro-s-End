#ifndef TABLECONTAINER_H
#define TABLECONTAINER_H
#include<QMap>
#include"../Subject.h"
#include"ReadingVisitor.h"
#include"ReadingTable.h"

class TableContainer: public Subject{
private:
  static TableContainer* instance;
  TableContainer();
  QMap<QString, ReadingTable*> tables;

  void addTable(const QString& key);
public:
  int count() const;
  static TableContainer* tablecontainer();
  void insertReading(Reading* reading);
  void removeReading(Reading* reading);
  ReadingTable* getTable(const QString& type) const;
  ReadingTable* getTable(int index) const;
  QString getKey(ReadingTable* value) const;
};

#endif