#include "bargraphdelegate.h"
#include "../qtquick/processmodel.h"
#include <QApplication>

BarGraphDelegate::BarGraphDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void BarGraphDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data(int(ProcessModel::Role::Type)).toString() == QLatin1String("%")) {
        int percent = qRound(index.data(int(ProcessModel::Role::Number)).toDouble());

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = percent;
        progressBarOption.text = index.data().toString();
        progressBarOption.textVisible = true;

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
