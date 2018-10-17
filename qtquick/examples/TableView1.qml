import QtQuick 2.12
import QtQuick.Controls 1.4
import org.lxqt.qps 1.0

TableView {
    id: table
    property alias updateInterval: timer.interval
    property alias updateEnabled: timer.running
    TableViewColumn {
        role: "pid"
        title: "PID"
        width: model.columnWidth(0) + 8
    }
    TableViewColumn {
        role: "user"
        title: "User"
        width: model.columnWidth(1) + 8
    }
    TableViewColumn {
        role: "pri"
        title: "Pri"
        width: model.columnWidth(2) + 8
    }
    TableViewColumn {
        role: "nice"
        title: "NI"
        width: model.columnWidth(3) + 8
    }
    TableViewColumn {
        role: "size"
        title: "Size"
        width: model.columnWidth(4) + 8
    }
    TableViewColumn {
        role: "rss"
        title: "RSS"
        width: model.columnWidth(5) + 8
    }
    TableViewColumn {
        role: "cpu"
        title: "CPU"
        width: model.columnWidth(6) + 8
    }
    TableViewColumn {
        role: "mem"
        title: "Memory"
        width: model.columnWidth(7) + 8
    }
    TableViewColumn {
        role: "time"
        title: "Time"
        width: model.columnWidth(8) + 8
    }
    TableViewColumn {
        role: "plcy"
        title: "Policy"
        width: model.columnWidth(9) + 8
    }
    TableViewColumn {
        role: "cmd"
        title: "Command"
        width: model.columnWidth(10) + 8
    }
    sortIndicatorVisible: true
    onSortIndicatorOrderChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)
    onSortIndicatorColumnChanged: model.sort(sortIndicatorColumn, sortIndicatorOrder)
    model: SortFilterProcessModel { id: model }
    Timer {
        id: timer
        repeat: true
        onTriggered: table.model.processModel.update()
        interval: 1000
        running: true
    }
}

