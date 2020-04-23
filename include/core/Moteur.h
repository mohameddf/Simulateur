#ifndef H_MOTEUR
#define H_MOTEUR


#include "Reservoir.h"
#include "Pompe.h"


class Pompe;
class Reservoir;

class Moteur{
    friend class MoteurWidget;
    friend class Systeme;
private:
	int  num; //Numero du moteur
	etat_t etat;
	Reservoir* res_linked; //Nom du réservoir qui l'alimente
	Pompe* pompe_linked; //Pompe qui lui envoie du carburant
	double consomation;

public:

	Moteur(int n, double c);
         ~Moteur();
	//Getters

	int GetNumero(){return num;}; 
	etat_t GetEtat(){return etat;};
	Pompe* GetPompe(){return pompe_linked;};
	Reservoir* GetReservoir(){return res_linked;};
	double GetConsomation() const {return consomation;};
	//Setters
	bool SetEtat(etat_t etat);
	void SetPompe(Pompe * po);
	void SetReservoir(Reservoir * res);
	friend void consomme(Reservoir& r, Moteur& m);
	//Affiche information
 	void printInfos(); 
};

 
#endif
