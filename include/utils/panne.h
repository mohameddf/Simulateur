#ifndef H_PANNE
#define H_PANNE

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "../core/Systeme.h"
#include "xmlparser.h"
class Systeme;

class panne{
    friend class MainGui;
    friend class xmlparser;
private:
        int id; //Numéro de panne
        int parent; //Dans le cas d'une pompe numéro de réservoir sinon numéro de piece
        int piece;//0 pour le réservoir 1 pour la pompe
        int idobjet; //Pompe ( 1,2) ou Réservoir (1,2,3)
        int note; //0 à l'initialisation
        int duree; //temps à laquelle est apparait
        int isdone; //Lors d'un reprise de partie est ce que la panne à déja été injectée


        int getNumberInRange(int max);

public:
	//Construit une panne aléatoire
    panne(int, int);
	//Construit une panne depuis le fichier de configuration
	panne(int _id, int _idp, int _p, int _ido,int _note, int _duree, int _passe);
	~panne();
	void affiche() const;
    void apply(Systeme * s);
};
#endif
