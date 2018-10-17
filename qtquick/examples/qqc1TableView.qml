import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import "."

ApplicationWindow {
    title: qsTr("top")
    width: 900; height: 600; visible: true
    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 6
            Label {
                text: qsTr("Update every")
            }
            Switch {
                id: cbUpdate
                checked: true
            }
            SpinBox {
                id: sbUpdate
                minimumValue: 1
                maximumValue: 60
                value: 2
                enabled: cbUpdate.checked
            }
            Label {
                text: qsTr("sec")
            }
            Item {
                Layout.fillWidth: true
            }
            TextField {
                id: tfFilter
                implicitWidth: parent.width / 4
            }
        }
    }
    TableView1 {
        id: table
        anchors.fill: parent
        updateInterval: sbUpdate.value * 1000
        updateEnabled: cbUpdate.checked
    }
}
