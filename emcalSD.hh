#ifndef EM_CALORIMETER_SD_HH
#define EM_CALORIMETER_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

#include "emcalhit.hh"

// Class to define the sensitive detector for the EM calorimeter

class MyEmCalSD : public G4VSensitiveDetector
{    
public:
    MyEmCalSD(G4String name); // Constructor
    virtual ~MyEmCalSD(); // Destructor
    
    virtual void Initialize(G4HCofThisEvent*); // Function to initialise the hit collection of the current event
    virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*); // Function to process each hit in the current event
    
private:
    MyEmCalHitsCollection* fHitsCollection; // Pointer to the hit collection
    G4int fHCID; // Hit collection ID
};

#endif
