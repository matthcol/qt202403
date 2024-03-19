#include "persono.h"

PersonO::PersonO(QObject* parent): QObject(parent) {}

PersonO::PersonO(const QString &name, const QDate &birthdate, QObject* parent) :
    QObject(parent),
    m_name(name),
    m_birthdate(birthdate)
{}

QStringView PersonO::name() const
{
    return m_name; // implicit conversion to QStringView
}

void PersonO::setName(const QString &name)
{
    m_name = name; // copy
}

const QDate &PersonO::birthdate() const
{
    return m_birthdate; // const ref on member birthdate
}

void PersonO::setBirthdate(const QDate &birthdate)
{
    m_birthdate = birthdate;
}

QDebug operator<<(QDebug out, const PersonO& person){
    return out << person.name()
               << '(' << person.birthdate() << ')';
}



