
#ifndef BSF_TABLECOMPONENTMODEL_H
#define BSF_TABLECOMPONENTMODEL_H

#include <QtCore/QAbstractTableModel>
#include <domain/component.h>

struct ComponentTableStruct
{
    QVariant componentId;
    QString component;
    QVariant targetWeight;
    QVariant actualWeight;

    bool operator==(const ComponentTableStruct &other) const
    {
        return component == other.component;
    }
};

inline QDataStream &operator<<(QDataStream &stream, const ComponentTableStruct &contact)
{
    return stream << QVariant(contact.componentId) << contact.component << QVariant(contact.targetWeight).toString() << QVariant(contact.actualWeight);
}

inline QDataStream &operator>>(QDataStream &stream, ComponentTableStruct &contact)
{
    return stream >> contact.componentId >> contact.component >> contact.targetWeight >> contact.actualWeight;
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

private:
    QVector<Component> components;
    QVector<ComponentTableStruct> componentsTableStruct;

    void initTableStruct();

};


#endif //BSF_TABLECOMPONENTMODEL_H
