#ifndef BSF_DETECTIONSENSORFORM_H
#define BSF_DETECTIONSENSORFORM_H

#include <QWidget>
#include <incl/domain/iodevice.h>

namespace Ui {
    class DetectionSensorForm;
}

class DetectionSensorForm: public QWidget {

    Q_OBJECT

public:
    explicit DetectionSensorForm(QWidget *parent = nullptr, IODevice *_ioDevice = nullptr);
    virtual ~DetectionSensorForm();

public slots:
    void onSensorChange(QChar isLow);

private:
    IODevice *ioDevice = nullptr;
    Ui::DetectionSensorForm *ui = nullptr;

};
#endif //BSF_DETECTIONSENSORFORM_H
