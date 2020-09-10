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
    explicit IODeviceService(QObject *parent, const QString& _connection = "");
    void createArduinoDeviceWidgetList(QHBoxLayout *layout);
    void createDeviceActionForm(DeviceActionForm *parent);
    void createIODeviceForm(IODeviceForm*, Arduino&);
    void updateIODeviceForm(IODeviceForm* form, int);

private:
    QString connection= "";
};
#endif //BSF_IODEVICESERVICE_H
