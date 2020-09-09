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
    QGridLayout *gridLayout = nullptr;

    Arduino arduinoBinAndLift;
    QGroupBox *binAndLiftGroupBox = nullptr;
    QFormLayout *arduinoBinAndLiftFormLayout = nullptr;
    QPushButton *btnStatusBinAndLift = nullptr;

    Arduino arduinoWeightstation;
    QGroupBox *weightstationGroupBox = nullptr;
    QFormLayout *arduinoWeightstationFormLayout = nullptr;
    QPushButton *btnStatusWeightstation = nullptr;

    void createArduinoBinAndLiftGroupBox();

    void updateArduinoBinAndLiftGroupBox(Arduino::ARDUINO_STATE);

    void createArduinoWeightstationGroupBox();

    void updateArduinoWeightstationGroupBox();

    void createArduinoStatusButton(QPushButton*, Arduino::ARDUINO_STATE);

    void addIODevicesToGrid(QFormLayout *grid, Arduino);

    void deleteChildrenFromGrid();

public:
    explicit StateMachinePage(QWidget *parent, const Qt::WindowFlags &f);

    void initializePage();

public slots:

    void updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE, const QVector<IODevice *> &);

signals:
    void requestIODeviceStates(Arduino);
};

#endif //BSF_STATEMACHINEPAGE_H
