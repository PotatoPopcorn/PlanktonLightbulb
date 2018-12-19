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
    m_rwLock.lockForWrite();
    ui->faderSlider->setValue(value);
    ui->valueLineEdit->setText(QString::number(value));
    m_value = value;
    m_rwLock.unlock();
}

int Channel::getValue()
{
    m_rwLock.lockForRead();
    int val = 0;
    if(m_isFading)
    {
        val = (((m_fadeVF-m_fadeVS)/m_fadeDuration)*m_fadeTime.elapsed())+m_fadeVS;
        ui->faderSlider->setValue(val);
        ui->valueLineEdit->setText(QString::number(val));
        m_value = val;
        if(val == m_fadeVF)
        {
            m_isFading = false;
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
    m_rwLock.lockForWrite();
    m_fadeTime.restart();
    m_fadeDuration = mSec;
    m_fadeVS = m_value;
    m_fadeVF = newValue;
    m_isFading = true;
    m_rwLock.unlock();
}


void Channel::on_valueLineEdit_textChanged(const QString &value)
{
    ui->faderSlider->setValue(value.toInt());

}

void Channel::on_faderSlider_valueChanged(int position)
{
    ui->valueLineEdit->setText(QString::number(position));
    m_rwLock.lockForWrite();
    m_value = position;
    m_rwLock.unlock();
}
