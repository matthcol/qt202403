import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
// https://doc.qt.io/qt-5/qtquickcontrols2-material.html
import Qt.labs.qmlmodels 1.0

Page {

    header: Label {
        // color: Material.Purple
        font.pointSize: 25
        text: qsTr("TableView with c++ model")
    }

    footer: Row {
        Button{
            text: qsTr("Add")
            onClicked: {
                console.log("Add person")
                modelPersonTable.addPerson()
            }
        }
        Button{
            text: qsTr("Remove")
            onClicked: console.log("Remove person")
        }
    }

    TableView{
        id: tablePersonView
        anchors.fill: parent
        columnSpacing: 5
        model: modelPersonTable
        delegate: DelegateChooser{
            DelegateChoice { column: 0 ; delegate: delegateEditableText }
            DelegateChoice { column: 1 ; delegate: delegateDate }
        }
    }

    Component {
        id: delegateEditableText
        TextInput {
            color: Material.foreground
            font.pixelSize: 20
            text: display

            onEditingFinished: {
               console.log("name changed:", text)
               // modelPersonTable.setData(right index, text, Qt::EditRole
               edit = text
            }
        }
    }

    Component {
        id: delegateDate
        Label {
            text: display.toLocaleDateString(Locale.ShortFormat)
        }
    }

}
