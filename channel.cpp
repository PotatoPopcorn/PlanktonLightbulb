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
    if(!m_automated) return;
    ui->valueLineEdit->setText(QString::number(value));
    ui->faderSlider->setValue(value);
    m_rwLock.lockForWrite();
    stopFade();
    m_value = value;
    m_rwLock.unlock();
}

int Channel::getValue()
{
    m_rwLock.lockForRead();
    int val = 0;
    if(m_isFading)
    {
        val = (((m_fadeVF-m_fadeVS)*m_fadeTime.elapsed()/m_fadeDuration))+m_fadeVS;
        if(m_fadeTime.elapsed() > m_fadeDuration)
        {
            stopFade();
        }
    }
    else
    {
        val = m_value;
    }
    m_rwLock.unlock();
    return val;
}

void Channel::setFade(int newValue, int mSec)
{
    if(!m_automated) return;

    m_rwLock.lockForWrite();
    stopFade();
    m_fadeTime.restart();
    m_fadeDuration = mSec;
    m_fadeVS = m_value;
    m_fadeVF = newValue;
    m_value = newValue;
    m_isFading = true;
    ui->faderSlider->setStyleSheet("background-color:#333;");
    m_rwLock.unlock();
    ui->faderSlider->setValue(newValue);
    ui->valueLineEdit->setText(QString::number(newValue));

}

void Channel::on_valueLineEdit_textEdited(const QString &value)
{
    ui->faderSlider->setValue(value.toInt());
    m_rwLock.lockForWrite();
    stopFade();
    m_value = value.toInt();
    m_rwLock.unlock();
}

void Channel::on_faderSlider_sliderMoved(int position)
{
    ui->valueLineEdit->setText(QString::number(position));
    m_rwLock.lockForWrite();
    stopFade();
    m_value = position;
    m_rwLock.unlock();
}

void Channel::on_networkEnableButton_clicked(bool checked)
{
    m_rwLock.lockForWrite();
    m_automated = checked;
    m_rwLock.unlock();
}

void Channel::stopFade()
{
    m_isFading = false;
    ui->faderSlider->setStyleSheet("");
}
