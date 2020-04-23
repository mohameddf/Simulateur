#include "../../include/gui/MenuGui.h"


MenuGui::MenuGui(MenuState* state): QWidget(){
    menu = state;
    this->setStyleSheet("background-color:white;");
    this->setWindowIcon(QIcon("../../assets/simulator.png"));
    this->setFixedSize(QSize(500, 250));
    this->setCursor(QCursor());
    mainlayout = new QVBoxLayout();
    setLayout(mainlayout);
    newgame = new QPushButton("Nouvelle Simulation");
    charger = new QPushButton("Charger Simulation");
    libre = new QPushButton("Simulation Aléatoire");
    entr = new QPushButton("Entrainement libre");
    quit = new QPushButton("Quitter");
    quit->setStyleSheet("background-color : red");
    mainlayout->addWidget(newgame);
    mainlayout->addWidget(charger);
    mainlayout->addWidget(libre);
    mainlayout->addWidget(entr);
    mainlayout->addWidget(quit);

    //Connecter les signaux
    QObject::connect(newgame, SIGNAL(clicked()), this, SLOT(GenerateFromFile()));
    QObject::connect(charger, SIGNAL(clicked()), this, SLOT(GenerateFromFile()));
    QObject::connect(libre, SIGNAL(clicked()), this, SLOT(GenerateRandom()));
    QObject::connect(entr, SIGNAL(clicked()), this, SLOT(GenerateFree()));
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}


MenuGui::~MenuGui(){
  delete mainlayout;
  delete newgame;
  delete charger;
  delete libre;
  delete quit;
}

void MenuGui::GenerateFromFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Choisir fichier de configuration"), "../../assets/pannes",
            tr("XML file (*.xml);;All Files (*)"));

      if(fileName.toStdString().substr(fileName.toStdString().find_last_of(".") + 1) == "xml") {
                    MainGState * ms = new MainGState(fileName);
                  //  menu->GetManager()->PopState();
                    hide();
                    menu->GetManager()->PushState(ms);
                    menu->GetManager()->GetCurrentState()->update();
      } else {
               QMessageBox::warning(this, "Erreur fichier", "Le fichier séléctionné ne correspond pas ");
      }
}

void MenuGui::GenerateRandom(){
    QString diff = QInputDialog::getText(this, "Selection de la difficulté", "Veuillez séléction la difficulté [0-2]");
    if(diff > 3 && diff < 0){
         QMessageBox::warning(this, "Erreur choix difficulté", "La difficulté doit être comprise entre 0 et 2 ");
    }
    switch(diff.toInt()){
    case 0:{ //Difficulté facile
       
        MainGState * ms = new MainGState(4000.0, 2,15*60,0, 5);
        hide();
        //menu->GetManager()->PopState();
        menu->GetManager()->PushState(ms);
        menu->GetManager()->GetCurrentState()->update();
        break;
    }
    case 1:{
        MainGState * ms = new MainGState(3500.0, 3, 8*60,0, 8);
        //menu->GetManager()->PopState();
        hide();
        menu->GetManager()->PushState(ms);
        menu->GetManager()->GetCurrentState()->update();
       break;
    }case 2:{
        MainGState * ms = new MainGState(2000.0,4,6*60,0,10);
       // menu->GetManager()->PopState();
        hide();
        menu->GetManager()->PushState(ms);
        menu->GetManager()->GetCurrentState()->update();
        break;
    }
    default: break;
    }

}

void MenuGui::GenerateFree(){

    QString res = QInputDialog::getText(this, "Choix capacité et consomtion","Capacité/Consomation");
    QList<QString> l = res.split("/");

    MainGState * ms = new MainGState(l.at(0).toDouble(),l.at(1).toDouble());
    hide();
    //menu->GetManager()->PopState();
    menu->GetManager()->PushState(ms);
    menu->GetManager()->GetCurrentState()->update();
}
