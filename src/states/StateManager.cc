#include "../../include/states/State.h"
#include "../../include/states/StateManager.h"
#include "../../include/states/MainGState.h"
StateManager::StateManager(){

}

StateManager::~StateManager(){
}


void StateManager::PushState(State* state )
{   state->SetStateManager((*this)); 
    SStack.push(state);
}
 
void StateManager::SetState(State* state )
{
    state->SetStateManager((*this));
    PopState();
    PushState(state);
}
 
void StateManager::PopState()
{
    if ( !SStack.empty() )
    {
        //SStack.top()->free();
        SStack.pop();
    }
} 
