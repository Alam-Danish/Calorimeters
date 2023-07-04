#ifndef EM_CALORIMETER_HIT_HH
#define EM_CALORIMETER_HIT_HH 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"


class MyEmCalHit : public G4VHit
{
public:
    MyEmCalHit();
    MyEmCalHit(G4int z);
    MyEmCalHit(const MyEmCalHit &right);
    virtual ~MyEmCalHit();

    const MyEmCalHit& operator=(const MyEmCalHit &right);
    int operator==(const MyEmCalHit &right) const;
    
    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
    
    virtual void Draw();
    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;
    virtual void Print();
    
    void SetCellID(G4int z) { fCellID = z; }
    G4int GetCellID() const { return fCellID; }

    void SetEdep(G4double de) { fEdep = de; }
    void AddEdep(G4double de) { fEdep += de; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    G4ThreeVector GetPos() const { return fPos; }

    void SetRot(G4RotationMatrix rmat) { fRot = rmat; }
    G4RotationMatrix GetRot() const { return fRot; }

    void SetLogV(G4LogicalVolume *val) { fPLogV = val; }
    const G4LogicalVolume *GetLogV() const { return fPLogV; }
    
private:
    G4int fCellID;
    G4double fEdep;
    G4ThreeVector fPos;
    G4RotationMatrix fRot;
    const G4LogicalVolume* fPLogV;
};

typedef G4THitsCollection<MyEmCalHit> MyEmCalHitsCollection;

extern G4ThreadLocal G4Allocator<MyEmCalHit>* MyEmCalHitAllocator;

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
