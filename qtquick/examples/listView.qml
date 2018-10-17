import QtQuick 2.12
import org.lxqt.qps 1.0
import "../content"

ListView {
    id: listView
    width: 900; height: 600
    model: SortFilterProcessModel { id: listModel }
    header: Rectangle{
        color: "lightsteelblue"
        width: parent.width; height: 20
        Row {
            width: parent.width; height: 20
            Text { text: "pid"; width: listModel.columnWidth(0) + 4 }
            Text { text: "user"; width: listModel.columnWidth(1) + 4 }
            Text { text: "pri"; width: listModel.columnWidth(2) + 4 }
            Text { text: "nice"; width: listModel.columnWidth(3) + 4 }
            Text { text: "size"; width: listModel.columnWidth(4) + 4 }
            Text { text: "rss"; width: listModel.columnWidth(5) + 4 }
            Text { text: "cpu"; width: listModel.columnWidth(6) + 4 }
            Text { text: "pmem"; width: listModel.columnWidth(7) + 4 }
            Text { text: "time"; width: listModel.columnWidth(8) + 4 }
            Text { text: "plcy"; width: listModel.columnWidth(9) + 4 }
            Text { text: "cmd"; width: listModel.columnWidth(10) + 4 }
        }
    }
    delegate:  Row {
        width: parent.width; height: 20
        Text { text: pid; width: listModel.columnWidth(0) + 4 }
        Text { text: user; width: listModel.columnWidth(1) + 4 }
        Text { text: pri; width: listModel.columnWidth(2) + 4 }
        Text { text: nice; width: listModel.columnWidth(3) + 4 }
        Text { text: size; width: listModel.columnWidth(4) + 4 }
        Text { text: rss; width: listModel.columnWidth(5) + 4 }
        Text { text: cpu; width: listModel.columnWidth(6) + 4 }
        Text { text: pmem; width: listModel.columnWidth(7) + 4 }
        Text { text: time; width: listModel.columnWidth(8) + 4 }
        Text { text: plcy; width: listModel.columnWidth(9) + 4 }
        Text { text: cmd; width: listModel.columnWidth(10) + 4 }
    }
    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: listModel.processModel.update()
    }

    Rectangle {
        id: verticalScrollDecorator
        anchors { right: parent.right; margins: 2 }
        color: "grey"
        width: 5; radius: 2; antialiasing: true
        height: parent.height * (parent.height / parent.contentHeight) - (width - anchors.margins) * 2
        y: (parent.contentY - parent.originY) * (parent.height / parent.contentHeight)
    }
    Component.onCompleted: listModel.sort(7, Qt.DescendingOrder) // memory
}
