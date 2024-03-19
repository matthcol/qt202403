#include "personm.h"

PersonM::PersonM() {}

PersonM::PersonM(const QString &name, const QDate &birthdate) :
    m_name(name),
    m_birthdate(birthdate)
{}

QStringView PersonM::name() const
{
    return m_name; // implicit conversion to QStringView
}

void PersonM::setName(const QString &name)
{
    m_name = name; // copy
}

const QDate &PersonM::birthdate() const
{
    return m_birthdate; // const ref on member birthdate
}

void PersonM::setBirthdate(const QDate &birthdate)
{
    m_birthdate = birthdate;
}

QDebug operator<<(QDebug out, const PersonM& person){
    return out << person.name()
               << '(' << person.birthdate() << ')';
}


