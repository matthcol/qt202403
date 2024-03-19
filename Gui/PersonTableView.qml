import QtQuick 2.15
import QtQuick.Controls 2.15

Page {

    header: Label {
        text: qsTr("TableView with c++ model")
    }

    TableView{
        id: tablePersonView
        anchors.fill: parent
        columnSpacing: 5
        model: modelPersonTable
        delegate: Label{
            text: display
        }
    }
}
