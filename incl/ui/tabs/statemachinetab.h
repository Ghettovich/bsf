#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <incl/statemachine/bsfpavementmachine.h>
#include <incl/repo/iodevicerepo.h>
#include <incl/repo/reciperepo.h>
#include <incl/service/payloadservice.h>
#include <incl/ui/forms/detectionsensorform.h>
#include <incl/ui/forms/relayform.h>
#include <incl/ui/forms/weightsensorform.h>

class StateMachineTab : public QTabWidget {

    Q_OBJECT

public:
    explicit StateMachineTab(QWidget *parent = nullptr);

private:
    int sensorWeightId = 1, sensorLiftDropId = 5, sensorLiftLoadId = 6, relayLiftUpId = 7, relayLiftDownId = 8;
    PayloadService payloadService;
    QList<Recipe> recipeList;
    QList<IODevice *> ioDeviceList;
    IODeviceRepository *ioDeviceRepository = nullptr;
    RecipeRepository * recipeRepository = nullptr;
    QComboBox *comboBoxRecipe = nullptr;
    BsfPavementMachine *pavementMachine;

    QGroupBox * grpboxSelectRecipe = nullptr;
    DetectionSensorForm *binLoadedDetectionSensorForm = nullptr;
    RelayForm *relayFormLiftDown = nullptr;
    QPushButton *btnStart = nullptr;

    QGroupBox * grpboxBinLoading = nullptr;
    RelayForm *relayFormLiftUp = nullptr;
    WeightSensorForm *weightSensorForm = nullptr;
    DetectionSensorForm *binDropDetectionSensorForm = nullptr;

    void fillRecipeComboBox();
    void createSelectRecipeGroupBox();
    void createBinLoadGroupBox();

public slots:
    void onSelectRecipeCombobox(int comboBoxItemId);
    void onReceiveIODeviceDtoList(const QList<IODeviceDTO *>&);
    void onClickStart();
    void onReceiveFoundWeightStation(const QByteArray &);

};
#endif //BSF_STATEMACHINETAB_H
