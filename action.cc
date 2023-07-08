#include "action.hh"


MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{   
    // Generator, run action, and event action definition
    SetUserAction(new MyPrimaryGenerator);
    SetUserAction(new MyRunAction);
}