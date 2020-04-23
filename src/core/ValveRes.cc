#include "../../include/core/ValveRes.h"


bool ValveRes::setEtat(const of _etat){

    switch (_etat) {
    case FERME: {

            etat = _etat;
            reservoirs[0]->SetEtat(PLEIN);
            reservoirs[1]->SetEtat(PLEIN);
            return true;

    }
    case OUVERT: {
        if(reservoirs[0]->GetEtat() == VIDE || reservoirs[1]->GetEtat() == VIDE){

            etat = _etat;
            reservoirs[0]->SetEtat(REMPLISSAGE);
            reservoirs[1]->SetEtat(REMPLISSAGE);
            *reservoirs[0] + *reservoirs[1];
        return true;
        }
        else {
            etat = FERME;
            return false;
        }
    }
    default: return true;
    }
}
