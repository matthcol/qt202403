#pragma once
#include <QAbstractTableModel>
#include "personm.h"

class PersonTableModel:
     public QAbstractTableModel
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
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    // unused with QML views by default:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    // CRUD methods
    void addPerson();
    void addPerson(const QString& name, const QDate& birthdate);
    void addPerson(const PersonM& person);
    PersonM createPerson(const QString& name, const QDate& birthdate);

signals:
    void personAdded(const PersonM& person);
};
