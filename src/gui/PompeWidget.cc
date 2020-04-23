#include "../../include/gui/PompeWidget.h"


PompeWidget::PompeWidget(MainGui * _mainGui,Pompe * _p){
    mainGui = _mainGui;
    p = _p;
    init();
    showInfos();
    setEtatCombo(p->etat);
    QObject::connect(&combo_etat, SIGNAL(currentIndexChanged(int)), this, SLOT(setEtatCombo(int)));
    QObject::connect(&combo_m, SIGNAL(currentIndexChanged(int)), this, SLOT(setMoteurCombo(int)));


}

PompeWidget::~PompeWidget(){
    delete mainGui;
    delete p;
}

void PompeWidget::init(){
    setLayout(&p_layout);
    setMaximumHeight(80);
    setMinimumSize(140,80);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    combo_m.addItem("N/A");
    combo_m.addItem("1", QVariant(1));
    combo_m.addItem("2", QVariant(2));
    combo_m.addItem("3", QVariant(3));



    combo_etat.addItem("ARRET");
    combo_etat.addItem("MARCHE");
    combo_etat.addItem("PANNE");

    label_name.setAlignment(Qt::AlignCenter);
    label_name.setStyleSheet("font-weight: bold; font-size:14px; background-color: rgba(0,0,0,0)");
    label_name.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // Form layout
    f_layout.addRow("Moteur", &combo_m);
    f_layout.addRow("Etat", &combo_etat);

    p_layout.addWidget(&label_name);
    p_layout.addLayout(&f_layout);


}

void PompeWidget::showInfos(){
    QString title = "Pompe "+ QString::number(p->num);
    label_name.setText(title);

    if(p->mot_linked)
        combo_m.setCurrentIndex(p->mot_linked->GetNumero());
    else combo_m.setCurrentIndex(0);
    //qDebug()<<"Moteur-"<<num_m<<" Pompe-"<<num_etat;
    combo_etat.setCurrentIndex(p->etat);


}

void PompeWidget::setEtatCombo(int etat){
    if(etat == MARCHE)
        if(p->res_linked->GetNum() != combo_m.currentIndex() &&
        !mainGui->getSysteme()->vanneActive(p->res_linked->GetNum(), combo_m.currentIndex()))
        {
            combo_etat.setCurrentIndex(p->etat);
            return;
        }

    if(p->SetEtat(static_cast<etat_t>(etat)))
    switch (etat) {
        case ARRET: {
        setStyleSheet("background-color:red;");
        mainGui->updateGui();
        break;
    }
        case MARCHE: {
        setStyleSheet("background-color:green;");
        mainGui->updateGui();
        break;
    }
        case PANNE: {
        setStyleSheet("background-color:orange;");
        mainGui->updateGui();
        break;
    }
    }

    else
        combo_etat.setCurrentIndex(p->etat);

}

void PompeWidget::setMoteurCombo(int index){
    //qDebug()<< "pompe_combo_moteur"<< index;
    if(index == 0)
        p->SetMoteur(nullptr);
    else{
        if(p->res_linked->GetNum() == index ||
                mainGui->getSysteme()->vanneActive(p->res_linked->GetNum(), index))
            p->SetMoteur(mainGui->getSysteme()->GetMoteurs()[index-1]);
    }

    mainGui->updateGui();


}

