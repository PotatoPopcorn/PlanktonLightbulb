#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QDebug>
#include <QWidget>

#include "outputhandler.h"

namespace Ui {
class SettingsPanel;
}

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPanel(QWidget *parent = nullptr);
    ~SettingsPanel();

    OutputHandler* getOutputHandler();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::SettingsPanel *ui;

    OutputHandler *outHand;
    QWidget *outWidget;
};

#endif // SETTINGSPANEL_H
