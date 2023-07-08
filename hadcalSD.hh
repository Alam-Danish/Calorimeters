#ifndef HAD_CALORIMETER_SD_HH
#define HAD_CALORIMETER_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"

#include "hadcalhit.hh"

// Class to define the sensitive detector for the hadronic calorimeter

class MyHadCalSD : public G4VSensitiveDetector
{    
public:
    MyHadCalSD(G4String name); // Constructor
    virtual ~MyHadCalSD(); // Destructor
    
    virtual void Initialize(G4HCofThisEvent*); // Function to initialise the hit collection of the current event
    virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*); // Function to process each hit in the current event
    
private:
    MyHadCalHitsCollection* fHitsCollection; // Pointer to the hit collection
    G4int fHCID; // Hit collection ID
};

#endif
