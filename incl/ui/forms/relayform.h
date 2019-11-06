#include <incl/controller/relaycontroller.h>
#include <incl/domain/action.h>
#include "ui_testrelaywidget.h"

#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#endif //BSF_RELAYFORM_H

class RelayForm : public QWidget {
    Q_OBJECT

public:
    explicit RelayForm(RelayController relayController, QWidget *parent = nullptr);
    void createItems();
    void initWidget(stateAction &stateAction);

public slots:


private:
    Ui::bsfTestRelayWidget ui{};
    RelayController relayController;
    stateAction action;

    QLabel *lblRelayDescription{};
    QPushButton *btnLow{};
    QPushButton *btnHigh{};
    QPlainTextEdit *response{};

    void defaultButtonState();
    void onClickBtnLow();
    void onClickBtnHigh();

};