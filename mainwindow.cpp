/*Author: Yifan Wang
Date: Aug 25th 2021
References:
https://stackoverflow.com/a/4644922
https://blog.csdn.net/ljheee/article/details/70230016
*/

#include "mainwindow.h"
#include "ui_mainwindow.h" 

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::connect(ui->tabs, SIGNAL( currentChanged(int)),this, SLOT( onTabChange(int)));
    QWidget::connect(ui->killButton, SIGNAL(clicked(bool)),this, SLOT(onKillProcess()));
    QWidget::connect(ui->refreshButton, SIGNAL(clicked(bool)),this,SLOT(onRefreshProcess()));
    showTab(1);
}

void MainWindow::showTab(int currentTab)
{

    //if at process page
    if(currentTab == 1)
    {
        ui->processList->clear();
        QDir qd("/proc");
        QString str = qd.entryList().join("\n"), sPid, text, pName, pState, pMemory;
        int head=3, totalProcess=0, nPSleep=0, nPActive=0, nPZombie=0, pid;
        bool isInt;
        QFile file;
        QListWidgetItem *title = new QListWidgetItem("PID\t" + QString::fromUtf8("name") + "\t\t\t" +
                                                                 QString::fromUtf8("status") + "\t" +
                                                                 QString::fromUtf8("memory"), ui->processList);
        ui->processList->addItem(title);

        while(1){
            //get pid
            int s = str.indexOf("\n", head);
            int e = str.indexOf("\n", s+1);
            head = e;

            sPid = str.mid(s+1, e-s-1);
            pid = sPid.toInt(&isInt, 10);
            if(!isInt) break;
            totalProcess++;


            //open the file corressponding to that pid
            file.setFileName("/proc/"+sPid+"/stat");
            if(!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::warning(this, tr("warning"), tr("the file is not readable"), QMessageBox::Ok);
                return;
            }
            text = file.readLine();
            qCritical(text.toUtf8().constData());

            if(text.length()==0)
            {
                QMessageBox::warning(this, tr("warning"), tr("no stat"), QMessageBox::Ok);
                break;
            }
            s = text.indexOf("(");
            e = text.indexOf(")");
            pName = text.mid(s+1, e-s-1);
            pName.trimmed();
            pState = text.section(" ", 2,2);
            pMemory = text.section(" ",22,22);

            switch(pState.at(0).toLatin1())
            {
                case 'S':
                    nPSleep++;
                break;
                case 'R':
                    nPActive++;
                break;
                case 'Z':
                    nPZombie++;
                break;
                default:
                break;
            }

            if(pName.length()>=12)
            {
                QListWidgetItem *item =
                        new QListWidgetItem(sPid + "\t" + pName + "\t\t" +
                                            pState + "\t" +
                                            pMemory, ui->processList);
                ui->processList->addItem(item);
            }

            ui->nPLabel->setText(QString::number(totalProcess,10));
            ui->nPActiveLabel->setText(QString::number(nPActive, 10));
            ui->nPSleepLabel->setText(QString::number(nPSleep,10));
            ui->nPZombieLabel->setText(QString::number(nPZombie,10));


        }
    }
}

void MainWindow::onKillProcess()
{
    QListWidgetItem *selectedProcess = ui->processList->currentItem();
    QString process = selectedProcess->text();
    QString pid = process.section("\t", 0,0);
    system("kill "+pid.toLatin1());
    QMessageBox::warning(this, tr("killed"), QString::fromUtf8("this process has been successfully killed"), QMessageBox::Ok);
    showTab(1);

}

void MainWindow::onTabChange(int currentTab)
{
    showTab(currentTab);
    return;
}

void MainWindow::onRefreshProcess(){
    showTab(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

