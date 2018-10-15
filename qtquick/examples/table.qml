import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import org.lxqt.qps 1.0
import "../content"

ApplicationWindow {
    title: qsTr("top")
    width: 1730; height: 720; visible: true
    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            Switch {
                id: cbUpdate
                checked: true
                text: qsTr("Update every")
            }
            SpinBox {
                id: sbUpdate
                from: 1
                to: 60
                value: 2
                enabled: cbUpdate.checked
            }
            Label {
                text: "sec"
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }
    Row {
        id: header
        width: table.contentWidth
        height: cbUpdate.height
        x: -table.contentX
        z: 1
        spacing: 4
        Repeater {
            id: peter
            model: table.model.columnCount()
            SortableColumnHeading {
                width: Math.min(600, table.model.columnWidth(index)); height: parent.height
                text: table.model.headerData(index, Qt.Horizontal)
                onSorting: {
                    for (var i = 0; i < peter.model; ++i)
                        if (i != index)
                            peter.itemAt(i).stopSorting()
                    table.model.sort(index, state == "up" ? Qt.AscendingOrder : Qt.DescendingOrder)
                }
            }
        }
    }
    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        columnSpacing: 4; rowSpacing: 4
        model: SortFilterProcessModel { }
        Timer {
            interval: sbUpdate.value * 1000
            repeat: true
            running: cbUpdate.checked
            onTriggered: table.model.processModel.update()
        }
        columnWidthProvider: function(column) { return Math.min(600, model.columnWidth(column)) }

        delegate: Rectangle {
            color: "#EEE"
            implicitHeight: text.implicitHeight
            Text {
                id: text
                text: model.display
                width: parent.width
                elide: column == 49 ? Text.ElideLeft : Text.ElideRight
                font.preferShaping: false
            }
        }

        ScrollBar.horizontal: ScrollBar { }
        ScrollBar.vertical: ScrollBar { }
    }
    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
}
