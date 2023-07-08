#include "runaction.hh"
#include "run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

// Constructor for RunAction class
MyRunAction::MyRunAction()
{ 
  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Set a name for the output file
  analysisManager->SetFileName("output.root");

  // Create ntuple
  analysisManager->CreateNtuple("Energy", "Energy");
  analysisManager->CreateNtupleDColumn("ECEnergy"); // column Id = 0
  analysisManager->CreateNtupleDColumn("HCEnergy"); // column Id = 1
  analysisManager->FinishNtuple();
}

MyRunAction::~MyRunAction()
{
  delete G4AnalysisManager::Instance();
}

void MyRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  // Get analysis manager and open an output file
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
}

// Collect the energy accumulated in the local Run
// And dump on screen the needed physics quantities
// for this particular run.
void MyRunAction::EndOfRunAction(const G4Run* run)
{
  const Run* myrun = dynamic_cast<const Run*>(run);
  if ( myrun )
  {
    G4int nEvents = myrun->GetNumberOfEvent();
    if ( nEvents < 1 )
    {
      G4ExceptionDescription msg;
      msg << "Run consists of 0 events";
      G4Exception("RunAction::EndOfRunAction()","Code001", JustWarning, msg);
    }
    G4double em_ene = myrun->GetEmEnergy();
    G4double had_ene = myrun->GetHadEnergy();
    G4double shower_shape = myrun->GetShowerShape();
    G4int safety = ( nEvents > 0 ? nEvents : 1);//To avoid divisions by zero
    G4cout<<"Run["<<myrun->GetRunID()<<"] With: "<<nEvents<<"Events\n"
      <<" <E_em>="<<G4BestUnit(em_ene/safety,"Energy")<<"\n"
      <<" <E_had>="<<G4BestUnit(had_ene/safety,"Energy")<<"\n"
      <<" <E>="<<G4BestUnit((em_ene+had_ene)/safety,"Energy")<<"\n"
      <<" <ShowerShape>="<<shower_shape/safety<<G4endl;
  } else {
    G4ExceptionDescription msg;
    msg << "Run is not of correct type, skipping analysis via RunAction";
    G4Exception("RunAction::EndOfRunAction()", "Code001", JustWarning, msg);
  }
  
  // Write and close output file
  // save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

// Implement this method,
// instead of creating a generic G4Run
// create a user-defined Run
G4Run* MyRunAction::GenerateRun()
{
  return new Run;
}
