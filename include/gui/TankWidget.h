#ifndef TANKWIDGET_H
#define TANKWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>
#include <QPainter>
#include "../core/Reservoir.h"
#include "MainGui.h"
#include "MyQWidget.h"

class MainGui;

class TankWidget : public QLabel, virtual public MyQWidget {
    Q_OBJECT
private:
    MainGui * mainGui;
    Reservoir * r;
    QVBoxLayout tank_layout;
    QHBoxLayout p_layout;
    QFormLayout f_layout;
    QProgressBar progress_c;
    QComboBox combo_etat;
    QLabel label_name;
    void init();

public:
    TankWidget(MainGui *, Reservoir *);
    ~TankWidget();
    void showInfos() override;

public slots:
    void setEtatCombo(int);



};
#endif // TANKWIDGET_H
