#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include "../qtquick/sortfilterprocessmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int updateInterval READ updateInterval WRITE setUpdateInterval NOTIFY updateIntervalChanged)
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int updateInterval() const { return m_updateInterval; }
    QString filter() const { return m_model.filterText(); }

public slots:
    void setUpdateInterval(int secs);
    void setFilter(QString filter);

signals:
    void updateIntervalChanged(int updateInterval);
    void filterChanged(QString filter);

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void on_actionQuit_triggered();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    SortFilterProcessModel m_model;
    QMenu *m_contextMenu = new QMenu(this);
    int m_timerId = -1;
    int m_updateInterval = -1;
};

#endif // MAINWINDOW_H
