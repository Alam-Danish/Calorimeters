#include "emcalSD.hh"

// Constructor 
MyEmCalSD::MyEmCalSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
  collectionName.insert("EMcalorimeterColl"); // Inserting the name of the collection of hits
}

// Destructor
MyEmCalSD::~MyEmCalSD()
{}

// Function to initialise the hit collection of the current event
void MyEmCalSD::Initialize(G4HCofThisEvent* hce)
{
  fHitsCollection = new MyEmCalHitsCollection(SensitiveDetectorName,collectionName[0]);
  if (fHCID<0)                                                                // check if the hit collection ID is not assigned
  { fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); } // Assigning the hit collection ID using the G4SDManager
  
  hce->AddHitsCollection(fHCID,fHitsCollection); // Adding the hit collection to the current event
  
  // Fill calorimeter hits with zero energy deposition
  for (G4int i=0;i<80;i++)
  {
    MyEmCalHit *hit = new MyEmCalHit(i);
    fHitsCollection->insert(hit);
  }
}

// Function to process each hit in the current event
G4bool MyEmCalSD::ProcessHits(G4Step*step, G4TouchableHistory*)
{
  G4double edep = step->GetTotalEnergyDeposit();                        // Getting the total energy deposit in the current step if it is 0, means successful detection
  if (edep==0.) return true;
  
  G4TouchableHistory *touchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable()); // Retrieving the physical volume and copy number
  G4VPhysicalVolume *physical = touchable->GetVolume();
  G4int copyNo = physical->GetCopyNo();
  
  MyEmCalHit *hit = (*fHitsCollection)[copyNo]; // Retrieving the hit corresponding to the copy number
  // check if it is first touch
  if (!(hit->GetLogV()))
  {
    // fill volume information
    hit->SetLogV(physical->GetLogicalVolume());
    G4AffineTransform transform = touchable->GetHistory()->GetTopTransform();
    transform.Invert();
    hit->SetRot(transform.NetRotation());
    hit->SetPos(transform.NetTranslation());
  }
  // add energy deposition
  hit->AddEdep(edep);
  
  return true;
}

 
