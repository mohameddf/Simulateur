#include <iostream>
#include <QApplication>
#include "../include/core/Systeme.h"
#include "../include/states/State.h"
#include "../include/states/StateManager.h"
#include "../include/states/Loginstate.h"
#include "../include/states/MenuState.h"

int main(int argc, char  *argv[]){
    srand((unsigned)time(0));
    QApplication app(argc, argv);
    StateManager sm;
  Loginstate* ls = new Loginstate();
    sm.PushState(ls);
    sm.GetCurrentState()->update();
    return app.exec();
}
