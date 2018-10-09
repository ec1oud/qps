import QtQuick 2.12
import org.lxqt.qps 1.0

TableView {
    width: 1730; height: 720
    columnSpacing: 4; rowSpacing: 4
    model: ProcessModel { }
    delegate: Rectangle {
        color: "#EEE"
        implicitWidth: Math.max(20, text.implicitWidth)
        implicitHeight: text.implicitHeight
        Text {
            id: text
            text: model.display
            width: parent.width
            elide: Text.ElideRight
        }
    }
    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
}
