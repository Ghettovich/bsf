#ifndef BSF_STATEMACHINETABWIDGET_H
#define BSF_STATEMACHINETABWIDGET_H

#include <arduino.h>
#include <networkservice.h>
#include <statewidgets/statemachinepage.h>
#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class StatemachineTabWidget : public QTabWidget {

Q_OBJECT

public:
    explicit StatemachineTabWidget(QWidget *parent);
    void createStatemachinePage();
    void createWeightSensorPage();

private:
    StateMachinePage *statemachinePageWidget = nullptr;
    QWidget *statemachinePage = nullptr;
    QWidget *weightSensorPage = nullptr;
    QWidget *detectionSensorPage = nullptr;
    QWidget *bunkerPage = nullptr;
    QWidget *relayPage = nullptr;

    NetworkService *networkService = nullptr;
//    PayloadService *payloadService = nullptr;

    void createTabWdigetPages();

public slots:

    void onTabWdigetCurrentChanged(int);

    void onRequestIODeviceState(const Arduino&);

    void updateArduinoWithIODeviceList(int, Arduino::ARDUINO_STATE, const QVector<IODevice *> &);
};


#endif //BSF_STATEMACHINETABWIDGET_H
