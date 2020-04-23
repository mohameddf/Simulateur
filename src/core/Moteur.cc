#include <iostream>

#include "../../include/core/Moteur.h"
#include "../../include/core/Reservoir.h"
#include "../../include/core/Pompe.h"


Moteur::Moteur(int _num, double _consomation){
    num = _num;
    etat = ARRET;
    res_linked = nullptr;
    pompe_linked = nullptr;
    consomation = _consomation;

} 

Moteur::~Moteur(){
	delete res_linked;
	delete pompe_linked;
}

void Moteur::SetPompe(Pompe * p){
    if(p){
        if(pompe_linked && p != pompe_linked)
            pompe_linked->SetMoteur(nullptr);
        pompe_linked = p;
        res_linked = p->GetReservoir();
    }else {

        pompe_linked = nullptr;
        res_linked = nullptr;


    }

}
bool Moteur::SetEtat(etat_t _etat){
    if(pompe_linked){
        etat = _etat;
        return true;
    }
    etat = ARRET;
    return true;
}
void Moteur::SetReservoir(Reservoir * res){
    res_linked = res;
}
void Moteur::printInfos(){
	std::cout << "Moteur: "<< GetNumero() << "/" << GetEtat() << "/" << GetReservoir()->GetNum() << "/" << GetPompe()->GetNum() << std::endl; 
}  

void consomme(Reservoir& r, Moteur& m){

        if(r.GetCapacity() > 0 ){

	    double nvcap = r.GetCapacity() - m.GetConsomation();
			r.SetCapacity(nvcap);	
		}
		else{
            r.SetCapacity(0);
		}
}   
