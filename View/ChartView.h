#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include<QChartView>
#include"../Model/Observer.h"
#include"ReadingChart.h"

class ChartView: public QChartView, public Observer{
  Q_OBJECT
public:
  ChartView(ReadingChart* chart);
  ~ChartView();
public slots:
  virtual void observerUpdate() override;
};

#endif