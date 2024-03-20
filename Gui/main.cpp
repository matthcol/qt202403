#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "persontablemodel.h"
#include "persontreemodel.h"
#include "persontreenode.h"

PersonTreeModel* createTreeModel(){
    QVector<PersonTreeNode_ptr> children21{
        new PersonTreeNode("John"),
        new PersonTreeNode("Jane"),
        new PersonTreeNode("Jill")

    };
    QVector<PersonTreeNode_ptr> children22{
        new PersonTreeNode("Geff"),
        new PersonTreeNode("Gill"),
        new PersonTreeNode("Gal")
    };
    // QVector<PersonTreeNode_ptr> children1{
    //     new PersonTreeNode("Paul", children21),
    //     new PersonTreeNode("Dana", children22)
    // };
    QVector<PersonTreeNode_ptr> children1{
        new PersonTreeNode("Paul"),
        new PersonTreeNode("Dana")
    };
    PersonTreeNode_ptr root = new PersonTreeNode("Groot", children1);
    //PersonTreeNode_ptr root = new PersonTreeNode("Groot");
    return new PersonTreeModel(root);
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
    PersonTreeModel* modelTree = createTreeModel();
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("modelPersonTable", &modelTable); // model_ptr);
    context->setContextProperty("modelPersonTree", modelTree);
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
