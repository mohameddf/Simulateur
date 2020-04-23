#ifndef H_STATE
#define H_STATE

#include "StateManager.h"


class StateManager;
class State
{
private:
    StateManager* manager;

public:
	
      State(){};
      virtual ~State(){};

        void SetStateManager(StateManager& sm){ manager = &sm;}
        StateManager* GetManager() const{return manager;}

          virtual void init()=0; //Initialise l'état lors de son ajout à la pile
          virtual void free()=0; //Libére l'état lors de son retrait de la pile

          virtual void update()=0; //Met à jour l'état
          virtual void display()=0; //Appelle la classe Gui correspondante


};

#endif
