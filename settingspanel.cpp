#include "settingspanel.h"
#include "ui_settingspanel.h"

SettingsPanel::SettingsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsPanel)
{
    ui->setupUi(this);
    outHand = new OutputHandler();
    ui->outputSettingsWidget->layout()->addWidget(outHand->getWidget());
}

SettingsPanel::~SettingsPanel()
{
    delete ui;
}

void SettingsPanel::on_comboBox_currentIndexChanged(const QString &newDev)
{

    if(newDev == "Dummy")
    {
        outHand->changeDevice("dummy");
    }
    else if (newDev == "Artnet")
    {
        outHand->changeDevice("artnet");
    }
    else if (newDev == "Enttec DMX Pro")
    {
        outHand->changeDevice("enttecpro");
    }
}
