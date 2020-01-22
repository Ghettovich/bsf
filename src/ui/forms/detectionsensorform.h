#ifndef BSF_DETECTIONSENSORFORM_H
#define BSF_DETECTIONSENSORFORM_H

#include <QWidget>
#include <domain/iodevice.h>

namespace Ui {
    class DetectionSensorForm;
}

class DetectionSensorForm: public QWidget {

    Q_OBJECT

public:

    DetectionSensorForm(QWidget *parent, const Qt::WindowFlags  &f, const IODevice& ioDevice);
    virtual ~DetectionSensorForm();
    bool getDeviceState();

public slots:
    void setDetectionSensorState(int state);

private:
    IODevice ioDevice;
    Ui::DetectionSensorForm *ui = nullptr;

};
#endif //BSF_DETECTIONSENSORFORM_H
