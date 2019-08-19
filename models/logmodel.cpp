#include <headers/models/logtablemodel.h>

LogTableModel::LogTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

LogTableModel::LogTableModel(const QVector<Log> &logs, QObject *parent)
    : QAbstractTableModel(parent),
      logs(logs)
{
}

int LogTableModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 2;
}

int LogTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant LogTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);

    return QVariant();
}

//! [3]
QVariant LogTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Address");
            default:
                break;
        }
    }
    return QVariant();
}
//! [3]

bool LogTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto log = logs.value(row);

        switch (index.column()) {
            case 0:
                log.title = value.toString();
                break;
            case 1:
                log.msg = value.toString();
                break;
            default:
                return false;
        }
        logs.replace(row, log);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
}

const QVector<Log> &LogTableModel::getLogs() const
{
    return logs;
}
