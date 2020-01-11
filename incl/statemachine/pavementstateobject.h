#ifndef BSF_PAVEMENTSTATEOBJECT_H
#define BSF_PAVEMENTSTATEOBJECT_H

#include <QObject>
#include <incl/domain/recipe.h>
#include <incl/domain/iodevice.h>
#include <incl/dto/iodevicedto.h>

class PavementStateObject : public QObject {

    Q_OBJECT

public:
    explicit PavementStateObject();
    Recipe *getRecipe() const;
    void setRecipe(Recipe *_recipe);

    QList<IODevice *> getIoDeviceList() const;
    void setIoDeviceList(QList<IODevice *> _ioDeviceList);

private:
    Recipe *recipe = nullptr;
    QList<IODevice *> ioDeviceList = QList<IODevice *>();

public slots:
    void updateIODevicesWithDto(const QList<IODeviceDTO *>&);
};
#endif //BSF_PAVEMENTSTATEOBJECT_H
