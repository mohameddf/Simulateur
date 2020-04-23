#include "../../include/gui/MainGui.h"


MainGui::MainGui(Systeme * _sys, QVector<panne *> * _pannes, MainGState* _st){
    sys = _sys;
    pannes = *_pannes;
    _pannes = &pannes;
    size_p_vector = pannes.size();
    state = _st;
    init();
    stopSimulation();
}

MainGui::MainGui(Systeme * _sys, MainGState * _st){
    sys = _sys;
    size_p_vector = 0;
    state = _st;
    init();
    QWidget * w = main_layout.itemAt(11)->widget();
    NavBarWidget * n = dynamic_cast<NavBarWidget*>(w);
    n->enableWidgets(false);
}

MainGui::~MainGui(){
    delete sys;
}

void MainGui::init(){
    resize(1000,600);
    setLayout(&main_layout);
    setWindowIcon(QIcon("../../assets/simulator.png"));
    setStyleSheet("background-color: lightgray;");
    // Time
    time.setHMS(0,0,0);
    time = time.addSecs(sys->duree - sys->tempsactuel);
    timerPanne.setTimerType(Qt::PreciseTimer);

    //timerSim.start(1000);
    middle_w = new QWidget();
    middle_w->setMinimumHeight(200);
    middle_w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // middle_w->setStyleSheet("background-color:yellow;");
    // Reservoirs
    main_layout.addWidget(new TankWidget(this, sys->reservoirs[0]), 0, 0 , 1, 2);
    main_layout.addWidget(new TankWidget(this, sys->reservoirs[1]), 0, 3 , 1 , 2);
    main_layout.addWidget(new TankWidget(this, sys->reservoirs[2]), 0, 6 , 1, 2);

    // Pompes
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[0]->pompes[0]), 1, 0);
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[0]->pompes[1]), 1, 1);
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[1]->pompes[0]), 1, 3);
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[1]->pompes[1]), 1, 4);
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[2]->pompes[0]), 1, 6);
    main_layout.addWidget(new PompeWidget(this, sys->reservoirs[2]->pompes[1]), 1, 7);

    // Vannes reservoirs
    main_layout.addWidget(new VWidget(this, sys->vannes[0]), 0, 2);
    main_layout.addWidget(new VWidget(this, sys->vannes[1]), 0, 5);

    // Navigateur de droit
    main_layout.addWidget(new NavBarWidget(this), 0, 8 ,4, 1);

    // Vannes moteurs-pompes
    main_layout.addWidget(middle_w, 2, 0, 1, 8);
    main_layout.addWidget(new VWidget(this, sys->vannes[2]), 2, 2);
    main_layout.addWidget(new VWidget(this, sys->vannes[4]), 2, 3 , 1, 2, Qt::AlignCenter);
    main_layout.addWidget(new VWidget(this, sys->vannes[3]), 2, 5);
    // Moteurs
    main_layout.addWidget(new MoteurWidget(this, sys->moteurs[0]), 3, 0, 1, 2);
    main_layout.addWidget(new MoteurWidget(this, sys->moteurs[1]), 3, 3, 1, 2);
    main_layout.addWidget(new MoteurWidget(this, sys->moteurs[2]), 3, 6, 1, 2);

    // Stretch
    main_layout.setColumnStretch(0,1);
    main_layout.setColumnStretch(1,1);
    main_layout.setColumnStretch(3,1);
    main_layout.setColumnStretch(4,1);
    main_layout.setColumnStretch(6,1);
    main_layout.setColumnStretch(7,1);
    main_layout.setColumnStretch(8,2);

    // Connect signals
    QObject::connect(&timerRept, SIGNAL(timeout()), this, SLOT(updateConsommation()));
    QObject::connect(&timerSim, SIGNAL(timeout()), this, SLOT(stopSimulation()));
    QObject::connect(&timerPanne, SIGNAL(timeout()), this, SLOT(applyPanne()));

}


void MainGui::updateConsommation(){
    //qDebug()<<"Pannes apply"<<&pannes;
    time = time.addSecs(-1);
    if(sys->cap_max >0){
        sys->updateconso();
        updateGui();
        return;
    }
    sys->updateconso();
    updateGui();
    stopSimulation();
}
void MainGui::startSimulation(){
    enableWidgets(true);
    timerSim.setSingleShot(true);
    timerSim.start(QTime(0,0).msecsTo(time));
    preparePanne();
    timerRept.start(1000);
}

void MainGui::stopSimulation(){
    timerSim.stop();
    timerRept.stop();
    timerPanne.stop();
    sys->tempsactuel = sys->duree - QTime(0,0).secsTo(time);
    evaluatePanne();
    enableWidgets(false);
}

void MainGui::applyPanne(){

    if(size_p_vector > 0){
        evaluatePanne();
        pannes.first()->apply(sys);
        pannes.first()->isdone = 1;
    }
    if(size_p_vector > 1){
        pannes.move(0,pannes.size()-1);
        timerPanne.start(QTime(0,0).msecsTo(time) - pannes.first()->duree*1000);
        size_p_vector--;
        return;
    }
    timerPanne.stop();
    pannes.move(0,pannes.size()-1);

}

void MainGui::preparePanne(){
    while(size_p_vector > 0 &&
          pannes.first()->duree*1000 > QTime(0,0).msecsTo(time)){
        pannes.move(0,pannes.size()-1);
        size_p_vector--;
    }
    if(size_p_vector > 0){
        timerPanne.start(QTime(0,0).msecsTo(time) - pannes.first()->duree*1000);
    }
}

void MainGui::evaluatePanne(){
    if(size_p_vector>0)
    if(pannes.last()->isdone == 1){

        if(sys->isActive()){
            pannes.last()->note =1;
        }
        else
            pannes.last()->note =0;
    }
}

void MainGui::retourarriere(){
    stopSimulation();
   int reponse = QMessageBox::question(this, "Sauvegarde", "Voulez vous sauvegarder l'état de la simulation ?", QMessageBox ::Yes | QMessageBox::No | QMessageBox::Cancel);
   switch (reponse) {
   case QMessageBox::Yes:{
        save();
        hide();
        state->GetManager()->PopState();
        state->GetManager()->GetCurrentState()->display();
        state->GetManager()->GetCurrentState()->update();
        break;
   }
   case QMessageBox::No:{
       hide();
       state->GetManager()->PopState();
       state->GetManager()->GetCurrentState()->display();
       state->GetManager()->GetCurrentState()->update();
       break;
     }
   case QMessageBox::Cancel:{
        break;
    }
    default: break;
   }
}
void MainGui::save(){
    //std::cout << state->GetManager()->getLogin().toStdString() << std::endl;
    QTime timestamp;
    //std::cout << timestamp.currentTime().toString().toStdString() << std::endl;
    QFile filename("../../assets/pannes/" + state->GetManager()->getLogin() + timestamp.currentTime().toString() + ".xml");
    //std::cout << state->GetManager()->getLogin().toStdString() + timestamp.currentTime().toString().toStdString() << std::endl;
    xmlparser::WriteinXmlFile(&filename,sys,pannes);
}

void MainGui::afficherNote(){
    stopSimulation();
    QString notes = "Notes";
    int somme =0 ;
    for (auto p : pannes){
        somme += p->note;
        notes = notes +"\n" + "Panne: "+QString::number(p->id)+" => "+QString::number(p->note);
    }
    int note = 10*somme/pannes.size();
    notes = notes + "\n \n"+"Note totale: "+QString::number(note)+"/10";
    QMessageBox::information(this, "Notes", notes);
}

void MainGui::enableWidgets(bool e){
    int count = main_layout.count();
    for (int i =0;i<count;i++) {
        if(i != 11){
            QWidget * w = main_layout.itemAt(i)->widget();
            w->setEnabled(e);
        }

    }
}
void MainGui::updateGui(){
    int count = main_layout.count();
    for (int i =0;i<count;i++) {
        QWidget * w = main_layout.itemAt(i)->widget();
        if(MyQWidget * mw = dynamic_cast<MyQWidget*>(w))
            mw->showInfos();
    }
}
