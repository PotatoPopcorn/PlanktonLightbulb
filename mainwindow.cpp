#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chans = new ChannelManager();
    faderLayout = new QStackedLayout();

    ui->fadersWidget->setLayout(faderLayout);
    faderLayout->addWidget(chans);

    networkHand = new NetworkHandler();

    settingsTab = new SettingsPanel();
    QStackedLayout *settingsLayout = new QStackedLayout();
    settingsLayout->addWidget(settingsTab);
    ui->settingsWidget->setLayout(settingsLayout);

    connect(networkHand, &NetworkHandler::commandRecieved, this, &MainWindow::recieveCommand);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveCommand(QString cmd)
{
    if(cmd.startsWith("SetChan(", Qt::CaseInsensitive))
    {
        QString params = cmd.mid(8, cmd.indexOf(')')-8);
        QRegExp rx("(\,)");
        QStringList query = params.split(rx);
        if(query.count() == 2)
        {
            bool res1;
            bool res2;
            int chan = query.at(0).toInt(&res1);
            int val = query.at(1).toInt(&res2);
            if(res1 && res2)
            {
                chans->setChan(chan, val);
            }
            else
            {
                //Bad Command
                qDebug() << "Invalid Command: " << cmd;
            }

        }
        else
        {
            //Bad Command
            qDebug() << "Invalid Command: " << cmd;
        }
    }
}
