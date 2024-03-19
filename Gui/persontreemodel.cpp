#include "persontreemodel.h"

PersonTreeModel::PersonTreeModel(QObject* parent):
    QAbstractItemModel(parent)
{}


QModelIndex PersonTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex PersonTreeModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int PersonTreeModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int PersonTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant PersonTreeModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
