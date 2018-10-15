#include "sortfilterprocessmodel.h"
#include <QDebug>

SortFilterProcessModel::SortFilterProcessModel(QObject *parent)
  : QSortFilterProxyModel (parent)
{
    setSourceModel(&m_processModel);
    setSortRole(int(ProcessModel::Role::Sort));
    // default fields that "top" displays
    m_fields << F_PID << F_USER << F_PRI << F_NICE << F_SIZE << F_RSS
             << F_CPU << F_PMEM << F_TIME << F_PLCY << F_CMD
    // the rest
             << F_CWD << F_ROOT << F_CMDLINE << F_TGID << F_PPID << F_PGID
             << F_SID << F_TTY << F_TPGID << F_GROUP << F_UID << F_EUID << F_SUID
             << F_FSUID << F_GID << F_EGID << F_SGID << F_FSGID
             << F_RPRI << F_TMS << F_AFFCPU << F_SLPAVG << F_NLWP << F_MAJFLT
             << F_MINFLT << F_TRS << F_DRS << F_STACK << F_SHARE << F_DT << F_IOW
             << F_IOR << F_STAT << F_FLAGS << F_WCHAN << F_WCPU << F_START << F_CPUNUM;
    setFilterKeyColumn(F_CMDLINE);
}

void SortFilterProcessModel::setFilterText(QString filterText)
{
    if (m_filterText == filterText)
        return;

    m_filterText = filterText;
    setFilterRegularExpression(filterText);
    emit filterTextChanged(m_filterText);
}

void SortFilterProcessModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << column << m_fields[column] << order;
    QSortFilterProxyModel::sort(m_fields[column], order);
}

int SortFilterProcessModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_fields.count();
}

int SortFilterProcessModel::columnWidth(int c, const QFont *font)
{
    if (c < 0 || c >= m_fields.count())
        return 0;
    return m_processModel.columnWidth(m_fields[c], font);
}

Qt::SortOrder SortFilterProcessModel::initialSortOrder(int column) const
{
    bool ok = false;
    if (column < 0 || column >= m_fields.count())
        return Qt::AscendingOrder;
    int ret = m_processModel.data(m_processModel.index(0, m_fields[column]), Qt::InitialSortOrderRole).toInt(&ok);
    if (ok)
        return Qt::SortOrder(ret);
    else
        return Qt::AscendingOrder;
}

QModelIndex SortFilterProcessModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    int row = QSortFilterProxyModel::mapFromSource(sourceIndex).row();
    fields field = fields(sourceIndex.column());
    return m_processModel.index(row, m_fields.indexOf(field));
}

QModelIndex SortFilterProcessModel::mapToSource(const QModelIndex &proxyIndex) const
{
    QModelIndex rowIndex = QSortFilterProxyModel::mapToSource(proxyIndex);
    int col = -1;
    if (proxyIndex.column() >= 0 && proxyIndex.column() < m_fields.count())
        col = m_fields[proxyIndex.column()];
    return m_processModel.index(rowIndex.row(), col);
}
