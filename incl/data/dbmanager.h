#include <QString>
#include <QtSql/QSqlDatabase>
#include "arduino.h"

#ifndef BSF_DBMANAGER_H
#define BSF_DBMANAGER_H
class DbManager {

public:
    DbManager(const QString& path);
    QList<arduino> getAllActiveArduino();

private:
    QSqlDatabase m_db;
};
#endif //BSF_DBMANAGER_H
