#include"ReadingDisplayWidget.h"
#include<QVBoxLayout>
#include<QHBoxLayout>

ReadingDisplayWidget::Buttons::Buttons(Reading* r, QWidget* parent):QPushButton(parent){
  reading=r;
  reading->attach(this);
  setText("Delete" + reading->getName());
  connect(this,&QPushButton::clicked,this,&ReadingDisplayWidget::Buttons::remove);
}

ReadingDisplayWidget::Buttons::~Buttons(){
  reading->detach(this);
}

void ReadingDisplayWidget::Buttons::observerUpdate() {
  setText("Delete" + reading->getName());
}

void ReadingDisplayWidget::Buttons::remove(){
  emit deleteclicked(reading);
}

void ReadingDisplayWidget::makeButton(Reading* r){
  buttons.append(new Buttons(r));
  hbox->addWidget(buttons.last());
  connect(buttons.last(), &ReadingDisplayWidget::Buttons::deleteclicked, this, &ReadingDisplayWidget::removeReading);
}

void ReadingDisplayWidget::deleteButton(Reading* r){
  auto it=buttons.begin();
  for(it;it!=buttons.end();it++){
    if(r==(*it)->reading)
      break;
  }
  if(it!=buttons.end()){
    hbox->removeWidget(*it);
    delete(*it);
    buttons.erase(it);
  }
}

ReadingDisplayWidget::ReadingDisplayWidget(ReadingTable* table, QWidget* parent): QWidget(parent){
  chart = new ReadingChart();
  chart_view = new ChartView(chart);
  reading_table = table;
  reading_table->attach(this);
  QWidget* button= new QWidget();
  hbox= new QHBoxLayout(button);
  QVBoxLayout* vbox = new QVBoxLayout(this);
  QScrollArea* scroll_area = new QScrollArea();
  scroll_area->setWidget(button);
  vbox->addWidget(chart_view);
  vbox->addWidget(scroll_area);
  vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

ReadingTable* ReadingDisplayWidget::getReadingTable() const{
  return reading_table;
}

void ReadingDisplayWidget::observerUpdate(){
  for(Reading* r : reading_table->getTable()){
    if(!chart->QMap::contains(r)){
      chart->addReading(r);
      makeButton(r);
    }
  }
  for(Reading* r : chart->keys()){
    if(!reading_table->contains(r))
      chart->removeReading(r);
      deleteButton(r);
  }
  show();
}

void ReadingDisplayWidget::removeReading(Reading* r){
  chart->removeReading(r);
  deleteButton(r);
}