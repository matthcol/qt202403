#pragma once
#include <QObject>
#include <QAbstractItemModel>
#include <persontreenode.h>

class PersonTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PersonTreeModel(PersonTreeNode_ptr root, QObject* parent=nullptr);
    virtual ~PersonTreeModel() = default;

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    PersonTreeNode_ptr m_root;
};


