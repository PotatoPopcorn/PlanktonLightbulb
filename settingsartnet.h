#ifndef SETTINGSARTNET_H
#define SETTINGSARTNET_H

#include <QWidget>

namespace Ui {
class SettingsArtnet;
}

class SettingsArtnet : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsArtnet(QWidget *parent = nullptr);
    ~SettingsArtnet();

private:
    Ui::SettingsArtnet *ui;
};

#endif // SETTINGSARTNET_H
