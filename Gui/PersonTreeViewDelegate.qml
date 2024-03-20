import QtQuick
import QtQuick.Controls

Item {
    implicitWidth: padding + label.x + label.implicitWidth + padding
    implicitHeight: label.implicitHeight * 1.5

    readonly property real indentation: 20
    readonly property real padding: 5

    // Assigned to by TreeView:
    required property TreeView treeView
    required property bool isTreeNode
    required property bool expanded
    required property int hasChildren
    required property int depth
    required property int row
    required property int column
    required property bool current

    // Rotate indicator when expanded by the user
    // (requires TreeView to have a selectionModel)
    property Animation indicatorAnimation: NumberAnimation {
        target: indicator
        property: "rotation"
        from: expanded ? 0 : 90
        to: expanded ? 90 : 0
        duration: 100
        easing.type: Easing.OutQuart
    }
    TableView.onPooled: indicatorAnimation.complete()
    TableView.onReused: if (current) indicatorAnimation.start()
    onExpandedChanged: indicator.rotation = expanded ? 90 : 0

    Rectangle {
        id: background
        anchors.fill: parent
        color: row === treeView.currentRow ? palette.highlight : "black"
        opacity: (treeView.alternatingRows && row % 2 !== 0) ? 0.3 : 0.1
    }

    Label {
        id: indicator
        x: padding + (depth * indentation)
        anchors.verticalCenter: parent.verticalCenter
        visible: isTreeNode && hasChildren
        text: "▶"

        TapHandler {
            onSingleTapped: {
                let index = treeView.index(row, column)
                treeView.selectionModel.setCurrentIndex(index, ItemSelectionModel.NoUpdate)
                treeView.toggleExpanded(row)
            }
        }
    }

    // use 3 roles statusTip, display and age
    Label {
        id: label
        color: statusTip ? Material.accent : Material.foreground
        x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width - padding - x
        clip: true
        text: `${display} (${age})`
    }

}
