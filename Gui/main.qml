import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Learn Model/View")

    footer: TabBar{
        id: bar
        width: parent.width
        TabButton{
            text: qsTr("ListView qml")
        }
        TabButton{
            text: qsTr("TableView c++")
        }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: bar.currentIndex
        DemoListView{}
        PersonTableView{}
    }
}
