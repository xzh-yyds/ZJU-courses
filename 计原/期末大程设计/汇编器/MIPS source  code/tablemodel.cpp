#include "tablemodel.h"
#include <iostream>

using namespace  std;

TableModel::TableModel(Data _list, QObject *parent) : QAbstractTableModel(parent), list(_list)
{
}

int TableModel::rowCount(const QModelIndex & /* parent */) const
{
    return list.count();
}

int TableModel::columnCount(const QModelIndex & /* parent */) const
{
    return list[0].count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter);
    } else if (role == Qt::DisplayRole) {
        return list[index.row()][index.column()];
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(Qt::DisplayRole != role) {
        return QVariant();
    }
    if(orientation == Qt::Horizontal) {
        if (section == 0)
            return QString("Address");
        return section;
    }
    return QVariant();
}
