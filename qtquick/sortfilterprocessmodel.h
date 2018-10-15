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
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);

    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;

private:
    ProcessModel m_processModel;
    QVector<fields> m_fields;
};

#endif // SORTFILTERPROCESSMODEL_H
