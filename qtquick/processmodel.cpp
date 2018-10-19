#include "processmodel.h"
#include "../src/proc.h"
#include <QDebug>
#include <QFontMetrics>
#include <QGuiApplication>

/* ----------------------- Global Variable START ---------------------- */
bool previous_flag_show_thread_prev = false; // previous state
bool flag_show_thread = false; // to see informations at the thread level
int flag_thread_ok = true;     // we presume a kernel 2.6.x using NPTL
bool flag_session_start = false;
bool flag_start_mini = false; // Need for Xorg.Session
bool flag_refresh = true;     // DEL
bool flag_xcompmgr = false;   // DEL test.compiz..
bool flag_devel = false;
bool flag_schedstat = false;
bool flag_smallscreen = false;
bool flag_firstRun = true; // test
/* ----------------------- END global variables ----------------------- */

ProcessModel::ProcessModel(QObject *parent):
    QAbstractTableModel(parent)
{
    m_proc.commonPostInit();
    update();
}

void ProcessModel::update()
{
    beginResetModel();
    // TODO complete this: tell which rows are inserted and which are removed
//    beginInsertRows(QModelIndex(), 0, 0);
    m_proc.refresh();
    m_pids = m_proc.procs.keys().toVector();
    std::sort(m_pids.begin(), m_pids.end());
//    endInsertRows();
    endResetModel();
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    return m_pids.count();
}

int ProcessModel::columnCount(const QModelIndex &parent) const
{
    return F_CMDLINE + 1;
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    fields field = fields(index.column());
    int pid = m_pids[index.row()];
    Procinfo *pi = m_proc.procs.value(pid);
    Category *cat = m_proc.categories.value(field);
    switch (role) {
    case Qt::DisplayRole:
        if (!cat) // F_PROCESSNAME probably
            return QString();
        return cat->string(pi);
    case int(ProcessModel::Role::Sort):
        if (!cat) // F_PROCESSNAME probably
            return QVariant();
        return cat->sortable(pi);
    default:
        return QVariant();
    }

    // Category::string() is pre-existing functionality so we can avoid doing a switch like this:
//    switch (field) {
//    case F_PID:
//        return pid;
//    case F_USER:
//        return pi->username;
//    case F_CMD:
//        return pi->command;
//    default:
//        return QString();
//    }
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        // section is interpreted as column
        Category *cat = m_proc.categories.value(section);
        if (!cat)
            return QString();
        return cat->name;
    } else {
        return QString();
    }
}

int ProcessModel::columnWidth(int c, const QFont *font)
{
    if (!m_columnWidths[c]) {
        Category *cat = m_proc.categories.value(c);
        if (!cat)
            return 1; // could be zero, but we have to avoid the error "columnWidthProvider did not return a valid width for column"
        QFontMetrics defaultFontMetrics = QFontMetrics(QGuiApplication::font());
        QFontMetrics fm = (font ? QFontMetrics(*font) : defaultFontMetrics);
        int ret = fm.width(headerData(c, Qt::Horizontal).toString() + QLatin1String(" ^")) + 8;
        for (int r = 0; r < m_pids.count(); ++r)
            ret = qMax(ret, fm.width(cat->string(m_proc.procs.value(m_pids[r]))));
        m_columnWidths[c] = ret;
    }
    return m_columnWidths[c];
}

ProcessModel::~ProcessModel()
{
}
