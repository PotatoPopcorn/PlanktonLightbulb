#include "settingsartnet.h"
#include "ui_settingsartnet.h"

SettingsArtnet::SettingsArtnet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsArtnet)
{
    ui->setupUi(this);
}

SettingsArtnet::~SettingsArtnet()
{
    delete ui;
}
