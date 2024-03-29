#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include <memory>

//! [0]
class TreeItem
{
public:
    explicit TreeItem(QVariantList data, TreeItem *parentItem = nullptr);

    void appendChild(std::unique_ptr<TreeItem> &&child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    std::vector<std::unique_ptr<TreeItem>> m_childItems;
    QVariantList m_itemData;
    TreeItem *m_parentItem;
};
//! [0]

#endif // TREEITEM_H
