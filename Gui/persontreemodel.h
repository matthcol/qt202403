#pragma once
#include <QObject>
#include <QAbstractItemModel>

class PersonTreeModel: public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PersonTreeModel(QObject* parent=nullptr);
    virtual ~PersonTreeModel() = default;

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};


