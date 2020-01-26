#ifndef BSF_DETECTIONSENSORFORM_H
#define BSF_DETECTIONSENSORFORM_H

#include <QWidget>
#include <domain/detectionsensor.h>

namespace Ui {
    class DetectionSensorForm;
}

class DetectionSensorForm: public QWidget {

    Q_OBJECT

public:

    DetectionSensorForm(QWidget *parent, const Qt::WindowFlags  &f, DetectionSensor&);
    virtual ~DetectionSensorForm();
    bool getDeviceState();

public slots:
    void setDetectionSensorState(IODevice::IO_DEVICE_HIGH_LOW);

private:
    DetectionSensor detectionSensor;
    Ui::DetectionSensorForm *ui = nullptr;

};
#endif //BSF_DETECTIONSENSORFORM_H
