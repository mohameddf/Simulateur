#ifndef H_POMPE
#define H_POMPE

#ifndef H_ETAT
#define H_ETAT
enum etat_t{
	ARRET = 0,
	MARCHE,
	PANNE
};
#endif


#include "Moteur.h"
#include "Reservoir.h"




class Moteur;
class Reservoir;


enum nb{
	PRIMAIRE = 1,
	SECONDAIRE
};



class Pompe{
    friend class PompeWidget;
private:
	int num;
	nb type;
	etat_t etat;
    Moteur* mot_linked; //Le moteur qu'elle alimente
	Reservoir* res_linked; //Le reservoir auquel elle appartient 

public:
 
	//Constructeur
    Pompe(int num,Reservoir &r, Moteur *, nb type);
	~Pompe();
	
	//Getters
	int GetNum(){return num;};
	nb GetType(){return type;};
	etat_t GetEtat(){return etat;};
	Moteur* GetMoteur(){return mot_linked;};
	Reservoir* GetReservoir(){return res_linked;};
	
	//Setters
	void SetType(const nb nb);
    bool SetEtat(const etat_t etat);
    void SetMoteur(Moteur * m);
    void SetReservoir(Reservoir * res);

	//Other methods
	void switchPanne();
	bool switchOnOff();
	void printInfos();
};


#endif
