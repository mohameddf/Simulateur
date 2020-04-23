#include "../../include/gui/NavBarWidget.h"


NavBarWidget::NavBarWidget(MainGui * _mainGui){
    mainGui = _mainGui;
    init();
    showInfos();
}

NavBarWidget::~NavBarWidget(){
    delete mainGui;
}

void NavBarWidget::init(){
    setLayout(&v_layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setStyleSheet("background-color : lightgray;");
    setMaximumWidth(300);
    setMinimumWidth(200);
    v_layout.setAlignment(Qt::AlignTop);

    btnStart.setText("Start");
    btnPause.setText("Pause");
    btnsave.setText("Sauvegarde");
    btnNote.setText("Afficher notes");
    btnquitter.setText("Retour");

    /*btnPause.setStyleSheet("font-size: 17px; font-weight:bold;");
    btnStart.setStyleSheet("font-size: 17px; font-weight:bold;");
    btnsave.setStyleSheet("font-size: 17px; font-weight:bold;");
    btnNote.setStyleSheet("font-size: 17px; font-weight:bold;");
    btnquitter.setStyleSheet("background-color:red;font-size: 17px; font-weight:bold; color:white;");
    */
    label_time.setDigitCount(8);
    label_time.setMinimumHeight(50);
    label_cap.setMinimumHeight(30);
    label_conso.setMinimumHeight(30);
    label_time.setSegmentStyle(QLCDNumber::Flat);
    label_cap.setSegmentStyle(QLCDNumber::Flat);
    label_conso.setSegmentStyle(QLCDNumber::Flat);

    v_layout.addWidget(&label_time);
    f_layout.addRow("Capacité", &label_cap);
    f_layout.addRow("Consommation",&label_conso);
    v_layout.addLayout(&f_layout);
    v_layout.addWidget(&btnStart);
    v_layout.addWidget(&btnPause);
    v_layout.addWidget(&btnsave);
    v_layout.addWidget(&btnNote);
    v_layout.addWidget(&btnquitter);
    QObject::connect(&btnsave, SIGNAL(clicked()), mainGui, SLOT(save()));
    QObject::connect(&btnquitter, SIGNAL(clicked()), mainGui, SLOT(retourarriere()));
    QObject::connect(&btnPause, SIGNAL(clicked()), mainGui, SLOT(stopSimulation()));
    QObject::connect(&btnStart, SIGNAL(clicked()), mainGui, SLOT(startSimulation()));
    QObject::connect(&btnNote, SIGNAL(clicked()), mainGui, SLOT(afficherNote()));
}
void NavBarWidget::showInfos(){
    label_time.display(mainGui->getTime());
    label_cap.display(mainGui->getSysteme()->GetCapacity());
    label_conso.display(mainGui->getSysteme()->getConsoMot());

}

void NavBarWidget::enableWidgets(bool e){
    btnStart.setEnabled(e);
    btnPause.setEnabled(e);
    btnsave.setEnabled(e);
    btnNote.setEnabled(e);
}
