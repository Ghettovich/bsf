#ifndef BSF_IODEVICETAB_H
#define BSF_IODEVICETAB_H

#include <service/iodeviceservice.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

class IODeviceTab : public QWidget
{
    Q_OBJECT

public:
    IODeviceTab(QWidget * parent, const Qt::WindowFlags &f);

public slots:
    void updateIODeviceTypes(int);

private:
    IODeviceService ioDeviceService;
    QHBoxLayout *hbox = nullptr;

    DeviceActionForm * devForm = nullptr;
    IODeviceForm * ioDevForm = nullptr;
};
#endif // BSF_IODEVICESTAB_H
