import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
// https://doc.qt.io/qt-5/qtquickcontrols2-material.html
import Qt.labs.qmlmodels 1.15

Page {

    header: Label {
        // color: Material.Purple
        font.pointSize: 25
        text: qsTr("TableView with c++ model")
    }

    footer: Row {
        Button{
            id: buttonAddDefault
            text: qsTr("Add 1")
            onClicked: {
                console.log("Add default person")
                modelPersonTable.addPerson()
            }

            // Component.onCompleted: {
            //     buttonAdd.onClicked.connect(modelPersonTable.addPerson)
            // }
        }
        Button{
            id: buttonAddNameBirthdate
            text: qsTr("Add 2")
            onClicked: {
                // TODO: fetch name and birthdate from UI
                const name = "Dupont"
                const birthdate = new Date()
                console.log("Add person with name and birthdate:", name, birthdate)
                modelPersonTable.addPerson(name, birthdate)
            }
        }

        Button{
            id: buttonAddPerson
            text: qsTr("Add 3")
            onClicked: {
                // TODO: fetch name and birthdate from UI
                const name = "Dupond"
                const birthdate = new Date()
                const person = modelPersonTable.createPerson(name, birthdate)
                console.log("Add person created by qml:",
                    person,
                    person.name,
                    person.birthdate
                )
                modelPersonTable.addPerson(person)
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

        // NB: without delegateChooser use a Loader to return
        // the delegate of your choice
        // but you have to retrieve columnIndex (with a customRole)
        // https://forum.qt.io/topic/123543/tableview-with-different-delegates-for-its-columns-qtquick-2-15/4
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

    // NB: need to be a QObject
    // PersonM {
    //     name: "Dupont"
    //     birthdate:  new Date()
    // }

    // Connections{
    //     target: buttonAdd
    //     function onClicked()  {
    //         console.log("Add person")
    //         modelPersonTable.addPerson()
    //     }
    // }

    function logAdded(person){
        console.log("person added with sucess: ", person)
    }

    // Connections{
    //     target:  modelPersonTable
    //     function onPersonAdded(person){
    //         logAdded(person)
    //     }
    // }

    Component.onCompleted: modelPersonTable.onPersonAdded.connect(logAdded)
}
