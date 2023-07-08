#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH


#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"

/// Event action

class MyEventAction : public G4UserEventAction
{
public:
    MyEventAction();
    ~MyEventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
private:
    G4int fECHCID = -1;
    G4int fHCHCID = -1;
};

#endif
