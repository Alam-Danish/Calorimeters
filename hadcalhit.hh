// Similar to ElecroMagnetic calorimeter hit,
// we define a class to store the information of each hit in the hadronic calorimeter.

#ifndef HAD_CALORIMETER_HIT_HH
#define HAD_CALORIMETER_HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VVisManager.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


// Class to store the information of each hit in the calorimeter
class MyHadCalHit : public G4VHit
{
public:
    MyHadCalHit(); // Default constructor
    MyHadCalHit(G4int iCol,G4int iRow); // Constructor with column and row ID as arguments
    MyHadCalHit(const MyHadCalHit &right); // Copy constructor
    virtual ~MyHadCalHit(); // Destructor

    const MyHadCalHit& operator=(const MyHadCalHit &right); // Assignment operator
    int operator==(const MyHadCalHit &right) const; // Comparison operator
    
    inline void *operator new(size_t); // new operator for memory allocation
    inline void operator delete(void *aHit);  // delete operator for memory deallocation
    
    virtual void Draw(); // Draw the hit in the visualisation
    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const; // Get the list of attributes of this hit
    virtual std::vector<G4AttValue>* CreateAttValues() const; // Get the list of values of this hit
    virtual void Print(); // Print the information of this hit
    
    void SetColumnID(G4int z) { fColumnID = z; } // Set the column ID
    G4int GetColumnID() const { return fColumnID; } // Reitrive the column ID

    void SetRowID(G4int z) { fRowID = z; } // Set the row ID
    G4int GetRowID() const { return fRowID; } // Retrieve the row ID

    void SetEdep(G4double de) { fEdep = de; } // Set the energy deposit
    void AddEdep(G4double de) { fEdep += de; } // Add the energy deposit
    G4double GetEdep() const { return fEdep; } // Get the total energy deposit

    void SetPos(G4ThreeVector xyz) { fPos = xyz; } // Set the position of the hit
    G4ThreeVector GetPos() const { return fPos; } // Retrieve the position of the hit

    void SetRot(G4RotationMatrix rmat) { fRot = rmat; } // Set the rotation matrix of the hit
    G4RotationMatrix GetRot() const { return fRot; } // Retrieve the rotation matrix of the hit
    
private:
    // Variables to store the information of the hit
    G4int fColumnID;
    G4int fRowID;
    G4double fEdep;
    G4ThreeVector fPos;
    G4RotationMatrix fRot;
};

typedef G4THitsCollection<MyHadCalHit> MyHadCalHitsCollection; // Define a collection of hits

extern G4ThreadLocal G4Allocator<MyHadCalHit>* MyHadCalHitAllocator; // Define a memory allocator for hits

// Previouly defined operators for memory allocation and deallocation
inline void* MyHadCalHit::operator new(size_t)
{
    if (!MyHadCalHitAllocator)
        MyHadCalHitAllocator = new G4Allocator<MyHadCalHit>;
    return (void*)MyHadCalHitAllocator->MallocSingle();
}

inline void MyHadCalHit::operator delete(void* aHit)
{
    MyHadCalHitAllocator->FreeSingle((MyHadCalHit*) aHit);
}

#endif
