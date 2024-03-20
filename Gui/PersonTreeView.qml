import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
// https://doc.qt.io/qt-5/qtquickcontrols2-material.html
import Qt.labs.qmlmodels

Page {

    header: Label {
        // color: Material.Purple
        font.pointSize: 25
        text: qsTr("TableTree with c++ model")
    }

    TreeView {
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
