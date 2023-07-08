#include "run.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "hadcalhit.hh"
#include "emcalhit.hh"

Run::Run()
{}

Run::~Run()
{}

// This method is called at the beginning of each run
void Run::RecordEvent(const G4Event* evt)
{
    G4Run::RecordEvent(evt); // Call the base class method

    if ( ECHCID == -1 || HCHCID == -1) {
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        ECHCID = sdManager->GetCollectionID("EmCalorimeter/EMcalorimeterColl");
        HCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");
    }
    G4HCofThisEvent* hce = evt->GetHCofThisEvent();
  
    const MyEmCalHitsCollection* emHC = static_cast<const MyEmCalHitsCollection*>(hce->GetHC(ECHCID));
    const MyHadCalHitsCollection* hadHC = static_cast<const MyHadCalHitsCollection*>(hce->GetHC(HCHCID));

    G4double em = 0;
    G4double had = 0;
    for (size_t i=0;i<emHC->GetSize();i++)
    {
        MyEmCalHit* hit = (*emHC)[i];
        em += hit->GetEdep();
    }
    for (size_t i=0;i<hadHC->GetSize();i++)
    {
        MyHadCalHit* hit = (*hadHC)[i];
        had += hit->GetEdep();
    }
    had_ene += had;
    em_ene += em;
    if ( had+em > 0 )
        shower_shape += ( em/(had+em) );
}