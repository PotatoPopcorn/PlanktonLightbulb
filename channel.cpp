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
    if(m_automated)
    {
        m_stopReset = true;
        setValue_p(value);
        m_stopReset = false;
    }
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

        m_value = val;
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
    if(!m_automated)
    {
        return;
    }
    m_rwLock.lockForWrite();
    m_fadeTime.restart();
    m_fadeDuration = mSec;
    m_fadeVS = m_value;
    m_fadeVF = newValue;
    m_isFading = true;
    ui->faderSlider->setStyleSheet("background-color:#333");
    m_stopReset = true;
    ui->faderSlider->setValue(m_fadeVF);
    ui->valueLineEdit->setText(QString::number(m_fadeVF));
    m_stopReset = false;
    m_rwLock.unlock();
}


void Channel::on_valueLineEdit_textChanged(const QString &value)
{
    if(m_stopReset) return;
    if(m_isFading)
    {
        stopFade();
    }
    setValue_p(value.toInt());
}

void Channel::on_faderSlider_valueChanged(int position)
{
    if(m_stopReset) return;
    if(m_isFading)
    {
        stopFade();
    }
    setValue_p(position);
}

void Channel::on_networkEnableButton_clicked(bool checked)
{
    m_rwLock.lockForWrite();
    m_automated = checked;
    m_rwLock.unlock();
}

void Channel::setValue_p(int value)
{
    m_rwLock.lockForWrite();
    m_value = value;
    m_stopReset = true;
    ui->faderSlider->setValue(value);
    ui->valueLineEdit->setText(QString::number(value));
    m_stopReset = false;
    m_rwLock.unlock();
}

void Channel::stopFade()
{
    //m_value = m_fadeVF;
    m_isFading = false;
    ui->faderSlider->setStyleSheet("");
}
