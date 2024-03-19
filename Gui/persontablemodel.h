#pragma once
#include <QAbstractTableModel>
#include "personm.h"

class PersonTableModel: public QAbstractTableModel
{
    Q_OBJECT
private:
    QVector<PersonM> m_persons;
public:
    explicit PersonTableModel(QObject* parent=nullptr);
    virtual ~PersonTableModel() = default;
    void loadData();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
