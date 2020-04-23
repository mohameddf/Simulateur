#include "../../include/core/ValveMR.h"

bool ValveMr::alimente(Moteur& m,  Reservoir& r){
	Pompe* tmp;	
	if(m.GetReservoir() != &r){ 
		tmp =  r.GetDispoPompe();
		if(tmp){
            m.SetReservoir(&r);
            m.SetPompe(tmp);
			return true;
		}
	}
	return false;
}


bool ValveMr::setEtat(const of _etat){
    switch (_etat) {
        case FERME:{
            if(moteurs[0]->GetEtat() == MARCHE
                    && moteurs[0]->GetNumero() != moteurs[0]->GetReservoir()->GetNum()
                    && (moteurs[0]->GetReservoir()->GetNum() == reservoirs[1]->GetNum()
                        ||moteurs[0]->GetReservoir()->GetNum() == reservoirs[0]->GetNum()))
            {
                moteurs[0]->GetPompe()->SetEtat(ARRET);
            }
            if(moteurs[1]->GetEtat() == MARCHE
                    && moteurs[1]->GetNumero() != moteurs[1]->GetReservoir()->GetNum()
                    && (moteurs[1]->GetReservoir()->GetNum() == reservoirs[0]->GetNum()
                        ||moteurs[1]->GetReservoir()->GetNum() == reservoirs[1]->GetNum()))
            {
                moteurs[1]->GetPompe()->SetEtat(ARRET);
            }

            etat = _etat;
            return true;
        }
        case OUVERT:{
            // Verifier si Moteur est en ARRET , et S'il existe au moins une pompe en ARRET
            if((moteurs[0]->GetEtat() == ARRET
                    && (reservoirs[1]->GetPompe(0)->GetEtat()== ARRET
                        || reservoirs[1]->GetPompe(1)->GetEtat() == ARRET)
                )
               || (moteurs[1]->GetEtat() == ARRET
                   && (reservoirs[0]->GetPompe(0)->GetEtat()== ARRET
                       || reservoirs[0]->GetPompe(1)->GetEtat() == ARRET)
                   )
               )
            {
                etat = _etat;
                return true;
            }else{
                return false;
            }
        }
    }

    return false;
}
/*
void ValveMr::printInfos(){
	Valve::printInfos();
	std::cout << reservoirs[0] << "/" << reservoirs[1] << "/" << moteurs[0] << "/" << moteurs[1] << std::endl;
} 
*/
