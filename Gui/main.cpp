#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "persontablemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    // model
    qRegisterMetaType<PersonM>();
    // std::shared_ptr<PersonTableModel> model_ptr(new PersonTableModel());
    // PersonTableModel* model_ptr(new PersonTableModel());
    // model_ptr->loadData();
    PersonTableModel model;
    model.loadData();
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("modelPersonTable", &model); // model_ptr);
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
