#ifndef BSF_STATECODE_H
#define BSF_STATECODE_H

#include <QtCore/QString>

struct StateCode {
    int id;
    QString message;
};

enum StateCodeEnum {
    READY = 0, LIFT_ASC = 1, LIFT_DESC = 2, BIN_LOADING = 3, BIN_DUMPING = 4, LIFT_STUCK = 90, BIN_STUCK = 91
};
#endif //BSF_STATECODE_H
