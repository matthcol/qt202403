#pragma once
#include <QString>
#include <QDate>
#include <QDebug>

class Person
{
public:
    Person();
    explicit Person(const QString &name);
    Person(const QString &name, const QDate &birthdate);

    QStringView name() const;
    void setName(const QString& name);

    const QDate& birthdate() const;
    void setBirthdate(const QDate &birthdate);

  private:
    QString m_name;
    QDate m_birthdate;
};

QDebug operator<<(QDebug out, const Person& person);
