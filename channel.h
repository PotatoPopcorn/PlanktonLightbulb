#ifndef CHANNEL_H
#define CHANNEL_H

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

private:
    Ui::Channel *ui;

    int m_id=-1;
};

#endif // CHANNEL_H
