#include "persontreemodel.h"

PersonTreeModel::PersonTreeModel(QObject* parent):
    QAbstractItemModel(parent)
{}


QModelIndex PersonTreeModel::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex PersonTreeModel::parent(const QModelIndex &child) const
{
}

int PersonTreeModel::rowCount(const QModelIndex &parent) const
{
}

int PersonTreeModel::columnCount(const QModelIndex &parent) const
{
}

QVariant PersonTreeModel::data(const QModelIndex &index, int role) const
{
}
