#ifndef H_VALVERES
#define H_VALVERES

#include "Valve.h"


class Reservoir;

class ValveRes : public Valve{
private:
	std::vector<Reservoir*> reservoirs; //taille 2
public:
    ValveRes(std::string _nom, std::string _nom2,
             of _etat, std::vector<Reservoir*> r):
            Valve(_etat, _nom, _nom2)
            {reservoirs =r;};
	~ValveRes(){reservoirs.resize(0);};
    void printInfos(){
        Valve::printInfos();
        std::cout << reservoirs[0]->GetNum() << "/" << reservoirs[1]->GetNum() << std::endl;
    }
    bool setEtat(const of);

};



#endif

