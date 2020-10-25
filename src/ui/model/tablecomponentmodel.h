
#ifndef BSF_TABLECOMPONENTMODEL_H
#define BSF_TABLECOMPONENTMODEL_H

#include <component.h>
#include <QtCore/QAbstractTableModel>

struct ComponentTableStruct {
    QVariant componentId;
    QString component;
    QVariant targetWeight;
    QVariant actualWeight;
    QVariant marginValue;

    bool operator==(const ComponentTableStruct &other) const {
        return component == other.component;
    }

    bool isActualWeightInValidRange() const {
        int marginWeight = (targetWeight.toInt() / 100) * marginValue.toInt();

        printf("\nMargin weight = %d", marginWeight);

        if (actualWeight.toInt() <= targetWeight.toInt() + marginWeight) {
            if(actualWeight.toInt() >= targetWeight.toInt() - marginWeight) {
                return true;
            }
        } else if(actualWeight.toInt() >= targetWeight.toInt() - marginWeight) {
            if(actualWeight.toInt() <= targetWeight.toInt() + marginWeight) {
                return true;
            }
        }

        return false;
    }

    bool isActualWeightGreaterThenTarget() {
        return actualWeight.toInt() > targetWeight.toInt();
    }

    bool isActualWeightLessThenTarget() {
        return actualWeight.toInt() < targetWeight.toInt();
    }
};

inline QDataStream &operator<<(QDataStream &stream, const ComponentTableStruct &contact) {
    return stream << QVariant(contact.componentId) << contact.component << QVariant(contact.targetWeight).toString()
                  << QVariant(contact.actualWeight) << QVariant(contact.marginValue);
}

inline QDataStream &operator>>(QDataStream &stream, ComponentTableStruct &contact) {
    return stream >> contact.componentId >> contact.component >> contact.targetWeight >> contact.actualWeight
                  >> contact.marginValue;
}

class TableComponentModel : public QAbstractTableModel {
Q_OBJECT

public:
    explicit TableComponentModel(QObject *parent = nullptr);

    explicit TableComponentModel(const QVector<Component> &components, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    const QVector<ComponentTableStruct> &getComponents() const;

    void updateComponentsInTable(const QMap<int, int> &currentComponentMap);

    enum TABLE_HEADERS {
        ID = 0,
        COMPONENT_NAME = 1,
        COMPONENT_TARGET_WEIGHT = 2,
        COMPONENT_CURRENT_WEIGHT = 3,
        COMPONENT_MARGIN_VALUE = 4
    };

private:
    QVector<Component> components;
    QVector<ComponentTableStruct> componentsTableStruct;

    void initTableStruct();

};


#endif //BSF_TABLECOMPONENTMODEL_H
