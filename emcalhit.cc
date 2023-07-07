#include "emcalhit.hh"


G4ThreadLocal G4Allocator<MyEmCalHit>* MyEmCalHitAllocator=0;

// Default constructor initialize base class and member variables
MyEmCalHit::MyEmCalHit()
: G4VHit(), fCellID(-1), fEdep(0.), fPos(0), fPLogV(0)
{}

// Constructor with cell ID as argument initialize base class and member variables
MyEmCalHit::MyEmCalHit(G4int z)
:  G4VHit(), fCellID(z), fEdep(0.), fPos(0), fPLogV(0)
{}

// Destructor
MyEmCalHit::~MyEmCalHit()
{}

// Copy constructor initialize base class and copy member variables from right
MyEmCalHit::MyEmCalHit(const MyEmCalHit &right)
: G4VHit() {
  fCellID = right.fCellID;
  fEdep = right.fEdep;
  fPos = right.fPos;
  fRot = right.fRot;
  fPLogV = right.fPLogV;
}

// Assigning member variables from right to current hit
const MyEmCalHit& MyEmCalHit::operator=(const MyEmCalHit &right)
{
  fCellID = right.fCellID;
  fEdep = right.fEdep;
  fPos = right.fPos;
  fRot = right.fRot;
  fPLogV = right.fPLogV;
  return *this;
}

// Comparison operator to check if two hits are same. If it is same return 1 else 0
int MyEmCalHit::operator==(const MyEmCalHit &right) const
{
  return (fCellID==right.fCellID);
}

// This function draw the hit in the visulaisation if the energy deposit is greater than 0
void MyEmCalHit::Draw()
{
  G4VVisManager *pVVisManager = G4VVisManager::GetConcreteInstance();
  if (pVVisManager&&(fEdep>0.))
  {
  // Draw a calorimeter cell with a color corresponding to its energy deposit
  G4Transform3D trans(fRot.inverse(),fPos);
  G4VisAttributes attribs;
  const G4VisAttributes *pVA = fPLogV->GetVisAttributes();
  if (pVA) attribs = *pVA;

  // Set the different color for different energy deposit
  G4double rcol = fEdep/(0.7*GeV);
  if (rcol>1.) rcol = 1.;
  if (rcol<0.4) rcol = 0.4;
  G4Colour colour(rcol,0.,0.); 
  attribs.SetColour(colour);
  attribs.SetForceSolid(true);
  pVVisManager->Draw(*fPLogV,attribs,trans);
  }
}

// Function to define the attibutes for the hit if if the hit is new
const std::map<G4String,G4AttDef>* MyEmCalHit::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
  = G4AttDefStore::GetInstance("MyEmCalHit",isNew);

  if (isNew) {
    (*store)["HitType"] = G4AttDef("HitType","Hit Type","Physics","","G4String");
    
    (*store)["ID"] = G4AttDef("ID","ID","Physics","","G4int");
    
    (*store)["Energy"] = G4AttDef("Energy", "Energy Deposited", "Physics", "G4BestUnit", "G4double");
    
    (*store)["Pos"] = G4AttDef("Pos", "Position", "Physics","G4BestUnit", "G4ThreeVector");
    
    (*store)["LVol"] = G4AttDef("LVol","Logical Volume","Physics","","G4String");
  }
  return store;
}

// Function to set the values of the previously defined attributes
std::vector<G4AttValue>* MyEmCalHit::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;
  
  values->push_back(G4AttValue("HitType","MyEmCalHit",""));
  values->push_back(G4AttValue("ID",G4UIcommand::ConvertToString(fCellID),""));
  values->push_back(G4AttValue("Energy",G4BestUnit(fEdep,"Energy"),""));
  values->push_back(G4AttValue("Pos",G4BestUnit(fPos,"Length"),""));
  
  // If the hit is inside a logical volume, set the name of the logical volume otherwise set it blank
  if (fPLogV)
    values->push_back(G4AttValue("LVol",fPLogV->GetName(),"")); 
  else
    values->push_back(G4AttValue("LVol"," ",""));

  return values;
}

// Function to print the cell ID and energy deposit in MeV
void MyEmCalHit::Print()
{
  G4cout << "  Cell[" << fCellID << "] " << fEdep/MeV << " (MeV)" << G4endl;
}

 
