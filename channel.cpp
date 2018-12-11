#include "channel.h"
#include "ui_channel.h"

Channel::Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channel)
{
    ui->setupUi(this);
    ui->valueLineEdit->setValidator(new QIntValidator(0, 255, this));
}

Channel::~Channel()
{
    delete ui;
}


void Channel::setID(int id)
{
    m_id=id;
    ui->idLabel->setText(QString::number(m_id));
}

int Channel::getID()
{
    return m_id;
}

void Channel::setValue(int value)
{
    ui->faderSlider->setValue(value);
    ui->valueLineEdit->setText(QString::number(value));
    m_value = value;
}

int Channel::getValue()
{
    return m_value;
}

void Channel::on_valueLineEdit_textChanged(const QString &value)
{
    ui->faderSlider->setValue(value.toInt());

}

void Channel::on_faderSlider_valueChanged(int position)
{
    ui->valueLineEdit->setText(QString::number(position));
    m_value = position;
}
