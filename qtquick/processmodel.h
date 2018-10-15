#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QAbstractTableModel>
#include "../src/proc.h"
class QFont;

class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(ProcessModel)

public:
    // supplemental roles beyond Qt::ItemDataRole
    enum class Role {
        Sort = Qt::UserRole
    };

    ProcessModel(QObject *parent = nullptr);
    ~ProcessModel();
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Q_INVOKABLE int columnWidth(int c, const QFont *font = nullptr);
    Q_INVOKABLE void update();

private:
    Proc m_proc; // the proctologist
    QVector<int> m_pids;
    QVector<int> m_columnWidths = QVector<int>(F_CMDLINE + 1);
};

#endif // PROCESSMODEL_H
