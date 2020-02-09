#include "statecode.h"
#include <QMetaEnum>

StateCode::StateCode(int id) : id(id), stateReplyEnum(StateReplyEnum(UNKNOWN)) {
}

int StateCode::getId() const {
    return id;
}

StateCode::StateReplyEnum StateCode::getStateReplyEnum() const {
    return stateReplyEnum;
}

void StateCode::setStateReplyEnum(StateCode::StateReplyEnum _stateReplyEnum) {
    stateReplyEnum = StateReplyEnum(_stateReplyEnum);
}

const QString &StateCode::getMessage() const {
    return message;
}
void StateCode::setMessage(const QString &_message) {
    message = _message;
}
