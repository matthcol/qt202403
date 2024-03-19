#pragma once
#include <QString>
#include <QDate>
#include <QDebug>

class PersonO: public QObject
{
    Q_OBJECT
public:
    PersonO(QObject* parent=nullptr);
    PersonO(const QString &name, const QDate &birthdate, QObject* parent=nullptr);

    QStringView name() const;
    void setName(const QString& name);

    const QDate& birthdate() const;
    void setBirthdate(const QDate &birthdate);

private:
    QString m_name;
    QDate m_birthdate;
};

QDebug operator<<(QDebug out, const PersonO& person);
