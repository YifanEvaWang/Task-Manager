#include "mainwindow.h"
#include "ui_mainwindow.h" 




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::connect( ui->tabs, SIGNAL( currentChanged(int) ),
                      this, SLOT( onTabChange(int)));
}

void MainWindow::showTab(int currentTab)
{

    //if at process page
    if(currentTab == 0)
    {
        ui->processList->clear();
        QDir qd("/proc");
        QString str = qd.entryList().join("\n"), sPid, text, pName, pState, pMemory;
        bool done;
        int head=3, totalProcess=0, pid, nPSleep=0, nPActive=0, nPZombie=0;
        QFile file;
        QListWidgetItem *title = new QListWidgetItem("PID\t" + QString::fromUtf8("name") + "\t\t" +
                                                                 QString::fromUtf8("status") + "\t" +
                                                                 QString::fromUtf8("memory"), ui->processList);
        ui->processList->addItem(title);

        while(1){
            //get pid
            int s = str.indexOf("\n", head);
            int e = str.indexOf("\n", s+1);
            head = e;

            sPid = str.mid(s+1, e-s+1);
            pid = sPid.toInt(&done, 10);
            totalProcess++;

            qCritical();

            if(!done) break;

            //open the file corressponding to that pid
            file.setFileName("/proc/"+sPid+"/stat");
            if(!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::warning(this, tr("warning"), tr("the file is not readable"), QMessageBox::Yes);
                return;
            }
            text = file.readLine();
            qCritical("hi");
            qCritical( qUtf8Printable(text) );
            if(text.length()==0)
            {
                QMessageBox::warning(this, tr("warning"),tr("no process?"),QMessageBox::Yes);
                break;
            }
            s = text.indexOf("(");
            e = text.indexOf(")");
            pName = text.mid(s+1, e-s+1);
            pState = text.section("", 2,2);
            pMemory = text.section("",22,22);

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

            QMessageBox::warning(this, tr("warning"),tr("no process"),QMessageBox::Yes);
            ui->nPLabel->setText(QString::number(totalProcess,10));
            ui->nPActiveLabel->setText(QString::number(nPActive, 10));
            ui->nPSleepLabel->setText(QString::number(nPSleep,10));
            ui->nPZombieLabel->setText(QString::number(nPZombie,10));


        }
    }
}

void MainWindow::onTabChange(int currentTab)
{
    showTab(currentTab);
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}
