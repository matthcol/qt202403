#pragma once
#include <QString>
#include <QDate>
#include <QDebug>

class PersonM
{
public:
    PersonM();
    PersonM(const QString &name, const QDate &birthdate);

    QStringView name() const;
    void setName(const QString& name);

    const QDate& birthdate() const;
    void setBirthdate(const QDate &birthdate);

private:
    QString m_name;
    QDate m_birthdate;
};

Q_DECLARE_METATYPE(PersonM)

QDebug operator<<(QDebug out, const PersonM& person);
