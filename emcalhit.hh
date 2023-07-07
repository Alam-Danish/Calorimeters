#ifndef EM_CALORIMETER_HIT_HH
#define EM_CALORIMETER_HIT_HH 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
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
class MyEmCalHit : public G4VHit
{
public:
    MyEmCalHit(); // Default constructor 
    MyEmCalHit(G4int z); // Constructor with cell ID as argument 
    MyEmCalHit(const MyEmCalHit &right); // Copy constructor 
    virtual ~MyEmCalHit(); // Destructor

    const MyEmCalHit& operator=(const MyEmCalHit &right); // Assignment operator
    int operator==(const MyEmCalHit &right) const; // Comparison operator 
    
    inline void *operator new(size_t); // Overload new operator to allocate memory for individual hits
    inline void operator delete(void *aHit); // Overload delete operator to deallocate memory for individual hits
    
    virtual void Draw(); // Draw the hit in the visualisation
    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const; // Get the list of attributes of hit
    virtual std::vector<G4AttValue>* CreateAttValues() const; //  Set the attributes values of hit
    virtual void Print(); // Print the hit details
    
    void SetCellID(G4int z) { fCellID = z; } // Set the cell ID of hit
    G4int GetCellID() const { return fCellID; } // Retrieve the cell ID of hit

    void SetEdep(G4double de) { fEdep = de; } // Set the energy deposit of hit
    void AddEdep(G4double de) { fEdep += de; } // Add energy deposit to current hit
    G4double GetEdep() const { return fEdep; } // Get the total energy deposit of hit

    void SetPos(G4ThreeVector xyz) { fPos = xyz; } // Set the position of hit
    G4ThreeVector GetPos() const { return fPos; } // Reitrieve the position of hit

    void SetRot(G4RotationMatrix rmat) { fRot = rmat; } // Set the rotation matrix of hit
    G4RotationMatrix GetRot() const { return fRot; } // Retrieve the rotation matrix of hit

    void SetLogV(G4LogicalVolume *val) { fPLogV = val; } // Set the logical volume of hit
    const G4LogicalVolume *GetLogV() const { return fPLogV; } // Retrieve the logical volume of hit
    
private:
    // Variables to store the information of each hit
    G4int fCellID;
    G4double fEdep;
    G4ThreeVector fPos;
    G4RotationMatrix fRot;
    const G4LogicalVolume* fPLogV;
};

typedef G4THitsCollection<MyEmCalHit> MyEmCalHitsCollection; // Define a collection of hits

extern G4ThreadLocal G4Allocator<MyEmCalHit>* MyEmCalHitAllocator; // Define a thread local allocator to allocate memory for hits


// Prevoiusly defined inline functions to allocate and deallocate memory for hits
inline void* MyEmCalHit::operator new(size_t)
{
    if (!MyEmCalHitAllocator)
        MyEmCalHitAllocator = new G4Allocator<MyEmCalHit>;
    return (void*)MyEmCalHitAllocator->MallocSingle();
}

inline void MyEmCalHit::operator delete(void* aHit)
{
    MyEmCalHitAllocator->FreeSingle((MyEmCalHit*) aHit);
}

#endif
