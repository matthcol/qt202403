#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include <memory>
#include "personm.h"

//! [0]
class TreeItem
{
public:
    explicit TreeItem(PersonM* data, TreeItem *parentItem = nullptr);

    void appendChild(std::unique_ptr<TreeItem> &&child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    const PersonM* data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    std::vector<std::unique_ptr<TreeItem>> m_childItems;
    PersonM* m_itemData; // TODO: std::shared_ptr
    TreeItem *m_parentItem;
};
//! [0]

#endif // TREEITEM_H
