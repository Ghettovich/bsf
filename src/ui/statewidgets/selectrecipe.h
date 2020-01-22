#ifndef BSF_SELECTRECIPE_H
#define BSF_SELECTRECIPE_H

#include <domain/recipe.h>
#include <domain/iodevice.h>
#include <repo/iodevicerepo.h>
#include <repo/reciperepo.h>
#include <ui/forms/detectionsensorform.h>
#include <ui/forms/relayform.h>

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGroupBox>




class SelectRecipe : public QWidget {

    struct SelectRecipeConf {
        int arduinoId = 1;
        int deviceIdArray[2] = {6, 7};
    };

public:
    SelectRecipe(QWidget *parent, const Qt::WindowFlags &f);

private:
    Recipe selectedRecipe;
    QVector<Recipe> recipeList;
    QVector<IODevice> ioDeviceList;

    QHBoxLayout *hbox = nullptr;

    QGroupBox * grpboxSelectRecipe = nullptr;
    QComboBox * comboBoxRecipe = nullptr;
    DetectionSensorForm *binLoadedDetectionSensorForm = nullptr;
    RelayForm *relayFormLiftDown = nullptr;
    QPushButton *btnStart = nullptr;

    void fillRecipeComboBox();
    void createSelectRecipeGroupBox();

public slots:
    void onClickContinue();
    void onSelectRecipeCombobox(int index);
    //void onReceiveFoundWeightStation(const QByteArray &);
};


#endif //BSF_SELECTRECIPE_H
