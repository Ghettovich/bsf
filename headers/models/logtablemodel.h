#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QAbstractTableModel>


struct Log
{
    QString title;
    QString msg;
    QString timestamp;
    qint16 severity;
};


inline QDataStream &operator<<(QDataStream &stream, const Log &log)
{
    // ToDo check if cast is valid
    return stream << log.title << log.msg; //<< log.timestamp << QString::number(log.severity);
}

inline QDataStream &operator>>(QDataStream &stream, Log &log)
{
    return stream >> log.title >> log.msg;
}

class LogTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    LogTableModel(QObject *parent = nullptr);
    LogTableModel(const QVector<Log> &logs, QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    //Qt::ItemFlags flags(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    const QVector<Log> &getLogs() const;

private:
    QVector<Log> logs;
};
#endif // LOGMODEL_H


