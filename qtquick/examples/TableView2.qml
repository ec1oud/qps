import QtQuick 2.12
import QtQuick.Controls 2.4
import org.lxqt.qps 1.0
import Qt.labs.qmlmodels 1.0
import "../content"

TableView {
    id: table
    property alias updateInterval: timer.interval
    property alias updateEnabled: timer.running
    property alias filterText: tableModel.filterText
    columnSpacing: 4; rowSpacing: 4
    model: SortFilterProcessModel { id: tableModel }
    Timer {
        id: timer
        interval: 1000
        repeat: true
        running: true
        onTriggered: table.model.processModel.update()
    }

    delegate: DelegateChooser {
        role: "type"
        DelegateChoice {
            roleValue: "%"
            BarGraph {
                value: model.number
            }
        }
        DelegateChoice {
            roleValue: "string"
            Rectangle {
                color: "#EEE"
                implicitHeight: stringText.implicitHeight
                Text {
                    id: stringText
                    text: model.display
                    width: parent.width
                    elide: Text.ElideRight
                    font.preferShaping: false
                }
            }
        }
        DelegateChoice {
            Rectangle {
                color: "#EEE"
                implicitHeight: defaultText.implicitHeight
                Text {
                    id: defaultText
                    text: model.display
                    width: parent.width
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignRight
                    font.preferShaping: false
                }
            }
        }
    }

    ScrollBar.horizontal: ScrollBar { }
    ScrollBar.vertical: ScrollBar { }
}
