#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include <QAbstractTableModel>


struct Log
{
    QString id;
    QString title;
    QString severity;
    QString msg;

    bool operator==(const Log &other) const
    {
        return msg == other.msg && title == other.title;
    }
};


inline QDataStream &operator<<(QDataStream &stream, const Log &log)
{
    // ToDo check if cast is valid
    return stream << log.id << log.title << log.severity << log.msg; //<< log.timestamp << QString::number(log.severity);
}

inline QDataStream &operator>>(QDataStream &stream, Log &log)
{
    return stream >> log.id >> log.title >> log.severity >> log.msg;
}

class LogTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    LogTableModel(QObject *parent = nullptr);
    LogTableModel(const QVector<Log> &logs, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int ) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    const QVector<Log> &getLogs() const;

private:
    QVector<Log> logs;
    void createSampleData();
};
#endif // LOGTABLEMODEL_H


