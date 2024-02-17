#ifndef SENSOR_SHOW_H
#define SENSOR_SHOW_H
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDoubleSpinBox>
#include<QHBoxLayout>
#include<QInputDialog>
#include"../Model/Observer.h"
#include"Model/Sensor/BaseSensor.h"
#include"Model/Sensor/TypeSensorVisitor.h"

class SensorShow: public QWidget, public Observer {
  Q_OBJECT
private:
	BaseSensor* sensor;
	QLabel* sensor_name;
	QLabel* sensor_id;
	QLabel* sensor_type;
	QLabel* type_image;
	QLabel* range_id;
	QPushButton* change_name_button;
	QPushButton* simulate;
	QDoubleSpinBox* min_range;
	QDoubleSpinBox* max_range;
public:
	SensorShow(QWidget* parent = nullptr);
	void refresh();
	virtual void observerUpdate() override;

signals:
	void simulated(int id, Reading* reading);

public slots:
	void changeName();
	void startSimulation();
	void setMin();
	void setMax();
	void addSensor(BaseSensor* s);
	void removeSensor();
};

#endif