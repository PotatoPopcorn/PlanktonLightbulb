#include "channel.h"
#include "ui_channel.h"

Channel::Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channel)
{
    ui->setupUi(this);
    ui->valueLineEdit->setValidator(new QIntValidator(0, 255, this));
    m_fadeTime.start();
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
    if(m_rwLock.tryLockForWrite())
    {
        m_value = value;
        ui->faderSlider->setValue(value);
        ui->valueLineEdit->setText(QString::number(value));
        m_rwLock.unlock();
    }
}

int Channel::getValue()
{   
    int val = 0;
    if(m_isFading)
    {
        val = (((m_fadeVF-m_fadeVS)*m_fadeTime.elapsed()/m_fadeDuration))+m_fadeVS;

        if(m_fadeTime.elapsed() > m_fadeDuration)
        {
            m_value = val;
            m_isFading = false;
            ui->faderSlider->setStyleSheet("");
        }
    }
    else
    {
        val = m_value;
    }
    return val;

}

void Channel::setFade(int newValue, int mSec)
{
    m_rwLock.lockForWrite();
    m_fadeTime.restart();
    m_fadeDuration = mSec;
    m_fadeVS = m_value;
    m_fadeVF = newValue;
    m_isFading = true;
    ui->faderSlider->setStyleSheet("background-color:#333");
    ui->faderSlider->setValue(m_fadeVF);
    ui->valueLineEdit->setText(QString::number(m_fadeVF));
    m_rwLock.unlock();
}


void Channel::on_valueLineEdit_textChanged(const QString &value)
{
    setValue(value.toInt());
}

void Channel::on_faderSlider_valueChanged(int position)
{
    setValue(position);
}
