#ifndef POMPEWIDGET_H
#define POMPEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QDebug>
#include "../core/Pompe.h"
#include "MainGui.h"
#include "MyQWidget.h"

class MainGui;

class PompeWidget : public QLabel, public MyQWidget{
    Q_OBJECT
private:
    Pompe * p;
    MainGui * mainGui;
    QVBoxLayout p_layout;
    QFormLayout f_layout;
    QComboBox combo_etat, combo_m;
    QLabel label_name;
    void init();
public:
    PompeWidget(MainGui *,Pompe *);
    ~PompeWidget();
    void showInfos() override;
public slots:
    void setEtatCombo(int);
    void setMoteurCombo(int = 0);
};

#endif
