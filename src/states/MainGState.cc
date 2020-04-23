#include "../../include/core/Systeme.h"
#include "../../include/states/MainGState.h"
#include "../../include/gui/MainGui.h"


MainGState::MainGState(double cap, double consomation, int _duree, int tactuel, int nbpannes){
    init(cap, consomation, _duree, tactuel, nbpannes);
}
MainGState::MainGState(QString infile){
    init(infile);
}

MainGState::MainGState(double cap, double consomation){
    sys= new Systeme(cap, consomation,0,0);
    mainGui = new MainGui(sys,this);
}
MainGState::~MainGState(){
        free();
}

void MainGState::init(double cap, double consomation, int _duree, int tactuel, int nbpannes){
  sys = new Systeme(cap, consomation, _duree, tactuel);
  QVector<panne*> pannes;
  for(int i=0; i < nbpannes; i++){
     pannes.push_back(xmlparser::GetRandomPannes(i, _duree));
   }

  xmlparser::sortedPannes(&pannes);
  mainGui = new MainGui(sys, &pannes, this);

}

void MainGState::init(QString infile){
    //Appel au Parser pour charger un fichier
   // std::cout << "DEBUG: Loading simulation file" << std::endl;
    xmlparser parser(infile);
    parser.parseXmlFile();
    sys = parser.GetSysteme();
    mainGui = new MainGui(sys, xmlparser::sortedPannes(parser.getPannes()), this);
}

void MainGState::free(){
        delete sys;
        delete mainGui;
}

void MainGState::update(){
	/**
	 * Délplacer dans une classe
	 */
    display();
    //time_t starttime;
    //time(&starttime);
    //time_t endtime;

    //std::cout << starttime << std::endl;

    //sys->AfficherEtat();

        //Boucle de jeu de la simulation (Ajouter le sortie forcée par l'utilisateur comme condition d'arrêt)


    //sys->AfficherEtat();

    //time(&endtime);

    //std::cout << starttime << std::endl;
    //std::cout << "La simulation à duré "<< endtime - starttime << " Secondes" << std::endl;

}

void MainGState::display(){
    mainGui->show();
}
