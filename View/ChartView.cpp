#include"ChartView.h"

ChartView::ChartView(ReadingChart* chart): QChartView(chart){
  chart->attach(this);
}

ChartView::~ChartView(){
  delete chart();
}

void ChartView::observerUpdate(){
  setChart(chart());
  QWidget::update();
}