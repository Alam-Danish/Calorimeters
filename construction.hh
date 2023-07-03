#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


// Including all the libraries here which also need to be included in the .cc file

#include "G4VUserDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"

#include "parameter.hh"

// Detector Construction class declaration
class MyDetectorConstruction : public G4VUserDetectorConstruction
{

public:
    MyDetectorConstruction(); // Constructor
    virtual ~MyDetectorConstruction(); // Destructor

    virtual G4VPhysicalVolume* Construct(); // Construct method

private:
    G4LogicalVolume *emCalCellLogical;
    G4LogicalVolume *hadCalScintLogical;
};
#endif