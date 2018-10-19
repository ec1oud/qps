#ifndef BARGRAPHDELEGATE_H
#define BARGRAPHDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class BarGraphDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BarGraphDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // BARGRAPHDELEGATE_H
