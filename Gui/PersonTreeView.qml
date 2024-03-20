import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
// https://doc.qt.io/qt-5/qtquickcontrols2-material.html
import Qt.labs.qmlmodels 1.0

Page {

    header: Label {
        // color: Material.Purple
        font.pointSize: 25
        text: qsTr("TableTree with c++ model")
    }

    TableView {
    //TreeView {
        id: treePersonView
        anchors.fill: parent
        columnSpacing: 5
        model: modelPersonTree

        delegate: //TreeViewDelegate{}
                  Label{
            text: display
        }
    }
}
