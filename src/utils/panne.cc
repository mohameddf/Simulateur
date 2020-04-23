#include "../../include/utils/panne.h"

panne::panne(int i, int _duree){
    id = i;
    piece = getNumberInRange(2) -1;
     if(piece == 0){
           idobjet = getNumberInRange(3);
           parent = -1;
     }
     else{
           idobjet = getNumberInRange(2);
           parent = getNumberInRange(3);
     }
    note = 0;
    duree = getNumberInRange(_duree-1);

    isdone = false;
}
panne::panne(int _id ,int _idp,int _p, int _ido,int _note, int _duree, int _passe) {
	id = _id;
	parent = _idp;
	note = _note;
	duree = _duree;
	idobjet = _ido;
	piece = _p;
	isdone = _passe;
}

panne::~panne(){

}


void panne::affiche() const {
    std::cout << id<<" idpanne"<< std::endl;
    std::cout << piece <<" piece"<< std::endl;
    std::cout << idobjet <<" idobjet"<< std::endl;
    std::cout << note <<" note"<< std::endl;
    std::cout << duree <<" idduree"<<std::endl;
    std::cout << isdone <<" isdone"<< std::endl;
    std::cout << "****************"<<std::endl;
}

void panne::apply(Systeme *s){
  if(piece == 0){ // Dans le cas d'une panne réservoir
    s->GetReservoirs()[idobjet-1]->SetEtat(VIDE);
    }
  if(piece == 1){ //Dans le cas d'une panne pompe
      if(parent != -1){
        s->GetReservoirs()[parent-1]->GetPompe(idobjet-1)->SetEtat(PANNE);
      }
    }
}

int panne::getNumberInRange(int max){

    return rand()%max+1;
}
