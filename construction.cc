#include "construction.hh"

// Constructor
MyDetectorConstruction::MyDetectorConstruction()
{
}

// Destructor
MyDetectorConstruction::~MyDetectorConstruction()
{
}

// Construct method
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // World volume material
    G4NistManager *nist = G4NistManager::Instance(); // NIST material manager
    G4Material *air = nist->FindOrBuildMaterial("G4_AIR"); // Air
    

    // World volume
    G4VSolid *worldSolid = new G4Box("worldSolid", 10.*m, 3.*m, 10.*m); // World volume with name ans its dimensions
    // Logical volume of the world volume with Mother volume, material, name
    G4LogicalVolume *worldLogical = new G4LogicalVolume(worldSolid, air, "worldLogical");
    // Physical volume of the world volume with logical volume, rotation, position, logical volume, mother volume name, boolean operation, copy number, check overlapes
    G4VPhysicalVolume *worldPhysical = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), worldLogical, "worldPhysical", 0, false, 0, true);

    // EM Calorimeter volume material
    G4Material *CsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE"); // Cesium Iodide

    // EM Calorimeter volume
    G4VSolid *emCalSolid = new G4Box("emCalSolid", 1.5*m, 30.*cm, 15.*cm);
    G4LogicalVolume *emCalLogical = new G4LogicalVolume(emCalSolid, CsI, "emCalLogical");
    G4VPhysicalVolume *emCalPhysical = new G4PVPlacement(0, G4ThreeVector(0., 0., 2.*m), emCalLogical, "emCalPhysical", worldLogical, false, 0, true);

    return worldPhysical;
}
