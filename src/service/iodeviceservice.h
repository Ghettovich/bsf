#ifndef BSF_IODEVICESERVICE_H
#define BSF_IODEVICESERVICE_H

#include <ui/forms/deviceform.h>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>
#include <QObject>
#include <QtWidgets/QHBoxLayout>

class IODeviceService : public QObject  {

    Q_OBJECT

public:
    explicit IODeviceService(QObject *parent, const QString& connection = "");
    void createArduinoDeviceWidgetList(QHBoxLayout *layout);
    void createDeviceActionForm(DeviceActionForm *parent);
    void createIODeviceForm(IODeviceForm*, Arduino&);
    void updateIODeviceForm(IODeviceForm* form, int);

private:
    bool isDefaultConnection = false;
    QString defaultConnection= "";
};
#endif //BSF_IODEVICESERVICE_H
