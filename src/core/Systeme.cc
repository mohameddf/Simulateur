#include "../../include/core/Systeme.h"

Systeme::Systeme(double cap, double consomation, int _duree, int tactuel){

	cap_max = cap;
    duree = _duree;
    tempsactuel = tactuel;
	//Initialise les 3 moteurs
	for (int i = 0; i < 3; ++i){
	    moteurs.push_back( new Moteur(i+1, consomation));
	}
	    //Crée les 3 réservoirs avec la configuration de base
	reservoirs.push_back(new Reservoir(1, (2*(cap/5)), moteurs[0]));
	reservoirs.push_back(new Reservoir(2, (cap/5), moteurs[1]));
	reservoirs.push_back(new Reservoir(3, (2*(cap/5)), moteurs[2]));

    //On va creer les tableau de moteurs et de reservoirs
    std::vector<Reservoir*> v_vt21 = {reservoirs[1], reservoirs[0]};
    std::vector<Reservoir*> v_vt23 = {reservoirs[1], reservoirs[2]};
	std::vector<Reservoir*> v_vt13 = {reservoirs[0], reservoirs[2]};

	//Moteurs
	std::vector<Moteur*> v_v12 = {moteurs[0], moteurs[1]};
	std::vector<Moteur*> v_v23 = {moteurs[1], moteurs[2]};
	std::vector<Moteur*> v_v13 = {moteurs[0], moteurs[2]};
 

	//Ajout des vannes toutes dans l'état fermé 
    vannes.push_back(new ValveRes("VT12", "VT21", FERME, v_vt21));
    vannes.push_back(new ValveRes("VT23", "VT32", FERME, v_vt23));
    vannes.push_back(new ValveMr("V12", "V21", FERME, v_vt21, v_v12));
    vannes.push_back(new ValveMr("V23", "V32", FERME, v_vt23, v_v23));
    vannes.push_back(new ValveMr("V13", "V31", FERME, v_vt13, v_v13));


}
Systeme::Systeme(double cap){
	cap_max = cap;
	duree = 3;
	//Initialise les 3 moteurs
	for (int i = 0; i < 3; ++i){
	    moteurs.push_back( new Moteur(i+1, 1.9));
	}
	    //Crée les 3 réservoirs avec la configuration de base
	reservoirs.push_back(new Reservoir(1, (2*(cap/5)), moteurs[0]));
	reservoirs.push_back(new Reservoir(2, (cap/5), moteurs[1]));
	reservoirs.push_back(new Reservoir(3, ((2*(cap)/5)), moteurs[2]));
        //Relier les pompes avec leur réservoirs et moteurss
         /*for (int i = 0; i < 3; ++i)
        {
        reservoirs[i]->GetPompe(0)->SetMoteur(moteurs[i]);
        }

	for (int i = 0; i < 3; ++i)
	{
       moteurs[i]->SetPompe(reservoirs[i]->GetPompe(0));
       reservoirs[i]->GetPompe(0)->SetMoteur(moteurs[i]);
        }*/
        //On va creer les tableau de moteurs et de reservoirs
        std::vector<Reservoir*> v_vt21 = {reservoirs[1], reservoirs[0]};
        std::vector<Reservoir*> v_vt23 = {reservoirs[1], reservoirs[2]};
        std::vector<Reservoir*> v_vt13 = {reservoirs[0], reservoirs[2]};

	//Moteurs
	std::vector<Moteur*> v_v12 = {moteurs[0], moteurs[1]};
	std::vector<Moteur*> v_v23 = {moteurs[1], moteurs[2]};
	std::vector<Moteur*> v_v13 = {moteurs[0], moteurs[2]};


    //Ajout des vannes toutes dans l'état fermé
    vannes.push_back(new ValveRes("VT12", "VT21", FERME, v_vt21));
    vannes.push_back(new ValveRes("VT23", "VT32", FERME, v_vt23));
    vannes.push_back(new ValveMr("V12", "V21", FERME, v_vt21, v_v12));
    vannes.push_back(new ValveMr("V23", "V32", FERME, v_vt23, v_v23));
    vannes.push_back(new ValveMr("V13", "V31", FERME, v_vt13, v_v13));
}


Systeme::~Systeme(){
	reservoirs.resize(0);
	vannes.resize(0);
	moteurs.resize(0);
	
}

void Systeme::AfficherEtat(){
	
    for (int i = 0; i  < 3; ++i)
	{
		reservoirs[i]->printInfos();
	}
	
    for (int i = 0; i < 3;++i)
	{
		reservoirs[i]->GetPompe(0)->printInfos();
		//reservoirs[i]->GetPompe(1)->printInfos();
	}
    for (int i = 0;  i < 3; ++i)
	{
		moteurs[i]->printInfos();
	}
	for (int i = 0; i < 5; ++i)
	{
		vannes.at(i)->printInfos();
		//vannes[i]->ChangerEtat();
		//vannes[i]->printInfos();
	}
	
} 
void Systeme::setCapacity(double c){
	cap_max = c;
}


/*Met à jours la capacité de chaque réservoirs plus la capacité totale*/
void Systeme::updateconso(){
    for (int i = 0; i < 3; ++i)
    {
        if(moteurs[i]->GetEtat() == MARCHE)
            consomme(*(moteurs[i]->GetReservoir()), *moteurs[i]);
	}
	UpdateCapaciteMax();
}

void Systeme::UpdateCapaciteMax(){
	double nouvellecapmax = 0;
    for (int i = 0; i < 3; ++i)
	{

		nouvellecapmax += reservoirs[i]->GetCapacity();
	}
    if( nouvellecapmax > 1)
        setCapacity(nouvellecapmax);
    else
        setCapacity(0);
}

bool Systeme::isActive(){
    if(moteurs[0]->GetEtat() == MARCHE
       && moteurs[1]->GetEtat() == MARCHE
       && moteurs[2]->GetEtat() == MARCHE)
        return true;

    return false;
}

bool Systeme::vanneActive(int r_num, int m_num){
    QString nom = "V"+QString::number(r_num)+QString::number(m_num);
    int size = vannes.size();
    for(int i=2; i< size; i++){
        if(nom.toStdString() == vannes[i]->nom
                || nom.toStdString() == vannes[i]->nom2)
            if(vannes[i]->etat == OUVERT)
                return true;
    }
    return false;
}


