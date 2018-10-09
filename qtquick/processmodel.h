#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QAbstractTableModel>
#include "../src/proc.h"

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcessModel)

public:
    ProcessModel(QObject *parent = nullptr);
    ~ProcessModel();
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Proc m_proc; // the proctologist
    QVector<int> m_pids;
};

#endif // PROCESSMODEL_H
