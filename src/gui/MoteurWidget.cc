#include "../../include/gui/MoteurWidget.h"



MoteurWidget::MoteurWidget(MainGui * _mainGui, Moteur * _m ){
    mainGui = _mainGui;
    m = _m;
    init();
    setEtatCombo(m->etat);
    showInfos();
    QObject::connect(&combo_etat, SIGNAL(currentIndexChanged(int)), this, SLOT(setEtatCombo(int)));
    QObject::connect(&combo_t_p, SIGNAL(currentIndexChanged(int)), this, SLOT(setRPCombo(int)));
}

MoteurWidget::~MoteurWidget(){
    delete m;
    delete mainGui;
}

void MoteurWidget::init(){
    setLayout(&m_layout);
    setStyleSheet("background-color: gray;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMaximumHeight(100);
    setMinimumHeight(100);


    label_name.setAlignment(Qt::AlignCenter);
    label_name.setStyleSheet("font-weight: bold; font-size:16px; background-color: rgba(0,0,0,0)");

    combo_t_p.addItem("N/A");
    combo_t_p.addItem("Reservoir 1 Pompe 1", QVariant(QPoint(0,0)));
    combo_t_p.addItem("Reservoir 1 Pompe 2", QVariant(QPoint(0,1)));
    combo_t_p.addItem("Reservoir 2 Pompe 1", QVariant(QPoint(1,0)));
    combo_t_p.addItem("Reservoir 2 Pompe 2", QVariant(QPoint(1,1)));
    combo_t_p.addItem("Reservoir 3 Pompe 1", QVariant(QPoint(2,0)));
    combo_t_p.addItem("Reservoir 3 Pompe 2", QVariant(QPoint(2,1)));
    combo_t_p.setEnabled(false);

    combo_etat.addItem("ARRET");
    combo_etat.addItem("MARCHE");
    combo_etat.setEnabled(false);

    //Form layout
    f_layout.addRow("", &combo_t_p);
    f_layout.addRow("Etat", &combo_etat);

    m_layout.addWidget(&label_name);
    m_layout.addLayout(&f_layout);

}
void MoteurWidget::showInfos(){
    QString title = "Moteur"+ QString::number(m->num);
    label_name.setText(title);
    if(!m->pompe_linked)
        combo_t_p.setCurrentIndex(0);
    else{
        QString curr_t_p = "Reservoir "+
                QString::number(m->res_linked->GetNum())
                +" Pompe "+ QString::number(m->pompe_linked->GetNum());
        combo_t_p.setCurrentText(curr_t_p);
    }
    combo_etat.setCurrentIndex(m->etat);


}

void MoteurWidget::setEtatCombo(int etat){
    if(m->SetEtat(static_cast<etat_t>(etat)))
    switch (etat) {
    case ARRET: {
        setStyleSheet("background-color:red;");
        mainGui->updateGui();
        break;
    }
    case MARCHE: {
        setStyleSheet("background-color:green;");
        mainGui->updateGui();
        break;}
    case PANNE: {
        combo_etat.setCurrentIndex(0); break;}
    }
}

void MoteurWidget::setRPCombo(int index){
    if(index == 0)
        setEtatCombo(0);
    else{
    QPoint tp = combo_t_p.itemData(index).toPoint();
    m->SetPompe(mainGui->getSysteme()->GetReservoirs()[tp.rx()]->GetPompe(tp.ry()));
    }
    mainGui->updateGui();

}
