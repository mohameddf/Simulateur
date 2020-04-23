#ifndef H_MENUSTATE
#define H_MENUSTATE

#include "State.h"
#include "../gui/MenuGui.h"

class State;
class MenuGui;

class MenuState: public State{
private:
    MenuGui* gui;
public:

    MenuState();
    ~MenuState();
    void init();
    void free();
    void update();
    void display();

     MenuGui* getGui() const {return gui;}
};
#endif
