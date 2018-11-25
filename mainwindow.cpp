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

}

MainWindow::~MainWindow()
{
    delete ui;
}
