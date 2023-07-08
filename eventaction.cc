#include "eventaction.hh"
#include "emcalhit.hh"
#include "hadcalhit.hh"
#include "G4AnalysisManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


MyEventAction::MyEventAction()
{
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
  if (fECHCID==-1) {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    fECHCID = sdManager->GetCollectionID("EmCalorimeter/EMcalorimeterColl");
    fHCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");
  }
}     


void MyEventAction::EndOfEventAction(const G4Event* event)
{
  G4HCofThisEvent* hce = event->GetHCofThisEvent();

  // Get hits collections 
  MyEmCalHitsCollection* ecHC = static_cast<MyEmCalHitsCollection*>(hce->GetHC(fECHCID));
  MyHadCalHitsCollection* hcHC = static_cast<MyHadCalHitsCollection*>(hce->GetHC(fHCHCID));
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill ntuple
  // ECEnergy
  G4int totalEmHit = 0;
  G4double totalEmE = 0.;
  for (G4int i=0;i<80;i++)
  {
      MyEmCalHit* hit = (*ecHC)[i];
      G4double eDep = hit->GetEdep();
      if (eDep>0.)
      {
          totalEmHit++;
          totalEmE += eDep;
      }
  }
  analysisManager->FillNtupleDColumn(0, totalEmE);

  // HCEnergy
  G4int totalHadHit = 0;
  G4double totalHadE = 0.;
  for (G4int i=0;i<20;i++)
  {
      MyHadCalHit* hit = (*hcHC)[i];
      G4double eDep = hit->GetEdep();
      if (eDep>0.)
      {
          totalHadHit++;
          totalHadE += eDep;
      }
  }
  analysisManager->FillNtupleDColumn(1, totalHadE);

    
  analysisManager->AddNtupleRow();
  
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
  
  G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
  G4cout << G4endl<< ">>> Event " << event->GetEventID() << " >>> Simulation: "<< primary->GetG4code()->GetParticleName()<< " " << primary->GetMomentum() << G4endl;
  

  // EM calorimeter
  G4cout << "EM Calorimeter has " << totalEmHit << " hits. Total Edep is " << totalEmE/MeV << " (MeV)" << G4endl;

  // Had calorimeter
  G4cout << "Hadron Calorimeter has " << totalHadHit << " hits. Total Edep is "<< totalHadE/MeV << " (MeV)" << G4endl;
}