#include "persontreemodel.h"

PersonTreeModel::PersonTreeModel(PersonTreeNode_ptr root, QObject* parent):
    QAbstractItemModel(parent),
    m_root(root)
{}


QModelIndex PersonTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // hasIndex checks if the values are in the valid ranges by using
    // rowCount and columnCount
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    // In order to create an index we first need to get a pointer to the Item
    // To get started we have either the parent index, which contains a pointer
    // to the parent item, or simply the root item

    PersonTreeNode_ptr parentItem = parent.isValid()
                           ? static_cast<PersonTreeNode_ptr>(parent.internalPointer())
                           : m_root;

    // We can now simply look up the item we want given the parent and the row
    PersonTreeNode_ptr childItem = (*parentItem)[row];

    // There is no public constructor in QModelIndex we can use, instead we need
    // to use createIndex, which does a little bit more, like setting the
    // model() in the QModelIndex to the model that calls createIndex
    return createIndex(row, column, childItem);
}

QModelIndex PersonTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    // Simply get the parent pointer and create an index for it
    PersonTreeNode_ptr parentItem = static_cast<PersonTreeNode_ptr>(child.internalPointer())->parent();
    return parentItem == m_root
               ? QModelIndex() // the root doesn't have a parent
               : createIndex(parentItem->rowInParent(), 0, parentItem);
}

int PersonTreeModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ?
        static_cast<PersonTreeNode_ptr>(parent.internalPointer())->childrenCount()
                            : m_root->childrenCount();
}

int PersonTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant PersonTreeModel::data(const QModelIndex &index, int role) const
{
    // Usually there will be more stuff here, like type conversion from
    // QVariant, handling more roles etc.
    qDebug() << "Treemodel; data with index ="
             << index << "and role=" << role;
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    PersonTreeNode_ptr item = static_cast<PersonTreeNode_ptr>(index.internalPointer());
    return item->value();
}
