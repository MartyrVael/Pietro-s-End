#ifndef READINGLIST_H
#define READINGLIST_H
#include<QMultiMap>
#include<QAbstractTableModel>
#include<QJsonObject>
#include<QJsonArray>
#include"../Observer.h"
#include"../Subject.h"
#include"Reading.h"
#include"ReadingFactory.h"
#include"TableContainer.h"

class ReadingList : public QAbstractTableModel, public Observer, public Subject{
  Q_OBJECT
private:
  static ReadingList* instance;
  QMultiMap<int, Reading*> map;
  ReadingList(){};

  int getKey(const QModelIndex& index) const;
  Reading* getValue(const QModelIndex& index) const;
  QJsonObject entryToJson(int key, Reading* value) const;
  void jsonToEntry(const QJsonObject& json);
  void importEntry(const QJsonObject& json, QMap<int, int>* changed_ids);
public:
  ~ReadingList();
  static ReadingList* readinglist();
  virtual int rowCount(const QModelIndex& parent =QModelIndex()) const override;
  virtual int columnCount(const QModelIndex& parent=QModelIndex()) const override;
  virtual QVariant data(const QModelIndex& index, int role =Qt::DisplayRole) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  virtual Qt::ItemFlags flags(const QModelIndex& index) const;
  virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
  void addToTable(const QModelIndex& index) const;
  void insert(int key, Reading* reading);
  void remove(int key);
  void remove(Reading* reading);
  void remove(const QModelIndex& index);
  void resetList();
  QModelIndex find(int id, Reading* reading) const;
  Reading* reading(const QModelIndex& index) const;
  QJsonObject toJson();
  void fromJson(const QJsonObject& json);
  QJsonObject exportReadings(QList<int>* ids) const;
  void importReadings(const QJsonObject& json, QMap<int,int>* changed_ids);
  virtual void observerUpdate() override;
};

#endif