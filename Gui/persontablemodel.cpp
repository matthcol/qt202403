#include "persontablemodel.h"
#include <QDebug>
#include <QDate>

PersonTableModel::PersonTableModel(QObject* parent):
    QAbstractTableModel(parent)
{}

void PersonTableModel::loadData()
{
    m_persons.append(PersonM("John Doe", QDate(1950,5,6)));
    m_persons.append(PersonM("John Doe", QDate(1950,5,6)));
}

int PersonTableModel::rowCount(const QModelIndex &parent) const
{
    return m_persons.size();
}

int PersonTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant PersonTableModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "model data called on index:"
             << index
             << "and role:"
             << role;
    if (!index.isValid()) return QVariant();
    // return data for view according index and role
    if (role == Qt::DisplayRole) {
        switch (index.column()){
        case 0:
            return m_persons[index.row()].name().toString();
        case 1:
            return m_persons[index.row()].birthdate().toString();
        }
    }
    return QVariant();
}


QVariant PersonTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug() << "model header data called on section:"
             << section
             << "and role:"
             << role;
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}
