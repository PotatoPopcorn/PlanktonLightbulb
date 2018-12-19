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
    ui->faderSlider->setValue(value);
}

int Channel::getValue()
{
    int val = 0;
    if(m_isFading)
    {
        val = (((m_fadeVF-m_fadeVS)*m_fadeTime.elapsed()/m_fadeDuration))+m_fadeVS;

        ui->faderSlider->setValue(val);
        if(m_fadeTime.elapsed() > m_fadeDuration)
        {
            m_fadeVF = val;
            m_isFading = false;
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
