#ifndef CHANNEL_H
#define CHANNEL_H

#include <QDebug>
#include <QIntValidator>
#include <QReadLocker>
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

    void setValue(int value);
    int getValue();

private slots:

    void on_valueLineEdit_textChanged(const QString &value);

    void on_faderSlider_valueChanged(int position);

private:
    Ui::Channel *ui;

    int m_id=-1;
    int m_value = 0;

    QReadWriteLock m_rwLock;
};

#endif // CHANNEL_H
