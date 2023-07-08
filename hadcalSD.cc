#include "hadcalSD.hh"

// Constructor
MyHadCalSD::MyHadCalSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
    collectionName.insert("HadCalorimeterColl"); // Inserting the name of the collection of hits
}

// Destructor
MyHadCalSD::~MyHadCalSD()
{}

// Function to initialise the hit collection of the current event
void MyHadCalSD::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new MyHadCalHitsCollection(SensitiveDetectorName,collectionName[0]);
    if (fHCID<0)                                                                   // check if the hit collection ID is not assigned
    { fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }    // Assigning the hit collection ID using the G4SDManager
    hce->AddHitsCollection(fHCID,fHitsCollection); // Adding the hit collection to the current event

    // Fill calorimeter hits with zero energy deposition
    for (G4int iColumn=0;iColumn<10;iColumn++)
        for (G4int iRow=0;iRow<2;iRow++)
        {
            MyHadCalHit* hit = new MyHadCalHit();
            fHitsCollection->insert(hit);
        }
}

// Function to process each hit in the current event
G4bool MyHadCalSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit(); // Getting the total energy deposit in the current step if it is 0, means successful detection
    if (edep==0.) return true;
    
    G4TouchableHistory* touchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());

    // Reteriving the column, row number for hit and copy number
    G4VPhysicalVolume* cellPhysical = touchable->GetVolume(2);
    G4int rowNo = cellPhysical->GetCopyNo(); 

    G4VPhysicalVolume* columnPhysical = touchable->GetVolume(3);
    G4int columnNo = columnPhysical->GetCopyNo();

    G4int hitID = 2*columnNo+rowNo;
    MyHadCalHit* hit = (*fHitsCollection)[hitID]; // Retrieving the hit corresponding to the copy number
    
    // check if it is first touch
    if (hit->GetColumnID()<0)
    {   
        // Fill column and row information
        hit->SetColumnID(columnNo);
        hit->SetRowID(rowNo);
        G4int depth = touchable->GetHistory()->GetDepth();
        G4AffineTransform transform = touchable->GetHistory()->GetTransform(depth-2);
        transform.Invert();
        hit->SetRot(transform.NetRotation());
        hit->SetPos(transform.NetTranslation());
    }
    // add energy deposition
    hit->AddEdep(edep);
    
    return true;
}