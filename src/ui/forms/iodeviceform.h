#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <arduino.h>
#include <iodevicetype.h>
#include <weightcensor.h>
#include <forms/relayform.h>
#include <forms/weightsensorform.h>
#include <forms/detectionsensorform.h>
#include <networkservice.h>
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QWidgetList>
#include <QtWidgets/QGridLayout>
#include <socketmanager/tcpserver.h>


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
