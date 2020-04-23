#ifndef MAINGUI_H
#define MAINGUI_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QTime>
#include <QtConcurrent/QtConcurrent>
#include "TankWidget.h"
#include "PompeWidget.h"
#include "MoteurWidget.h"
#include "NavBarWidget.h"
#include "VWidget.h"
#include "../core/Systeme.h"
#include "MyQWidget.h"
#include "../states/MainGState.h"
#include "../utils/xmlparser.h"
#include "../utils/panne.h"

class MainGState;
class xmlparser;
class panne;

class MainGui : public QWidget{
    Q_OBJECT
private :
    MainGState* state;
    Systeme * sys;
    QVector<panne*>  pannes;
    int size_p_vector;
    QGridLayout  main_layout;
    QWidget * middle_w;
    QTimer timerSim, timerRept, timerPanne;
    QTime time;
    void init();
public:
    MainGui(Systeme *, QVector<panne *> *, MainGState*);
    MainGui(Systeme *, MainGState*);
    ~MainGui();
    void updateGui();
    void preparePanne();
    void evaluatePanne();
    void enableWidgets(bool e);
    Systeme * getSysteme(){return sys;}
    QString getTime(){return time.toString("hh:mm:ss");}
public slots:
    void updateConsommation();
    void startSimulation();
    void stopSimulation();
    void applyPanne();
    void retourarriere();
    void save();
    void afficherNote();

};


#endif
