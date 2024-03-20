#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "persontablemodel.h"
#include "treemodel.h"
#include "treeitem.h"
#include <memory>

void logPersonAdded(const PersonM& person){
    qDebug() << "main log: person added:" << person;
}

QString textModel(){
    return QString("Getting Started                         How to familiarize yourself with Qt Designer\n")
           + QString("  Launching Designer                  Running the Qt Designer application\n")
           + QString("      Designer                        Running the Qt Designer application\n")
           + QString("  The User Interface                  How to interact with Qt Designer\n");
}

std::unique_ptr<TreeItem> personTreeData(){
    PersonM* person1 = new PersonM("John Doe", QDate(1950,5, 6));
    PersonM* person21 = new PersonM("Jane Doe", QDate(1970,5, 6));
    PersonM* person22 = new PersonM("Emil Doe", QDate(1971,5, 6));
    PersonM* person23 = new PersonM("Basil Doe", QDate(1972,5, 6));
    PersonM* person31 = new PersonM("Bjorn Doe", QDate(1992,5, 6));
    std::unique_ptr<TreeItem> root = std::make_unique<TreeItem>(nullptr);
    TreeItem* parent = root.get();
    std::unique_ptr<TreeItem> firstPerson = std::make_unique<TreeItem>(
        person1, parent);
    parent = firstPerson.get();
    std::unique_ptr<TreeItem> secondPerson = std::make_unique<TreeItem>(
        person21, parent);
    parent = secondPerson.get();
    secondPerson->appendChild(std::make_unique<TreeItem>(
        person31, parent
        ));
    firstPerson->appendChild(std::move(secondPerson));
    parent = firstPerson.get();
    firstPerson->appendChild(std::make_unique<TreeItem>(
        person22, parent
        ));
    firstPerson->appendChild(std::make_unique<TreeItem>(
        person23, parent
        ));
    root->appendChild(std::move(firstPerson));
    return root;
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    // model 1
    // qRegisterMetaType<PersonM>(); // need by QT5, QT6 => QML_VALUE_TYPE(person)
    // model in direct mode or classic pointer (no smart pointers)
    // PersonTableModel* model_ptr(new PersonTableModel());
    // model_ptr->loadData();
    PersonTableModel modelTable;
    modelTable.loadData();
    // model 2
    // TreeModel modelTree(textModel()); // fromindented text
    TreeModel modelTree(personTreeData());
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("modelPersonTable", &modelTable); // model_ptr);
    context->setContextProperty("modelPersonTree", &modelTree);
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    // connections
    QObject::connect(
        &modelTable,
        &PersonTableModel::personAdded,
        &logPersonAdded);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
