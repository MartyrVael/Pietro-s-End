QT += core widgets charts
CONFIG += debug

TARGET = SensorSim

HEADERS +=  Model/Sensor/BaseSensor.h \
            Model/Sensor/SensorFactory.h \
            Model/Sensor/SensorVisitor.h \
            Model/Sensor/TypeSensorVisitor.h \
            Model/Sensor/RainSensor.h \
            Model/Sensor/DustSensor.h \
            Model/Sensor/HumiditySensor.h \
            Model/Sensor/TemperatureSensor.h \
            Model/Sensor/WindSensor.h \
            Model/Reading/Reading.h \
            Model/Reading/DustReading.h \
            Model/Reading/HumidityReading.h \
            Model/Reading/TemperatureReading.h \
            Model/Reading/RainReading.h \
            Model/Reading/WindReading.h \
            Model/Reading/ReadingVisitor.h \
            Model/Reading/ReadingFactory.h \
            Model/Reading/TypeReadingVisitor.h \
            Model/Reading/ReadingTable.h \
            Model/Reading/ReadingList.h \
            Model/Reading/ReadingSeries.h \
            Model/Reading/TableContainer.h \
            Model/Tree/TreeNode.h \
            Model/Tree/LeafNode.h \
            Model/Tree/Tree.h \
            Model/Tree/NodeList.h \
            Model/Environment.h \
            Model/TypeRegistrar.h \
            Model/Observer.h \
            Model/Subject.h \
            View/DTreeView.h \
            View/MainWindow.h \
            View/SensorShow.h \
            View/IconVisitor.h \
            View/TreeWidget.h \
            View/ResultsWidget.h \
            View/ReadingListWidget.h \
            View/ReadingDisplayWidget.h \
            View/TableContainerWidget.h \
            View/ReadingChart.h \
            View/ChartView.h \
            View/NodesWidget.h


SOURCES +=  Model/Sensor/BaseSensor.cpp \
            Model/Sensor/SensorFactory.cpp \
            Model/Sensor/TypeSensorVisitor.cpp \
            Model/Sensor/RainSensor.cpp \
            Model/Sensor/DustSensor.cpp \
            Model/Sensor/HumiditySensor.cpp \
            Model/Sensor/TemperatureSensor.cpp \
            Model/Sensor/WindSensor.cpp \
            Model/Reading/Reading.cpp \
            Model/Reading/DustReading.cpp \
            Model/Reading/HumidityReading.cpp \
            Model/Reading/TemperatureReading.cpp \
            Model/Reading/RainReading.cpp \
            Model/Reading/WindReading.cpp \
            Model/Reading/ReadingFactory.cpp \
            Model/Reading/TypeReadingVisitor.cpp \
            Model/Reading/ReadingTable.cpp \
            Model/Reading/ReadingList.cpp \
            Model/Reading/ReadingSeries.cpp \
            Model/Reading/TableContainer.cpp \
            Model/Tree/TreeNode.cpp \
            Model/Tree/LeafNode.cpp \
            Model/Tree/Tree.cpp \
            Model/Tree/NodeList.cpp \
            Model/Environment.cpp \
            Model/TypeRegistrar.cpp \
            Model/Subject.cpp \
            View/DTreeView.cpp \
            View/MainWindow.cpp \
            View/SensorShow.cpp \
            View/IconVisitor.cpp \
            View/TreeWidget.cpp \
            View/NodesWidget.cpp \
            View/ReadingListWidget.cpp \
            View/ReadingDisplayWidget.cpp \
            View/TableContainerWidget.cpp \
            View/ResultsWidget.cpp \
            View/ReadingChart.cpp \
            View/ChartView.cpp \
            main.cpp

RESOURCES += \
              src.qrc