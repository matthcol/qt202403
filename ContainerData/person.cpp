#include "person.h"

Person::Person() {}

Person::Person(const QString &name, const QDate &birthdate) :
    m_name(name),
    m_birthdate(birthdate)
{}

Person::Person(const QString &name) :
    m_name(name)
{}

QStringView Person::name() const
{
    return m_name; // implicit conversion to QStringView
}

void Person::setName(const QString &name)
{
    m_name = name; // copy
}

const QDate &Person::birthdate() const
{
    return m_birthdate; // const ref on member birthdate
}

void Person::setBirthdate(const QDate &birthdate)
{
    m_birthdate = birthdate;
}

QDebug operator<<(QDebug out, const Person& person){
    return out << person.name()
               << '(' << person.birthdate() << ')';
}


