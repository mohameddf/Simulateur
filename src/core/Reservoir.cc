#include <iostream>
#include "../../include/core/Reservoir.h"


//Construit un réservoir et ses deux pompes
Reservoir::Reservoir(int _num, double c, Moteur * m){
	num= _num;
	capacity = c;
	etat = PLEIN;
  moteurs.push_back(m);
  m->SetReservoir(this);
  moteurs.push_back(nullptr);

  pompes.push_back(new Pompe(1,*this,moteurs[0], PRIMAIRE));
  pompes.push_back(new Pompe(2,*this,moteurs[1], SECONDAIRE));

}

Reservoir::~Reservoir(){
	pompes.resize(0);
	moteurs.resize(0);
}

/* 
Pompe* Reservoir::GetPompe(int i){
	if(i >= 0 && i < 2)
		return pompes[i];
	else
		return pompes[2];
}*/

Pompe* Reservoir::GetDispoPompe(){
	for (int i = 0; i < 2; ++i)
	{
		if(pompes[i]->GetEtat() == ARRET)
			return pompes[i];
	}
	return NULL;
}

bool Reservoir::SetEtat(tank_etat _etat){

    switch (_etat) {
    case VIDE:{
        capacity =0;
        setPompes(ARRET);
        etat=_etat;
        return true;
    }
    case PLEIN:{
        if(capacity == 0){
            etat = VIDE;
            return false;
        }
        setPompes(MARCHE);
        etat = _etat;
        return true;
    }
    case REMPLISSAGE:{
        setPompes(ARRET);
        etat = _etat;
        return true;
    }
    case VIDANGE:{
        setPompes(ARRET);
        etat = _etat;
        return true;
    }
    default: return false;
    }
}

void Reservoir::SetCapacity(double c){
    if(c == 0)
     SetEtat(VIDE);
    capacity = c;
}

void Reservoir::setPompes(const etat_t _etat){
    if(pompes[0]->GetEtat() == 1 - _etat)
        pompes[0]->SetEtat(_etat);
    if(pompes[1]->GetEtat() == 1 - _etat)
        pompes[1]->SetEtat(_etat);

}



bool Reservoir::estVide(){
	if(capacity > 0){
		std::cout << "Le Reservoir " << GetNum() << " est encore plein : " << GetCapacity() << "L" << std::endl;
		return false;
	} else{
		this->SetEtat(VIDE);
		std::cout << "Le Reservoir " << GetNum() << " est vide" << std::endl;
		return true;
	}
}

void Reservoir::printInfos(){
	estVide();
}

//Fonction amies
void operator+(Reservoir& a, Reservoir& b){
	double moyenne = 0;
    if(a.capacity > 0 || b.capacity > 0){
		moyenne = (a.capacity + b.capacity)/2;
		a.capacity  = (moyenne);
		b.capacity = (moyenne);
	}
	else{
        //std::cout << "Transfert impossible entre " << a.num << "et " << b.num << std::endl;
	}
}
