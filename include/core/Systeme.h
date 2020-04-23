#ifndef H_SYSTEME
#define H_SYSTEME


#include "Pompe.h"
#include "Moteur.h"
#include "Valve.h"
#include "Reservoir.h"
#include "ValveRes.h"
#include "ValveMR.h"
#include "../utils/panne.h"
#include "../utils/xmlparser.h"

#include <vector>
#include <set>
#include <sstream>

using namespace std;

class Pompe;
class Moteur;
class Valve;
class Reservoir;
class ValveMr;
class ValveRes;
class panne;
 
class Systeme{
    friend class MainGui;
    friend class xmlparser;
private:
	double cap_max;
    double conso_mot;
	int duree; //Durée de la simulation en secondes
    int tempsactuel;
	vector<Moteur*> moteurs;
	vector<Reservoir*> reservoirs;
 	vector<Valve*> vannes;
 	
public:
    Systeme(double);
    Systeme(double, double, int, int);
	~Systeme();

	//Getters
	double GetCapacity(){return cap_max;};
    double getConsoMot(){return moteurs[0]->GetConsomation();}
	vector<Moteur *> GetMoteurs(){return moteurs;};
	vector<Valve *> GetVannes(){return vannes;};
	vector<Reservoir *> GetReservoirs(){return reservoirs;};
	//Setters
	void setCapacity(double c);
	//Operations
	void AfficherEtat();
	//Ajouter une mise à jour de la capacite max 
	void UpdateCapaciteMax();
	void updateconso();
    bool isActive();
    bool vanneActive(int, int);
	//Injecter une panne dans le systeme
	friend void apply(Systeme &s);
};
#endif
