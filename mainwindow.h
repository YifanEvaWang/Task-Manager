#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include<QMessageBox>
#include<QDebug>
#include<string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void showTab(int currentTab);
    void onTabChange(int currentTab);
    void onKillProcess();
    void onRefreshProcess();


};

#endif // MAINWINDOW_H
