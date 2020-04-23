#ifndef NAVBARWIDGET_H
#define NAVBARWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLCDNumber>
#include "MyQWidget.h"
#include "MainGui.h"
class NavBarWidget : public QWidget, public MyQWidget{
private:
    QVBoxLayout v_layout;
    QFormLayout f_layout;
    QLCDNumber label_conso, label_cap, label_time;
    QPushButton btnStart, btnPause, btnquitter, btnsave, btnNote;
    MainGui * mainGui;

    void init();
public:
    NavBarWidget(MainGui *);
    ~NavBarWidget();
    void showInfos() override;
    void enableWidgets(bool);
};
#endif
