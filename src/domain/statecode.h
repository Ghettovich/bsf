#ifndef BSF_STATECODE_H
#define BSF_STATECODE_H

#include <QObject>
#include <QtCore/QString>

class StateCode {

    Q_GADGET

public:
    enum StateReplyEnum {
        UNKNOWN, READY, LIFT_ASC, LIFT_DESC, BIN_LOADING, BIN_DUMPING, LIFT_STUCK, BIN_STUCK
    };
    Q_ENUM(StateReplyEnum);

    StateCode(int id = 0);
    int getId() const;
    void setId(int id);
    StateReplyEnum getStateReplyEnum() const;
    void setStateReplyEnum(StateReplyEnum stateReplyEnum);
    const QString &getMessage() const;
    void setMessage(const QString &_message);

private:
    int id;
    StateReplyEnum stateReplyEnum;
    QString message;




};

#endif //BSF_STATECODE_H
