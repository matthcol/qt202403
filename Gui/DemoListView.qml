import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Page {

    function removeLast(model){
        if (model.count >0){
            model.remove(model.count - 1)
        } else {
            console.log("No person anymore to remove")
        }

    }

    header: Text {
        color: Material.foreground
        font.pointSize: 25
        text: qsTr("ListView with qml model")
    }
    footer: Row {
        Button{
            text: qsTr("Add")
            onClicked: modelPersons.append({
                name: "Another Doe",
                birthdate: "2000-1-1"
            })
        }
        Button{
            text: qsTr("Remove")
            onClicked: removeLast(modelPersons)
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: modelPersons
        delegate: Label{
            text: name + "(" + birthdate + ")"
        }
    }

    ListModel{
        id: modelPersons
        ListElement{
            name: "John Doe"
            birthdate: "1950-06-05"
        }
        ListElement{
            name: "Jane Doe"
            birthdate: "1950-05-06"
        }
    }
}
