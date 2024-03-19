#pragma once
#include <QString>
#include <QDate>
#include <QDebug>
#include <QQmlEngine>

class PersonM
{
    Q_GADGET
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QDate birthdate READ birthdate WRITE setBirthdate)
    // QML_VALUE_TYPE(person) // NB: need QT6
public:
    PersonM();
    PersonM(const QString &name, const QDate &birthdate);

    const QString& name() const;
    void setName(const QString& name);

    const QDate& birthdate() const;
    void setBirthdate(const QDate &birthdate);

private:
    QString m_name;
    QDate m_birthdate;
};

Q_DECLARE_METATYPE(PersonM)

QDebug operator<<(QDebug out, const PersonM& person);
