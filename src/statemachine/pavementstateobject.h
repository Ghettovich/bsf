#ifndef BSF_PAVEMENTSTATEOBJECT_H
#define BSF_PAVEMENTSTATEOBJECT_H

#include <QObject>
#include <domain/iodevice.h>
#include <dto/iodevicedto.h>
#include <domain/weightcensor.h>

class PavementStateObject : public QObject {

    Q_OBJECT

public:
    explicit PavementStateObject();
    Recipe *getRecipe() const;
    void setRecipe(Recipe *_recipe);

    QList<IODevice *> getIoDeviceList() const;
    void setIoDeviceList(QList<IODevice *> _ioDeviceList);

    QList<IODevice *> getIoDeviceWeightStationList() const;
    void setIoDeviceListWeightStation(QList<IODevice *> _ioDeviceList);

    QList<WeightCensor *> getWeightSensorList() const;
    void setWeightSensorList(QList<WeightCensor *>);

private:
    Recipe *recipe = nullptr;
    QList<IODevice *> ioDeviceList = QList<IODevice *>();
    QList<IODevice *> ioDeviceWeightStationList = QList<IODevice *>();
    QList<WeightCensor *> weightSensorList = QList<WeightCensor *>();

public slots:
    void updateIODevicesWithDto(const QList<IODeviceDTO *>&);
    void updateWeightSensorList(int, int, int);
};
#endif //BSF_PAVEMENTSTATEOBJECT_H
