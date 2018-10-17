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
    m_roleNames = QAbstractTableModel::roleNames();
    // TODO loop over the QMetaEnum
    m_roleNames.insert(int(Role::Sort), QByteArray("sort"));
    m_roleNames.insert(int(Role::Number), QByteArray("number"));
    m_roleNames.insert(int(Role::Type), QByteArray("type"));
    insertFieldRoles();
    m_proc.commonPostInit();
    update();
}

void ProcessModel::insertFieldRoles()
{
    int fdr = int(Role::FirstDataRole);
    m_roleNames.insert(fdr + F_PID, QByteArray("pid"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_TGID, QByteArray("tgid"));
#endif
    m_roleNames.insert(fdr + F_PPID, QByteArray("ppid"));
    m_roleNames.insert(fdr + F_PGID, QByteArray("pgid"));
    m_roleNames.insert(fdr + F_SID, QByteArray("sid"));
    m_roleNames.insert(fdr + F_TTY, QByteArray("tty"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_TPGID, QByteArray("tpgid"));
#endif
#ifdef MOSIX
    m_roleNames.insert(fdr + F_MIGR, QByteArray("migr"));
    m_roleNames.insert(fdr + F_LOCKED, QByteArray("locked"));
    m_roleNames.insert(fdr + F_NMIGS, QByteArray("nmigs"));
    m_roleNames.insert(fdr + F_NOMOVE, QByteArray("nomove"));
    m_roleNames.insert(fdr + F_RPID, QByteArray("rpid"));
#endif
    m_roleNames.insert(fdr + F_USER, QByteArray("user"));
    m_roleNames.insert(fdr + F_GROUP, QByteArray("group"));
    m_roleNames.insert(fdr + F_UID, QByteArray("uid"));
    m_roleNames.insert(fdr + F_EUID, QByteArray("euid"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_SUID, QByteArray("suid"));
    m_roleNames.insert(fdr + F_FSUID, QByteArray("fsuid"));
#endif
    m_roleNames.insert(fdr + F_GID, QByteArray("gid"));
    m_roleNames.insert(fdr + F_EGID, QByteArray("egid"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_SGID, QByteArray("sgid"));
    m_roleNames.insert(fdr + F_FSGID, QByteArray("fsgid"));
#endif
    m_roleNames.insert(fdr + F_PRI, QByteArray("pri"));
    m_roleNames.insert(fdr + F_NICE, QByteArray("nice"));
    m_roleNames.insert(fdr + F_PLCY, QByteArray("plcy"));
    m_roleNames.insert(fdr + F_RPRI, QByteArray("rpri"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_TMS, QByteArray("tms"));
    m_roleNames.insert(fdr + F_AFFCPU, QByteArray("affcpu"));
    m_roleNames.insert(fdr + F_SLPAVG, QByteArray("slpavg"));
#endif
    m_roleNames.insert(fdr + F_NLWP, QByteArray("nlwp"));
#ifdef SOLARIS
    m_roleNames.insert(fdr + F_ARCH, QByteArray("arch"));
#endif
    m_roleNames.insert(fdr + F_MAJFLT, QByteArray("majflt"));
    m_roleNames.insert(fdr + F_MINFLT, QByteArray("minflt"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_TRS, QByteArray("trs"));
    m_roleNames.insert(fdr + F_DRS, QByteArray("drs"));
    m_roleNames.insert(fdr + F_STACK, QByteArray("stack"));
#endif
    m_roleNames.insert(fdr + F_SIZE, QByteArray("size"));
    m_roleNames.insert(fdr + F_SWAP, QByteArray("swap"));
    m_roleNames.insert(fdr + F_MEM, QByteArray("mem"));
    m_roleNames.insert(fdr + F_RSS, QByteArray("rss"));
#ifdef LINUX
    m_roleNames.insert(fdr + F_SHARE, QByteArray("share"));
    m_roleNames.insert(fdr + F_DT, QByteArray("dt"));
    m_roleNames.insert(fdr + F_IOW, QByteArray("iow"));
    m_roleNames.insert(fdr + F_IOR, QByteArray("ior"));
#endif
    m_roleNames.insert(fdr + F_STAT, QByteArray("stat"));
    m_roleNames.insert(fdr + F_FLAGS, QByteArray("flags"));
    m_roleNames.insert(fdr + F_WCHAN, QByteArray("wchan"));
    m_roleNames.insert(fdr + F_WCPU, QByteArray("wcpu"));
    m_roleNames.insert(fdr + F_CPU, QByteArray("cpu"));
    m_roleNames.insert(fdr + F_PMEM, QByteArray("pmem"));
    m_roleNames.insert(fdr + F_START, QByteArray("start"));
    m_roleNames.insert(fdr + F_TIME, QByteArray("time"));
    m_roleNames.insert(fdr + F_CPUNUM, QByteArray("cpunum"));
    m_roleNames.insert(fdr + F_CMD, QByteArray("cmd"));
    m_roleNames.insert(fdr + F_CWD, QByteArray("cwd"));
    m_roleNames.insert(fdr + F_ROOT, QByteArray("root"));
    m_roleNames.insert(fdr + F_CMDLINE, QByteArray("cmdline"));
}

QHash<int, QByteArray> ProcessModel::roleNames() const
{
    return m_roleNames;
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
    case Qt::InitialSortOrderRole: {
        bool numeric = false;
        if (cat)
            cat->sortable(pi).toFloat(&numeric);
        if (numeric)
            return Qt::DescendingOrder;
        return Qt::AscendingOrder;
    }
    case int(ProcessModel::Role::Sort):
        if (!cat) // F_PROCESSNAME probably
            return QVariant();
        return cat->sortable(pi);
    case int(ProcessModel::Role::Number):
        if (!cat) // F_PROCESSNAME probably
            return -1;
        return cat->sortable(pi).toDouble();
    case int(ProcessModel::Role::Type):
        // TODO this is silly: make a virtual in the Category perhaps?
        switch (field) {
        case F_CPU:
        case F_PMEM:
            return QLatin1String("%");
        case F_PID:
        case F_SID:
        case F_TPGID:
        case F_EUID:
        case F_SUID:
        case F_FSUID:
        case F_SGID:
            return QLatin1String("id");
        case F_SIZE:
        case F_RSS:
        case F_TRS:
        case F_DRS:
        case F_STACK:
        case F_SHARE:
        case F_IOW:
        case F_IOR:
            return QLatin1String("size");
        case F_PRI:
        case F_NICE:
        case F_RPRI:
        case F_MAJFLT:
        case F_MINFLT:
        case F_WCPU:
            return QLatin1String("int");
        case F_FLAGS:
            return QLatin1String("flags");
        default:
            return QLatin1String("string");
        }
    default:
        if (role >= int(Role::FirstDataRole))
            // convert the data role to a column and get the DisplayRole
            return data(QAbstractTableModel::index(index.row(), role - int(Role::FirstDataRole)), Qt::DisplayRole);
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
