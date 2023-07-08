#include "hadcalhit.hh"
 

G4ThreadLocal G4Allocator<MyHadCalHit>* MyHadCalHitAllocator=0; 

// Default constructor initialize base class and member variables
MyHadCalHit::MyHadCalHit()
: G4VHit(), fColumnID(-1), fRowID(-1), fEdep(0.), fPos(0)
{} 

// Constructor with cell ID as argument initialize base class and member variables
MyHadCalHit::MyHadCalHit(G4int iCol,G4int iRow)
: G4VHit(), fColumnID(iCol), fRowID(iRow), fEdep(0.), fPos(0)
{}

// Destructor
MyHadCalHit::~MyHadCalHit()
{}
 
// Copy constructor initialize base class and copy member variables from right
MyHadCalHit::MyHadCalHit(const MyHadCalHit &right)
: G4VHit() {
    fColumnID = right.fColumnID;
    fRowID = right.fRowID;
    fEdep = right.fEdep;
    fPos = right.fPos;
    fRot = right.fRot;
}

// Assigning member variables from right to current hit
const MyHadCalHit& MyHadCalHit::operator=(const MyHadCalHit &right)
{
    fColumnID = right.fColumnID;
    fRowID = right.fRowID;
    fEdep = right.fEdep;
    fPos = right.fPos;
    fRot = right.fRot;
    return *this;
}

// Comparison operator to check if two hits are same. If it is same return 1 else 0
int MyHadCalHit::operator==(const MyHadCalHit &right) const
{
    return (fColumnID==right.fColumnID&&fRowID==right.fRowID);
}

// This function draw the hit in the visulaisation if the energy deposit is greater than 0
void MyHadCalHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
    if (pVVisManager&&(fEdep>0.))
    {
        // Draw a calorimeter cell with depth propotional to the energy deposition
        G4Transform3D trans(fRot.inverse(),fPos);
        G4VisAttributes attribs;
        G4Colour colour(1.,0.,0.);
        attribs.SetColour(colour);
        attribs.SetForceSolid(true);
        G4Box box("dummy",15.*cm,15.*cm,1.*m*fEdep/(0.1*GeV));
        pVVisManager->Draw(box,attribs,trans);
    }
}

// Function to define the attributes of the hit if it is not already defined
const std::map<G4String,G4AttDef>* MyHadCalHit::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("MyHadCalHit",isNew);

    if (isNew) {
        (*store)["HitType"] = G4AttDef("HitType","Hit Type","Physics","","G4String");
        
        (*store)["Column"] = G4AttDef("Column","Column ID","Physics","","G4int");
        
        (*store)["Row"] = G4AttDef("Row","Row ID","Physics","","G4int");
        
        (*store)["Energy"] = G4AttDef("Energy","Energy Deposited","Physics","G4BestUnit","G4double");
        
        (*store)["Pos"] = G4AttDef("Pos", "Position", "Physics","G4BestUnit","G4ThreeVector");
    }
    return store;
}

// Function to get the attribute values of the hit
std::vector<G4AttValue>* MyHadCalHit::CreateAttValues() const
{
    std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
    
    values->push_back(G4AttValue("HitType","MyHadCalHit",""));
    values->push_back(G4AttValue("Column",G4UIcommand::ConvertToString(fColumnID), ""));
    values->push_back(G4AttValue("Row",G4UIcommand::ConvertToString(fRowID),""));
    values->push_back(G4AttValue("Energy",G4BestUnit(fEdep,"Energy"),""));
    values->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
    
    return values;
} 

// Function to print the Row and Column ID of the hit and the energy deposited
void MyHadCalHit::Print()
{
    G4cout << "  Cell[" << fRowID << ", " << fColumnID << "] " << fEdep/MeV << " (MeV) " << fPos << G4endl;
}

 
