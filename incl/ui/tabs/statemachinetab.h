#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <incl/statemachine/bsfpavementmachine.h>
#include <incl/repo/iodevicerepo.h>
#include <incl/repo/reciperepo.h>
#include <incl/service/payloadservice.h>

class StateMachineTab : public QTabWidget {

    Q_OBJECT

public:
    explicit StateMachineTab(QWidget *parent = nullptr);

private:
    QList<Recipe> recipeList;
    QList<IODevice *> ioDeviceList;
    IODeviceRepository *ioDeviceRepository = nullptr;
    RecipeRepository * recipeRepository = nullptr;
    PayloadService * payloadService = nullptr;
    QComboBox *comboBoxRecipe = nullptr;
    BsfPavementMachine *pavementMachine;
    QPushButton * btnIncrementWeight = nullptr;
    QPushButton * btnDecreaseWeight = nullptr;
    QPushButton * btnStart = nullptr;

    void createRecipeComboBox();

private slots:
    void onStart();
    void onIncrementWeight();
    void onDecreaseWeight();
    void onSelectRecipeCombobox(int comboBoxItemId);
    void onActivtedRecipeCombobox(int comboBoxItemId);
    void onReceiveIODeviceDtoList(const QList<IODeviceDTO *>&);

};
#endif //BSF_STATEMACHINETAB_H
