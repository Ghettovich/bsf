#include "incl/ui/forms/relayform.h"

RelayForm::RelayForm(RelayController relayController, QWidget *parent) :
        relayController(relayController),
        QWidget(parent) {
    ui.setupUi(this);
    createItems();
}

void RelayForm::createItems() {
    this->lblRelayDescription = ui.label;
    this->btnHigh = ui.pushButtonHigh;
    this->btnLow = ui.pushButtonLow;
    this->response = ui.plainTextEdit;
    // Plain Text Set Properties
    response->setEnabled(false);
    response->setReadOnly(true);
    // Push Button Click Events
    connect(btnHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(btnLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::defaultButtonState() {
    btnLow->setEnabled(false);
    btnLow->setText(QStringLiteral("%1 LOW").arg(action.code));
    btnHigh->setEnabled(false);
    btnHigh->setText(QStringLiteral("%1 HIGH").arg(action.code));
}

void RelayForm::initWidget(stateAction &stateAction) {
    this->action = stateAction;
    lblRelayDescription->setText(stateAction.description);
    defaultButtonState();
}

void RelayForm::onClickBtnLow() {

}

void RelayForm::onClickBtnHigh() {

}
