#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "persontablemodel.h"
#include "treemodel.h"

QString textModel(){
    return QString("Getting Started                         How to familiarize yourself with Qt Designer\n")
           + QString("  Launching Designer                  Running the Qt Designer application\n")
           + QString(" The User Interface                  How to interact with Qt Designer\n");
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    // model 1
    // qRegisterMetaType<PersonM>();
    // std::shared_ptr<PersonTableModel> model_ptr(new PersonTableModel());
    // PersonTableModel* model_ptr(new PersonTableModel());
    // model_ptr->loadData();
    PersonTableModel modelTable;
    modelTable.loadData();
    // model 2
    TreeModel modelTree(textModel());
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("modelPersonTable", &modelTable); // model_ptr);
    context->setContextProperty("modelPersonTree", &modelTree);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
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
