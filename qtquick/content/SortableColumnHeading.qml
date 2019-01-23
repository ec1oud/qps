import QtQuick 2.12

Rectangle {
    id: root
    color: "wheat"
    property int initialSortOrder: Qt.AscendingOrder
    property alias text: label.text
    property real initialWidth: 100
    signal sorting
    signal dropped(real x)
    width: splitter.x + 6
    z: dragHandler.active ? 1 : 0

    function stopSorting() {
        state = ""
    }

    Text {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        x: 4
        width: parent.width - 4
        text: table.model.headerData(index, Qt.Horizontal)
    }

    Text {
        id: upDownIndicator
        anchors.right: parent.right
        anchors.margins: 4
        anchors.verticalCenter: parent.verticalCenter
        text: "^"
        visible: false
    }

    TapHandler { id: tap; onTapped: nextState() }

    Item {
        id: splitter
        x: root.initialWidth - 6
        width: 12
        height: parent.height + 10
        DragHandler {
            yAxis.enabled: false
            onActiveChanged: if (!active) table.forceLayout()
        }
    }

    DragHandler {
        id: dragHandler
        onActiveChanged: if (!active) root.dropped(centroid.scenePosition.x)
    }

    function nextState() {
        if (state == "")
            state = (initialSortOrder == Qt.DescendingOrder ? "down" : "up")
        else if (state == "up")
            state = "down"
        else
            state = "up"
        root.sorting()
    }
    states: [
        State {
            name: "up"
            PropertyChanges { target: upDownIndicator; visible: true; rotation: 0 }
            PropertyChanges { target: root; color: "orange" }
        },
        State {
            name: "down"
            PropertyChanges { target: upDownIndicator; visible: true; rotation: 180 }
            PropertyChanges { target: root; color: "orange" }
        }
    ]
}
