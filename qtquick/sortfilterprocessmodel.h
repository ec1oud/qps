#ifndef SORTFILTERPROCESSMODEL_H
#define SORTFILTERPROCESSMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "processmodel.h"

class SortFilterProcessModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(ProcessModel *processModel READ processModel CONSTANT)
public:
    SortFilterProcessModel(QObject *parent = nullptr);

    ProcessModel *processModel() { return &m_processModel; }
    Q_INVOKABLE void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);

private:
    ProcessModel m_processModel;
};

#endif // SORTFILTERPROCESSMODEL_H
