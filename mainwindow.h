#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <QTextCodec>
#include <QMetaType>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addItemToChattingRoom(QString text);


private:
    Ui::MainWindow *ui;
    int firstConnect;

private slots:
    void showTab(int currentTab);
    void onTabChange(int currentTab);
    void onKillProcess();
    void onRefreshProcess();

};

#endif // MAINWINDOW_H
