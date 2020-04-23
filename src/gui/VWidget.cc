#include "../../include/gui/VWidget.h"




VWidget::VWidget(MainGui * _mainGui,Valve * _v) {
    mainGui = _mainGui;
    v = _v;
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMaximumSize(40,30);
    setText(QString::fromStdString(_v->nom));
    setCheckable(true);
    setVanne(_v->etat);
    QObject::connect(this, SIGNAL(toggled(bool)), this, SLOT(setVanne(bool)));

}

VWidget::~VWidget(){
    delete mainGui;
    delete v;
}


void VWidget::setVanne(bool etat){
    if(etat)
        if(v->setEtat(OUVERT)){
             setStyleSheet("background-color : green;");
             mainGui->updateGui();

        }else {
            setChecked(!etat);
            mainGui->updateGui();
        }
   else
        if(v->setEtat(FERME)){
             setStyleSheet("background-color : red;");
             mainGui->updateGui();
        }else {
           setChecked(!etat);
             mainGui->updateGui();
        }

}

void VWidget::showInfos(){
   // qDebug("vwidget");
}

