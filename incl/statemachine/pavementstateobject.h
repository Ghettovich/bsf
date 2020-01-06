#ifndef BSF_PAVEMENTSTATEOBJECT_H
#define BSF_PAVEMENTSTATEOBJECT_H

#include <incl/domain/recipe.h>
#include <incl/domain/iodevice.h>

class PavementStateObject {

public:
    explicit PavementStateObject();
    Recipe *recipe = nullptr;
    QList<IODevice *> ioDeviceList{};

    Recipe *getRecipe() const;
    void setRecipe(Recipe *_recipe);

    QList<IODevice *> getIoDeviceList() const;
    void setIoDeviceList(QList<IODevice *> _ioDeviceList);

};
#endif //BSF_PAVEMENTSTATEOBJECT_H
