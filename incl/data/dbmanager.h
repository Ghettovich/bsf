#include <QString>
#include <QtSql/QSqlDatabase>
#include "incl/domain/arduino.h"

#ifndef BSF_DBMANAGER_H
#define BSF_DBMANAGER_H


class DbManager {

public:
    DbManager(const QString& path);
    QList<arduino> getAllActiveArduino();
    void updateArduino(const arduino &arduinoDevice);

private:
    QSqlDatabase m_db;
};
#endif //BSF_DBMANAGER_H
