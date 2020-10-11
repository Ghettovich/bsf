#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <domain/arduino.h>
#include <domain/iodevicetype.h>
#include <domain/weightcensor.h>
#include <ui/forms/relayform.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/detectionsensorform.h>
#include <service/networkservice.h>
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QWidgetList>
#include <QtWidgets/QGridLayout>
#include <service/socketmanager/tcpserver.h>


namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {
Q_OBJECT

public:
    IODeviceForm(QWidget *parent, const Qt::WindowFlags &f);
    virtual ~IODeviceForm();
    void onCreateArduinoDeviceTypeIOComboBox(Arduino&, QVector<IODeviceType>);
    bool isIODeviceListEmpty();

private:
    Arduino arduino;
    IODeviceType selectedIODeviceType;
    QVector<IODevice *> ioDeviceList;
    QVector<IODeviceType> ioDeviceTypeList;
    QList<RelayForm *> relayWidgetList;
    QList<WeightSensorForm *> weightSensorWidgetList;
    QList<DetectionSensorForm *> detetectionSensorWidgetList;

    //PayloadService payloadService;
    NetworkService networkService;
    QVBoxLayout *vbox = nullptr;
    QGridLayout *grid = nullptr;

    LocalTcpServer localSocket;

    Ui::IODeviceForm *ui;
    void createIODeviceWidgets();
    void updateWidgetsWithState();
    void killChildWidgets();

public slots:
    void onCreateIODeviceTypeFormList(int index);
    void onToggleRelayWithId(int id);
    void onBroadcastRecipe(const Recipe& recipe);
    void onUpdateWeightSensor(IODevice*, Arduino::ARDUINO_STATE);
    void onUpdateIODeviceWidgets(int, Arduino::ARDUINO_STATE,const QVector<IODevice *>&);

};
#endif //BSF_IODEVICEFORM_H
