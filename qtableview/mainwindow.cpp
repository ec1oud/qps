#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayoutItem>
#include <QScroller>
#include "../qtquick/sortfilterprocessmodel.h"
#include "bargraphdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->resizeColumnsToContents();
    while (ui->toolbarStuff->count()) {
        QWidget *tw = ui->toolbarStuff->takeAt(0)->widget();
        if (!tw)
            continue;
        tw->setAttribute(Qt::WA_AcceptTouchEvents);
        ui->mainToolBar->addWidget(tw);
    }
    delete ui->toolbarStuff;
    ui->toolbarStuff = nullptr;
    BarGraphDelegate *bar = new BarGraphDelegate(this);
    for (int c = 0; c < m_model.columnCount(); ++c) {
        if (m_model.data(m_model.index(0, c), int(ProcessModel::Role::Type)).toString() == QLatin1String("%"))
            ui->tableView->setItemDelegateForColumn(c, bar);
    }
    m_contextMenu->addAction(ui->actionKillProcess);
    QScroller::grabGesture(ui->tableView, QScroller::TouchGesture);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        m_model.processModel()->update();
}

/**
 * @brief MainWindow::setUpdateInterval
 * @param secs how often to refresh the model data, in seconds
 */
void MainWindow::setUpdateInterval(int secs)
{
    if (m_updateInterval == secs)
        return;

    m_updateInterval = secs;
    if (m_timerId >= 0)
        killTimer(m_timerId);
    if (m_updateInterval)
        m_timerId = startTimer(m_updateInterval * 1000);
    emit updateIntervalChanged(m_updateInterval);
}

void MainWindow::setFilter(QString filter)
{
    if (filter == m_model.filterText())
        return;

    m_model.setFilterText(filter);
    emit filterChanged(m_model.filterText());
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex idx = ui->tableView->indexAt(pos);
    QModelIndex pidIdx = m_model.index(idx.row(), F_PID);
    bool ok = false;
    int pid = m_model.data(pidIdx, int(ProcessModel::Role::Number)).toInt(&ok);
    if (ok) {
        QAction * act = m_contextMenu->exec(ui->tableView->mapToGlobal(pos));
        if (act == ui->actionKillProcess)
            qDebug() << pos << "row" << idx.row() << "will kill" << pid;
    }
}
