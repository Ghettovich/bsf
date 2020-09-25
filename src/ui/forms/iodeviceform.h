#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <domain/arduino.h>
#include <domain/iodevicetype.h>
#include <domain/weightcensor.h>
#include <ui/forms/relayform.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/detectionsensorform.h>
#include <service/payloadservice.h>
#include <service/networkservice.h>
#include <QtWidgets/QWidget>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QWidgetList>
#include <QtWidgets/QGridLayout>


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

    PayloadService payloadService;
    NetworkService networkService;
    QVBoxLayout *vbox = nullptr;
    QGridLayout *grid = nullptr;

    Ui::IODeviceForm *ui;
    void createIODeviceWidgets();
    void updateWidgetsWithState();
    void killChildWidgets();

public slots:
    void onCreateIODeviceTypeFormList(int index);
    void onSendRequest(const QUrl&);
    void onUpdateWeightSensor(IODevice*, Arduino::ARDUINO_STATE);
    void onUpdateIODeviceWidgets(int, Arduino::ARDUINO_STATE,const QVector<IODevice *>&);

signals:
    void createIODeviceTypeFormList(int arduinoId);

};
#endif //BSF_IODEVICEFORM_H
