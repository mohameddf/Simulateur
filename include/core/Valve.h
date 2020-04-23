#ifndef H_VALVE
#define H_VALVE

#include <vector>
#include <string>
#include <iostream>
#include "Reservoir.h"
#include "Moteur.h"


enum of{
	FERME = 0,
	OUVERT,
};

class Valve{
    friend class VWidget;
    friend class Systeme;
protected: 
	of etat;
	std::string nom;
    std::string nom2;


public:
    Valve(of, std::string, std::string);
    virtual ~Valve();
	
	std::string GetNom(){return nom;};
	of GetEtat(){return etat;};
    virtual bool setEtat(const of);
	virtual void printInfos();

};

#endif
