
#include "../../include/core/Valve.h"

Valve::Valve(of _etat, std::string _nom, std::string _nom2){
	etat = _etat;
	nom = _nom;
    nom2 = _nom2;
}

Valve::~Valve(){

}
bool Valve::setEtat(of){
    //std::cout<<"setEtat from Valve class"<<std::endl;
    return false;
}
	

void Valve::printInfos(){
	std::cout << GetNom()<<"/"<<GetEtat()<<"/";
}
  
