#ifndef BSF_STATEMACHINEPAGE_H
#define BSF_STATEMACHINEPAGE_H

#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <repo/arduinorepo.h>
#include <service/networkservice.h>
#include <QObject>
#include <QtCore/QStringList>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QFormLayout>
#include <service/payloadservice.h>


class StateMachinePage : public QWidget {

    Q_OBJECT

private:
    QVector<Arduino *> arduinoList;
    QGridLayout *gridLayout = nullptr;
    QWidget * defaultPage = nullptr;
    QWidget * weightSensorPage = nullptr;
    QWidget * detectionSensorPage = nullptr;
    QWidget * bunkerPage = nullptr;
    QWidget * relayPage = nullptr;
    QStringList tabNames = {"Start", "Weegcellen", "Sensoren", "Relay", "Bunkers"};
    QTabWidget *tabWidgetIODevices = nullptr;
    NetworkService *networkService = nullptr;
    PayloadService *payloadService = nullptr;

    void createTabwidgetIODevices();
    void createDefaultPage();
    void addIODevicesToGrid(QFormLayout *grid, Arduino);
    void createDetectionSensorPage();
    void deleteChildrenFromGrid();

public:
    StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f);

public slots:
    void onChangeIndexTabWidgetIODevices(int);
    void updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);

};

#endif //BSF_STATEMACHINEPAGE_H
