#ifndef MOTEURWIDGET_H
#define MOTEURWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include "../core/Moteur.h"
#include "MainGui.h"
#include "MyQWidget.h"

class MainGui;
class MoteurWidget : public QLabel , public MyQWidget{
    Q_OBJECT
private:
    Moteur * m;
    MainGui * mainGui;
    QVBoxLayout m_layout;
    QFormLayout f_layout;
    QComboBox combo_t_p, combo_etat;
    QLabel label_name;
    void init();

public:
    MoteurWidget(MainGui *, Moteur *);
    ~MoteurWidget();
    void showInfos() override;
public slots:
    void setEtatCombo(int);
    void setRPCombo(int);
};

#endif
