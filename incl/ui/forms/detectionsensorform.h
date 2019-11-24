#ifndef BSF_DETECTIONSENSORFORM_H
#define BSF_DETECTIONSENSORFORM_H

#include <incl/domain/iodevice.h>

namespace Ui {
    class DetectionSensorForm;
}

class DetectionSensorForm: public QWidget {

public:
    explicit DetectionSensorForm(QWidget *parent = nullptr, IODevice *_ioDevice = nullptr);
    virtual ~DetectionSensorForm();

private:
    IODevice *ioDevice = nullptr;
    Ui::DetectionSensorForm *ui = nullptr;

};
#endif //BSF_DETECTIONSENSORFORM_H
