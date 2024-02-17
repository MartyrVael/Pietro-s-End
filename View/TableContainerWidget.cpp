#include"TableContainerWidget.h"
#include<QHBoxLayout>

TableContainerWidget::TableContainerWidget(TableContainer* tc, QWidget* parent): QWidget(parent), tablecontainer(tc){
  tablecontainer->attach(this);
  tabs = new QTabWidget();
  QHBoxLayout* hbox = new QHBoxLayout(this);
  hbox->addWidget(tabs);
}

void TableContainerWidget::highlightReading(Reading* r){
  emit searchReading(r);
}

void TableContainerWidget::changeTab(ReadingDisplayWidget* const widget){
  tabs->setCurrentWidget(widget);
}

void TableContainerWidget::observerUpdate(){
  int count = tablecontainer->count();
  for(int i=0; i < count; i++){
    bool found = false;
    for(ReadingDisplayWidget* display : displays){
      if(display->getReadingTable() == tablecontainer->getTable(i)){
        found = true;
        break;
      };
    }
    if(!found){
      ReadingTable* newtable = tablecontainer->getTable(i);
      addNewTable(tablecontainer->getKey(newtable), newtable);
    }
  }
  QWidget::update();
}

void TableContainerWidget::addNewTable(const QString& type, ReadingTable* table){
  displays.append(new ReadingDisplayWidget(table));
  displays.last();
  tabs->addTab(displays.last(), type);
  connect(displays.last(), &ReadingDisplayWidget::readingcontained, this, &TableContainerWidget::changeTab);
}