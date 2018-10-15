#include "sortfilterprocessmodel.h"
#include <QDebug>

SortFilterProcessModel::SortFilterProcessModel(QObject *parent)
  : QSortFilterProxyModel (parent)
{
    setSourceModel(&m_processModel);
}

void SortFilterProcessModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << column << order;
    QSortFilterProxyModel::sort(column, order);
}

int SortFilterProcessModel::columnWidth(int c, const QFont *font) {
    return m_processModel.columnWidth(c, font);
}
