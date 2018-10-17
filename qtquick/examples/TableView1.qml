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
    // -------------------------
    // end of "top"-like columns
    // -------------------------
    TableViewColumn {
        role: "cwd"
        title: "Current working directory"
        width: model.columnWidth(11) + 8
    }
    TableViewColumn {
        role: "root"
        title: "Root directory"
        width: model.columnWidth(12) + 8
    }
    TableViewColumn {
        role: "cmdline"
        title: "Whole command line"
        width: model.columnWidth(13) + 8
    }
    TableViewColumn {
        role: "tgid"
        title: "TGID"
        width: model.columnWidth(14) + 8
    }
    TableViewColumn {
        role: "ppid"
        title: "PPID"
        width: model.columnWidth(15) + 8
    }
    TableViewColumn {
        role: "pgid"
        title: "PGID"
        width: model.columnWidth(16) + 8
    }
    TableViewColumn {
        role: "sid"
        title: "SID"
        width: model.columnWidth(17) + 8
    }
    TableViewColumn {
        role: "tty"
        title: "TTY"
        width: model.columnWidth(18) + 8
    }
    TableViewColumn {
        role: "tpgid"
        title: "TPGID"
        width: model.columnWidth(19) + 8
    }
    TableViewColumn {
        role: "group"
        title: "Group"
        width: model.columnWidth(20) + 8
    }
    TableViewColumn {
        role: "uid"
        property int col: 21
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "euid"
        property int col: 22
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "suid"
        property int col: 23
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "fsuid"
        property int col: 24
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "gid"
        property int col: 25
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "egid"
        property int col: 26
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "sgid"
        property int col: 27
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "fsgid"
        property int col: 28
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "rpri"
        property int col: 29
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "tms"
        property int col: 30
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "affcpu"
        property int col: 31
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "cpunum"
        property int col: 48
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "slpavg"
        property int col: 32
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "nlwp"
        property int col: 33
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "majflt"
        property int col: 34
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "minflt"
        property int col: 35
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "trs"
        property int col: 36
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "drs"
        property int col: 37
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "stack"
        property int col: 38
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "share"
        property int col: 39
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "dt"
        property int col: 40
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "iow"
        property int col: 41
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "ior"
        property int col: 42
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "stat"
        property int col: 43
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "flags"
        property int col: 44
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "wchan"
        property int col: 45
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "wcpu"
        property int col: 46
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
    }
    TableViewColumn {
        role: "start"
        property int col: 47
        title: model.headerData(col, Qt.Horizontal)
        width: model.columnWidth(col) + 8
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

