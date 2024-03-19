#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <algorithm>
#include <iterator>
#include <vector>

#include "person.h"
#include "personm.h"
#include "persono.h"

void playWithIntList(){
    qDebug() << "Play with list of integers";
    QList<qint32> temperatures;
    QList<qint32> temperatures2{12, 13, 18, 21, -7};
    qDebug() << temperatures;
    qDebug() << temperatures2;
    // loops
    for (int i=0; i<temperatures2.size(); i++) {
        qDebug() << "* " << temperatures2[i];
    }
    // c++11 foreach
    for (qint32 t : qAsConst(temperatures2)) {
        qDebug() << "- " << t;
    }
    // c++11 foreach with auto
    for (auto t : qAsConst(temperatures2)) {
        qDebug() << "# " << t;
    }
    // qt foreach
    foreach (auto t, temperatures2) {
        qDebug() << "@ " << t;
    }
    // functional foreach with iterators
    std::for_each(
        temperatures2.begin(),
        temperatures2.end(),
        [](auto t){ qDebug() << ". " << t; }
    );
    // partial iteration
    std::for_each(
        temperatures2.begin(),
        temperatures2.begin()+2,
        [](auto t){ qDebug() << "^ " << t; }
    );
    // Constructor with iterators
    QVector<qint32> temperatureVector(temperatures2.begin(), temperatures2.end());
    QVector<qint32> temperatureVector2(temperatures2.begin(), temperatures2.begin()+3);
    QVector<qint32> temperatureVector3(temperatures2.end()-3, temperatures2.end());
    QVector<qint32> temperatureVector4(temperatures2.rbegin(), temperatures2.rend());
    qDebug() << temperatureVector;
    qDebug() << temperatureVector2;
    qDebug() << temperatureVector3;
    qDebug() << temperatureVector4;
    // iterate with mutation
    for (auto& t: temperatures2){
        ++t;
    }
    qDebug() << "After incr: " << temperatures2;
}

void playWithStringList(){
    QVector<QString> cities{"Toulouse", "Pau", "Montpellier", "Paris"};
    cities << QStringLiteral("Lille")
           << QStringLiteral("Rennes")
           << QStringLiteral("Lyon")
           << u8"東京"
        ;
    qDebug() << cities;
    // for (const auto& city: cities){
    for (auto& city: qAsConst(cities)){
        qDebug() << city.toUpper();
    }
    for (auto& city: cities){
        city[0] = '#';
    }
    qDebug() << cities;
    // algo copy/copy_if from <algorithm>
    QVector<QString> extract;
    std::copy_if(
        cities.cbegin(),
        cities.cend(),
        std::back_inserter(extract),
        [](auto& city){ return city.length() > 6;}
    );
    qDebug() << extract;
    // auto + iterator
    // here: auto = QVector<QString>::ConstIterator or QVector<QString>::const_iterator
    auto first = cities.cbegin()+1;
    auto last = first + 3;
    std::vector<QString> cityStdVector(first, last);
    QSet<QString> citySet(cityStdVector.cbegin(), cityStdVector.cend());
    qDebug() << citySet;
}

void playWithString(){
    QString city = QStringLiteral("Toulouse");
    QString city2 = city;
    QString city3(city);
    QStringView cityView(city);
    city[0] = '#';
    qDebug() << city
             << ", " << cityView
             << ", " << city2;
}

void playWithPersonList(){
    Person p1;
    Person p2("John Doe", QDate(1950, 6, 5));
    Person p3(p2);

    qDebug() << p1.name();
    qDebug().noquote() << p2.name();
    qDebug() << p1 << p2 << p3;

    QVector<Person> persons{p1, p2};
    qDebug() << persons;

    // QVariant magic = QVariant::fromValue(p2);
    // qDebug() << magic;
}

void playWithPersonMList(){
    PersonM p1;
    PersonM p2("John Doe", QDate(1950, 6, 5));
    PersonM p3(p2);

    qDebug() << p1.name();
    qDebug().noquote() << p2.name();
    qDebug() << p1 << p2 << p3;

    QVector<PersonM> persons{p1, p2};
    qDebug() << persons;

    QVariant magic = QVariant::fromValue(p2);
    qDebug() << magic;
}

void playWithPersonOList(){
    PersonO p1;
    PersonO p2("John Doe", QDate(1950, 6, 5));
    // No copy !
    // PersonO p3(p2);
    // p1 = p2;

    qDebug() << p1.name();
    qDebug().noquote() << p2.name();
    qDebug() << p1 << p2;

    QVector<PersonO*> persons{&p1, &p2};
    qDebug() << persons;

    QVariant magic = QVariant::fromValue(&p2);
    qDebug() << magic;
}

void playWithVariants(){
    PersonM pm("John Doe", QDate(1950, 6, 5));
    PersonO po("Jane Doe", QDate(1950, 5, 6));
    QVector<QVariant> variants {
        "Toulouse", // implicit conversion QVariant(QString or const char *)
        12, // QVariant(int)
        QDate::currentDate(),  // QVariant(QDate)
        // QVariant::fromValue<PersonM>(pm),
        // QVariant::fromValue<PersonO*>(&po)
        QVariant::fromValue(pm),
        QVariant::fromValue(&po)
    };
    qDebug() << variants;
    for(auto& variant: qAsConst(variants)){
        qDebug() << " * Handle variant:" << variant
                 << " of type " << variant.typeName();
        if (variant.isNull() || !variant.isValid()){
            qDebug() << "Null or invalid variant:" << variant;
        }
        if (variant.canConvert<int>()) {
            int nb = variant.toInt();
            qDebug() << "Extract int from variant:" << nb;
        }
        if (variant.canConvert<QDate>()){
            QDate date = variant.toDate();
            qDebug() << "Extract date from variant:" << date;
        }
        if (variant.canConvert<PersonM>()){
            PersonM personM = variant.value<PersonM>();
            qDebug() << "Extract PersonM from variant:"
                     << personM;
        }
        if (variant.canConvert<PersonO*>()){
            PersonO* personO_ptr = variant.value<PersonO*>();
            qDebug() << "Extract PersonO ptr from variant:"
                     << personO_ptr
                     << ","  << *personO_ptr;
        }
        qDebug();
    }
}

void handlePerson(const Person& p){
    qDebug() << "Handle 1 person:" << p;
}

void demoImplicitConversion(){
    QString name1("John Doe");
    QString name2("Jane Doe");
    Person person(name1);
    qDebug() << person;
    // person = name2; // !! assign var Person to value of type QString
    qDebug() << person;
    handlePerson(person);
    // handlePerson(name1); // !!
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // call constructor QCoreApplication(int, char*[])
    qRegisterMetaType<PersonM>();
    // playWithIntList();
    // playWithStringList();
    // playWithString();
    // playWithPersonList();
    // playWithPersonMList();
    // playWithPersonOList();
    // playWithVariants();
    demoImplicitConversion();
    return a.exec();
}
