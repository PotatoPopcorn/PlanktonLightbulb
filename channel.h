#ifndef CHANNEL_H
#define CHANNEL_H

#include <QDebug>
#include <QIntValidator>
#include <QReadLocker>
#include <QTime>
#include <QWidget>

namespace Ui {
class Channel;
}

class Channel : public QWidget
{
    Q_OBJECT

public:
    explicit Channel(QWidget *parent = 0);
    ~Channel();

    //Setters and Getters
    void setID(int id);
    int getID();

    void setFade(int newValue, int mSec);
    void setValue(int value);
    int getValue();

private slots:

    void on_valueLineEdit_textChanged(const QString &value);

    void on_faderSlider_valueChanged(int position);

    void on_networkEnableButton_clicked(bool checked);

private:
    Ui::Channel *ui;

    int m_id=-1;
    int m_value = 0;

    bool m_isFading = false;
    bool m_automated = true;
    bool m_stopReset = false;
    QTime m_fadeTime;
    int m_fadeDuration = 0;
    int m_fadeVS = 0;
    int m_fadeVF = 0;


    QReadWriteLock m_rwLock;

    void setValue_p(int value);
    void stopFade();

};

#endif // CHANNEL_H
