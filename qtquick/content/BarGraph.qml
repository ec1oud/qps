import QtQuick 2.12

Item {
    property real value: 50
    implicitWidth: 250
    implicitHeight: text.implicitHeight + 6
    Rectangle {
        anchors {
            fill: parent
            topMargin: 2
            bottomMargin: 2
        }
        color: "lightgray"

        Rectangle {
            x: 1; y: 1; height: parent.height - 2
            width: value * parent.width / 100
            color: "green"
        }

        Text {
            id: text
            anchors.fill: parent
            text: value.toFixed(1) + "%"
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.preferShaping: false
        }
    }
}
