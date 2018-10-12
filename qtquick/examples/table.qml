import QtQuick 2.12
import QtQuick.Controls 2.4
import org.lxqt.qps 1.0

Rectangle {
    width: 1730; height: 720
    Row {
        id: header
        width: table.contentWidth
        height: 40
        x: -table.contentX
        z: 1
        spacing: 4
        Repeater {
            model: table.model.columnCount()
            Rectangle {
                width: table.model.columnWidth(index); height: parent.height
                color: "orange"

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    x: 4
                    width: parent.width - 4
                    text: table.model.headerData(index, Qt.Horizontal)
                }
            }
        }
    }
    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        columnSpacing: 4; rowSpacing: 4
        model: ProcessModel { }
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
