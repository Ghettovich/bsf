#ifndef BSF_ERRORCODE_H
#define BSF_ERRORCODE_H

#include <QtCore/QString>

struct ErrorCode {
    int id;
    QString message;
};

enum ErrorCodeEnum { LIFT_STUCK = 90, BIN_STUCK = 91 };
#endif //BSF_ERRORCODE_H
