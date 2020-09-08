#ifndef BSF_STATEMACHINEPAGE_H
#define BSF_STATEMACHINEPAGE_H

#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <service/networkservice.h>
#include <service/payloadservice.h>
#include <QObject>
#include <QtWidgets/QGroupBox>
#include <QtCore/QStringList>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QFormLayout>


class StateMachinePage : public QWidget {

Q_OBJECT

private:
    int gridColumnCount = 0, gridRowCount = 0;
    const int arduinoBinAndLiftId = 1, arduinoWeightstationId = 2;
    QVector<Arduino *> arduinoList;
    QGridLayout *gridLayout = nullptr;
    QWidget *defaultPage = nullptr;
    QWidget *weightSensorPage = nullptr;
    QWidget *detectionSensorPage = nullptr;
    QWidget *bunkerPage = nullptr;
    QWidget *relayPage = nullptr;

    Arduino arduinoBinAndLift;
    QGroupBox *binAndLiftGroupBox = nullptr;
    QFormLayout *arduinoBinAndLiftFormLayout = nullptr;
    QPushButton *btnStatusBinAndLift = nullptr;

    Arduino arduinoWeightstation;
    QGroupBox *weightstationGroupBox = nullptr;
    QFormLayout *arduinoWeightstationFormLayout = nullptr;
    QPushButton *btnStatusArduino2 = nullptr;

    QTabWidget *tabWidgetIODevices = nullptr;
    NetworkService *networkService = nullptr;
    PayloadService *payloadService = nullptr;

    void createArduinoBinAndLiftGroupBox();

    void updateArduinoBinAndLiftGroupBox(Arduino::ARDUINO_STATE);

    void createArduinoWeightstationGroupBox();

    void updateArduinoWeightstationGroupBox();

    void createTabwidgetIODevices();

    void createDefaultPage();

    void addIODevicesToGrid(QFormLayout *grid, Arduino);

    void createDetectionSensorPage();

    void deleteChildrenFromGrid();

public:
    StateMachinePage(QVBoxLayout *layout, const Qt::WindowFlags &f);

public slots:

    void onChangeIndexTabWidgetIODevices(int);

    void updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE, const QVector<IODevice *> &);

};

#endif //BSF_STATEMACHINEPAGE_H
