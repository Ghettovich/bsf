#include "tablecomponentmodel.h"
#include <QtWidgets/QTableWidgetItem>

TableComponentModel::TableComponentModel(QObject *parent) : QAbstractTableModel(parent) {
}

TableComponentModel::TableComponentModel(const QVector<Component> &components, QObject *parent)
    : QAbstractTableModel(parent),
      components(components) {
    initTableStruct();
}

int TableComponentModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : componentsTableStruct.size();
}

int TableComponentModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 5;
}

QVariant TableComponentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= componentsTableStruct.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &comp = componentsTableStruct.at(index.row());

        switch (index.column()) {
            case 0:
                return comp.componentId;
            case 1:
                return comp.component;
            case 2:
                return comp.targetWeight;
            case 3:
                return comp.actualWeight;
            case 4:
                return comp.marginValue;
            default:
                break;
        }
    }
    return QVariant();
}

QVariant TableComponentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("id");
            case 1:
                return tr("Component");
            case 2:
                return tr("Target");
            case 3:
                return tr("Current");
            case 4:
                return tr("Marge %");
            default:
                break;
        }
    }
    return QVariant();
}

bool TableComponentModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        componentsTableStruct.insert(position, { QVariant(), QString(), QVariant(), QVariant(), QVariant() });

    endInsertRows();
    return true;
}

bool TableComponentModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        componentsTableStruct.removeAt(position);

    endRemoveRows();
    return true;
}

bool TableComponentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto componentTableStruct = componentsTableStruct.value(row);

        switch (index.column()) {
            case 0:
                componentTableStruct.componentId = value.toInt();
            case 1:
                componentTableStruct.component = value.toString();
                break;
            case 2:
                componentTableStruct.targetWeight = value.toInt();
                break;
            case 3:
                componentTableStruct.actualWeight = value.toInt();
                break;
            case 4:
                componentTableStruct.marginValue = value.toInt();
                break;
            default:
                return false;
        }
        componentsTableStruct.replace(row, componentTableStruct);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
}

Qt::ItemFlags TableComponentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

const QVector<ComponentTableStruct> &TableComponentModel::getComponents() const{
    return componentsTableStruct;
}

void TableComponentModel::initTableStruct() {

    for(const auto& comp: components) {
        insertRows(0, 1, QModelIndex());
        QModelIndex index = this->index(0, 0, QModelIndex());
        this->setData(index, comp.getComponentId(), Qt::EditRole);

        index = this->index(0, 1, QModelIndex());
        this->setData(index, comp.getComponent(), Qt::EditRole);

        index = this->index(0, 2, QModelIndex());
        this->setData(index, comp.getTargetWeight(), Qt::EditRole);

        index = this->index(0, 3, QModelIndex());
        this->setData(index, 0, Qt::EditRole);

        index = this->index(0, 4, QModelIndex());
        this->setData(index, comp.getMarginValue(), Qt::EditRole);
    }
}

void TableComponentModel::updateComponentsInTable(const QMap<int, int> &currentComponentMap) {

    for (int i = 0; i < componentsTableStruct.size(); ++i) {

        if(currentComponentMap.contains(componentsTableStruct[i].componentId.toInt())) {
            QModelIndex index = this->index(i, 3);
            this->setData(index, currentComponentMap.value(componentsTableStruct[i].componentId.toInt()));
        }
    }
}


