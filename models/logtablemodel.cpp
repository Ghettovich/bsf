#include "headers/models/logtablemodel.h"

LogTableModel::LogTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

LogTableModel::LogTableModel(const QVector<Log> &logs, QObject *parent)
    : QAbstractTableModel(parent),
      logs(logs)
{
}

int LogTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : logs.size();
}

int LogTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}

QVariant LogTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= logs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &log = logs.at(index.row());

        switch (index.column()) {
            case 0:
                return log.id;
            case 1:
                return log.title;
            case 2:
                return log.severity;
            case 3:
                return log.msg;
            default:
                break;
        }
    }
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
                return tr("id");
            case 1:
                return tr("title");
            case 2:
                return tr("severity");
            case 3:
                return tr("msg");
            default:
                break;
        }
    }
    return QVariant();
}

bool LogTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        logs.insert(position, { QString(), QString(), QString(), QString() });

    endInsertRows();
    return true;
}

bool LogTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto log = logs.value(row);

        switch (index.column()) {
            case 0:
                log.id = value.toString();
                break;
            case 1:
                log.title = value.toString();
                break;
            case 2:
                log.severity = value.toString();
                break;
            case 3:
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

Qt::ItemFlags LogTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const QVector<Log> &LogTableModel::getLogs() const
{
    return logs;
}

