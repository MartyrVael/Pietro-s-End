#include "SensorShow.h"
#include"IconVisitor.h"

SensorShow::SensorShow(QWidget* parent): QWidget(parent), sensor(nullptr){
  QHBoxLayout* hbox= new QHBoxLayout(this);
	QVBoxLayout* fieldbox= new QVBoxLayout();
	QVBoxLayout* set_minmax_box= new QVBoxLayout();
	QHBoxLayout* spinboxes = new QHBoxLayout();
	QVBoxLayout* buttonbox = new QVBoxLayout();

	type_image = new QLabel();
	sensor_name=new QLabel();
	sensor_id=new QLabel();
	sensor_type=new QLabel();
	range_id=new QLabel();
	min_range= new QDoubleSpinBox();
	max_range= new QDoubleSpinBox();
	simulate = new QPushButton("SIMULATE");
	simulate->setStyleSheet("QPushButton {background-color: #008800}");
	change_name_button = new QPushButton("Change Name");

	hbox->setAlignment(Qt::AlignCenter);
	hbox->insertWidget(0,type_image);
	fieldbox->setAlignment(Qt::AlignLeft | Qt:: AlignTop);
	fieldbox->addWidget(sensor_name);
	fieldbox->addWidget(sensor_id);
	fieldbox->addWidget(sensor_type);
	spinboxes->setAlignment(Qt::AlignCenter);
	spinboxes->addWidget(min_range);
	spinboxes->addWidget(max_range);
	set_minmax_box->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
	set_minmax_box->addWidget(range_id);
	set_minmax_box->addLayout(spinboxes);
	buttonbox->setAlignment(Qt::AlignCenter);
	buttonbox->addWidget(change_name_button);
	buttonbox->addWidget(simulate);
	hbox->addLayout(fieldbox);
	hbox->addStretch();
	hbox->addLayout(set_minmax_box);
	hbox->addStretch();
	hbox->addLayout(buttonbox);
	this->setEnabled(false);

	connect(change_name_button, &QPushButton::clicked, this, &SensorShow::changeName);
	connect(simulate, &QPushButton::clicked, this, &SensorShow::startSimulation);
	connect(min_range, &QDoubleSpinBox::valueChanged, this, &SensorShow::setMin);
	connect(max_range, &QDoubleSpinBox::valueChanged, this, &SensorShow::setMax);
};

void SensorShow::refresh(){
	IconVisitor i;
	sensor->accept(i);
	type_image->setText("icon");
	sensor_name->setText("Name:  " + sensor->getName());
	sensor_id->setText( "Id:  " + QString::number(sensor->getId()));
	TypeSensorVisitor v;
	sensor->accept(v);
	sensor_type->setText("Type:  " + v.getType());
	range_id->setText("Choose the values range:");
	min_range->setRange(sensor->getAbsoluteMin(), sensor->getAbsoluteMax());
	max_range->setRange(sensor->getAbsoluteMin(), sensor->getAbsoluteMax());
	min_range->setValue(sensor->getMin());
	max_range->setValue(sensor->getMax());
	this->show();
};

void SensorShow::observerUpdate(){
	refresh();
	QWidget::update();
}

void SensorShow::changeName(){
	bool ok;
	QString name = QInputDialog::getText(this, "Change Name", "Write the desired name:", QLineEdit::Normal,"",&ok);
	if (!ok) return;
	sensor->setName(name);
}

void SensorShow::setMin(){
	sensor->setMin(min_range->value());
	min_range->textFromValue(sensor->getMin());
};

void SensorShow::setMax(){
	sensor->setMax(max_range->value());
	max_range->textFromValue(sensor->getMax());
};

void SensorShow::startSimulation(){
	bool ok;
  QString name = QInputDialog::getText(this, "Gather Data", "Choose a name for the reading:", QLineEdit::Normal,"",&ok);
  if(!ok) return;
  unsigned int entry= QInputDialog::getInt(this, "Gather Data", "Select the desired amount of data gathered:", 1,1,50,1,&ok);
  if(!ok) return;
	emit simulated(sensor->getId(), sensor->simulate(name, entry));
}

void SensorShow::addSensor(BaseSensor* s){
	if(s == nullptr)
		return;
	if(sensor != nullptr)
		sensor->detach(this);
	sensor = s;
	if(sensor)
		sensor->attach(this);
	this->setEnabled(true);
	refresh();
}

void SensorShow::removeSensor(){
	if(sensor != nullptr)
		sensor->detach(this);
	sensor = nullptr;
	this->setEnabled(false);
}