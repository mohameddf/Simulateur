#include "../../include/states/MenuState.h"


MenuState::MenuState(){
    gui = new MenuGui(this);
    init();
}
MenuState::~MenuState(){
    free();
    delete gui;
}
void MenuState::init(){
    return;
}
void MenuState::free(){
    gui->hide();
}
void MenuState::display(){
    gui->show();
}
void MenuState::update(){
    display();
}
