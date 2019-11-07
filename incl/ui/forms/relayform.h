#ifndef BSF_RELAYFORM_H
#define BSF_RELAYFORM_H

#include <incl/controller/relaycontroller.h>
#include "ui_testrelaywidget.h"

class RelayForm : public QWidget {
    Q_OBJECT

public:
    explicit RelayForm(RelayController relayController, QWidget *parent = nullptr);
    void createItems();
    void initWidget(stateAction &stateAction);

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
#endif //BSF_RELAYFORM_H