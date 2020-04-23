#ifndef VWIDGET_H
#define VWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "../core/Valve.h"
#include "MainGui.h"
#include "MyQWidget.h"

class MainGui;

class VWidget :  public QPushButton, public MyQWidget {
    Q_OBJECT
private:
    MainGui * mainGui;
    Valve * v;
public:
    VWidget(MainGui *, Valve *);
    ~VWidget();
    void showInfos() override;
public slots:
    void setVanne(bool = false);
};
#endif
