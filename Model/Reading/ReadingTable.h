#ifndef READINGTABLE_H
#define READINGTABLE_H
#include<QVariant>
#include<QList>
#include<QAbstractTableModel>
#include"../Observer.h"
#include"../Subject.h"
#include"Reading.h"
#include"ReadingSeries.h"

class ReadingTable : public QAbstractItemModel, public Observer, public Subject{
private:
  QList<Reading*> table;
public:
  ReadingTable(){};
  virtual ~ReadingTable();
  virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  virtual QModelIndex parent(const QModelIndex& index) const override;
  virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
  virtual bool hasChildren(const QModelIndex& parent = QModelIndex()) const;
  Reading* getReading(const QModelIndex& index) const;
  QModelIndex getIndex(Reading* reading) const;
  void append(Reading* reading);
  void remove(Reading* reading);
  void remove(const QModelIndex& index);
  bool contains(Reading*) const;
  int row(Reading*) const;
  virtual void observerUpdate() override;
  const QList<Reading*> getTable() const;
};

#endif