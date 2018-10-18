import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.4
import org.lxqt.qps 1.0
import Qt.labs.qmlmodels 1.0
import "../content"
import "."

ApplicationWindow {
    title: qsTr("top")
    width: 1730; height: 720; visible: true
    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 6
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
            TextField {
                id: tfFilter
                implicitWidth: parent.width / 4
                onTextEdited: table.contentY = 0
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
                initialSortOrder: table.model.initialSortOrder(index)
                onSorting: {
                    for (var i = 0; i < peter.model; ++i)
                        if (i != index)
                            peter.itemAt(i).stopSorting()
                    table.model.sort(index, state == "up" ? Qt.AscendingOrder : Qt.DescendingOrder)
                }
            }
        }
    }
    TableView2 {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        updateInterval: sbUpdate.value * 1000
        updateEnabled: cbUpdate.checked
        filterText: tfFilter.text
    }
    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
}
