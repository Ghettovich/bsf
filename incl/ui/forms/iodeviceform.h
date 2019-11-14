#ifndef BSF_IODEVICEFORM_H
#define BSF_IODEVICEFORM_H

#include <incl/domain/iodevicetype.h>
#include <incl/domain/arduino.h>
#include <incl/domain/iodevice.h>
#include <incl/repo/iodevicerepo.h>

namespace Ui {
    class IODeviceForm;
}

class IODeviceForm : public QWidget {

public:
    explicit IODeviceForm(QWidget *_parent = nullptr, Arduino *_arduino = nullptr);
    virtual ~IODeviceForm();

private:
    QList<IODeviceType> ioDeviceTypeList;
    QList<IODevice> ioDeviceList;
    IODeviceRepository *ioDeviceRepository = nullptr;
    Arduino *arduino = nullptr;
    QWidget *parent = nullptr;
    Ui::IODeviceForm *ui;

    void createArduinoDeviceTypeIOComboBox();

};
#endif //BSF_IODEVICEFORM_H
