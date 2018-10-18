#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayoutItem>
#include "../qtquick/sortfilterprocessmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->resizeColumnsToContents();
    while (ui->toolbarStuff->count()) {
        QWidget *tw = ui->toolbarStuff->takeAt(0)->widget();
        ui->mainToolBar->addWidget(tw);
    }
    delete ui->toolbarStuff;
    ui->toolbarStuff = nullptr;
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
