#include "processmodel.h"
#include "../src/proc.h"

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
    m_proc.refresh();
    m_pids = m_proc.procs.keys().toVector();
    std::sort(m_pids.begin(), m_pids.end());
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
    switch (field) {
    case F_PID:
        return pid;
    case F_USER:
        return pi->username;
    case F_CMD:
        return pi->command;
    default:
        return QString();
    }
}

ProcessModel::~ProcessModel()
{
}