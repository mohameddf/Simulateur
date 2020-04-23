#include "../../include/gui/TankWidget.h"


TankWidget::TankWidget(MainGui * _mainGui, Reservoir * _r){
    mainGui = _mainGui;
    r = _r;
    init();
    showInfos();
    setEtatCombo(r->etat);
    QObject::connect(&combo_etat, SIGNAL(currentIndexChanged(int)), this, SLOT(setEtatCombo(int)));

}

TankWidget::~TankWidget(){
    delete mainGui;
    delete r;
}

void TankWidget::init(){
    //setStyleSheet("background-color:red; ");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMaximumHeight(120);
    setMinimumHeight(120);
    setLayout(&tank_layout);


    label_name.setAlignment(Qt::AlignCenter);
    label_name.setStyleSheet("font-weight: bold; font-size:16px;");

    // Capacity progress bar

    progress_c.setTextVisible(true);
    progress_c.setFormat("%p% (%v/%m)");
    progress_c.setRange(0,(int)r->capacity);

    // Etat QTool button
    combo_etat.addItem("VIDE");
    combo_etat.addItem("PLEIN");
    combo_etat.addItem("VIDANGE");
    combo_etat.addItem("REMPLISSAGE");
    // form layout
    f_layout.addRow("Etat :", &combo_etat);

    // layout
    tank_layout.addWidget(&label_name);
    tank_layout.addWidget(&progress_c);
    tank_layout.addLayout(&f_layout);
}

void TankWidget::showInfos(){
    QString title = "Reservoir "+ QString::number(r->num);
    label_name.setText(title);
    combo_etat.setCurrentIndex(r->etat);
    //setEtatCombo(r->etat);
    //progress_c.setValue();

    progress_c.setValue(r->capacity);

}


void TankWidget::setEtatCombo(int etat){

    if(r->SetEtat(static_cast<tank_etat>(etat)))
    {
        switch (etat) {
        case VIDE: {

            setStyleSheet("background-color:red; ");
            mainGui->updateGui();
            break;
        }
        case PLEIN: {
            setStyleSheet("background-color:green;");
            mainGui->updateGui();
            break;
        }
        case VIDANGE:{
            setStyleSheet("background-color:orange;");
            mainGui->updateGui();
            break;
        }
        case REMPLISSAGE: {
            setStyleSheet("background-color:blue;");
            mainGui->updateGui();
            break;
        }
        }

    }
    else
        combo_etat.setCurrentIndex(r->etat);
}


//void TankWidget::paintEvent(QPaintEvent * ){
//    qDebug("aa");
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}
