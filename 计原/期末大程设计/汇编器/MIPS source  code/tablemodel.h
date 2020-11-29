#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QAbstractTableModel>

typedef QList<QStringList> Data;

class TableModel : public QAbstractTableModel
{
public:
    TableModel(Data _list, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    Data list;
};

#endif // TABLEMODEL_H
