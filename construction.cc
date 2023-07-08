#include "construction.hh"

// Constructor
MyDetectorConstruction::MyDetectorConstruction()
{
}

// Destructor
MyDetectorConstruction::~MyDetectorConstruction()
{
  for (G4int i=0; i<G4int(VisAttributes.size()); ++i) 
  {
    delete VisAttributes[i];
  }  
}

// Construct method
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // World volume material
    G4NistManager *nist = G4NistManager::Instance(); // NIST material manager
    G4Material *air = nist->FindOrBuildMaterial("G4_AIR"); // Air
    

    // World volume
    G4VSolid *worldSolid = new G4Box("worldSolid", 2.*m, 1.*m, 6.*m); // World volume with name ans its dimensions
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

    // Here I divided the EM calorimeter into 80 cells in 20 columns and 4 rows
    // EM calorimeter Cell
    G4VSolid *emCalCellSolid = new G4Box("emCalCellSolid", 7.5*cm, 7.5*cm, 15.*cm);
    emCalCellLogical = new G4LogicalVolume(emCalCellSolid, CsI, "emCalCellLogical");
    // Parameterisation of the EM calorimeter cell which is defined in parameter.hh
    G4VPVParameterisation *cellParam = new EMCellParameterisation();
    // Parameterised volume (Parameterised volume name, logical cell volume, logical mother volume, copy number, number of cells, parameterisation)
    new G4PVParameterised("emCalCellPhysical", emCalCellLogical, emCalLogical, kUndefined, 80, cellParam);


    // Hadron Calorimeter volume material
    G4Material *Pb = nist->FindOrBuildMaterial("G4_Pb"); // Lead
    G4Material *scintillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); // Scintillator material

    // Hadron Calorimeter volume
    G4VSolid *hadCalSolid = new G4Box("hadCalSolid", 1.5*m, 30.*cm, 50.*cm);
    G4LogicalVolume *hadCalLogical = new G4LogicalVolume(hadCalSolid, Pb, "hadCalLogical");
    G4VPhysicalVolume *hadCalPhysical = new G4PVPlacement(0, G4ThreeVector(0., 0., 3.*m), hadCalLogical, "hadCalPhysical", worldLogical, false, 0, true);

    // Here I divided the hadron calorimeter into 10 columns, 2 rows and divided in 20 layers

    // hadron calorimeter column
    G4VSolid *hadCalColumnSolid = new G4Box("hadCalColumnBox", 15.*cm, 30.*cm, 50.*cm);
    G4LogicalVolume* hadCalColumnLogical = new G4LogicalVolume(hadCalColumnSolid, Pb, "hadCalColumnLogical");
    // Replication of the hadron calorimeter column (name, logical volume, mother volume, axis, number of copies, width of the column)
    new G4PVReplica("hadCalColumnPhysical", hadCalColumnLogical, hadCalLogical, kXAxis, 10, 30.*cm);
    
    // hadron calorimeter cell
    G4VSolid *hadCalCellSolid = new G4Box("hadCalCellBox", 15.*cm, 15.*cm, 50.*cm);
    G4LogicalVolume *hadCalCellLogical = new G4LogicalVolume(hadCalCellSolid, Pb, "hadCalCellLogical");
    new G4PVReplica("hadCalCellPhysical", hadCalCellLogical, hadCalColumnLogical, kYAxis, 2, 30.*cm);
    
    // hadron calorimeter layers
    G4VSolid *hadCalLayerSolid = new G4Box("hadCalLayerBox", 15.*cm, 15.*cm, 2.5*cm);
    G4LogicalVolume *hadCalLayerLogical = new G4LogicalVolume(hadCalLayerSolid, Pb, "hadCalLayerLogical");
    new G4PVReplica("hadCalLayerPhysical",hadCalLayerLogical, hadCalCellLogical,kZAxis,20,5.*cm);
    

    // hadron calorimeter scintillator plates
    // These are placed in the middle of the layers
    G4VSolid *hadCalScintSolid = new G4Box("hadCalScintBox", 15.*cm, 15.*cm, 0.5*cm);
    hadCalScintLogical = new G4LogicalVolume(hadCalScintSolid, scintillator, "hadCalScintLogical");
    new G4PVPlacement(0, G4ThreeVector(0., 0., 2.*cm), hadCalScintLogical, "hadCalScintPhysical", hadCalLayerLogical, false, 0, true);

    
    // visualization attributes of the volumes
    // world volume
    G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0)); // White
    visAttributes->SetVisibility(false); // Set the visibility of the world volume to false
    worldLogical->SetVisAttributes(visAttributes); // Set the visualization attributes of the world volume
    VisAttributes.push_back(visAttributes); // Add the visualization attributes to the vector
    
    // EM calorimeter
    visAttributes = new G4VisAttributes(G4Colour(0.8888,0.8888,0.0)); // Yellow
    visAttributes->SetVisibility(true);
    emCalLogical->SetVisAttributes(visAttributes);
    VisAttributes.push_back(visAttributes);
    
    // EM calorimeter cell which is visible
    visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0)); // Yellow
    visAttributes->SetVisibility(true); // Set the visibility false, if you want to see the EM calorimeter cell, set it to true
    emCalCellLogical->SetVisAttributes(visAttributes);
    VisAttributes.push_back(visAttributes);
    
    // Hadron calorimeter which is visible
    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9)); // Blue
    hadCalLogical->SetVisAttributes(visAttributes);
    VisAttributes.push_back(visAttributes);
    
    // Hadron calorimeter column, cell, layer and scintillator plate
    visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));
    visAttributes->SetVisibility(false); // Set the visibility false, if you want to see the hadron calorimeter column, cell, layer and scintillator plate, set it to true
    hadCalColumnLogical->SetVisAttributes(visAttributes);
    hadCalCellLogical->SetVisAttributes(visAttributes);
    hadCalLayerLogical->SetVisAttributes(visAttributes);
    hadCalScintLogical->SetVisAttributes(visAttributes);
    VisAttributes.push_back(visAttributes);

    return worldPhysical;
}


// Sesitive detector construction
void MyDetectorConstruction::ConstructSDandField()
{
  G4SDManager *SDman = G4SDManager::GetSDMpointer(); // Get the pointer to the sensitive detector manager
  G4String SDname;
  
  // EM calorimeter sensitive detector
  G4VSensitiveDetector *emCalorimeter = new MyEmCalSD(SDname="/EmCalorimeter");
  SDman->AddNewDetector(emCalorimeter);
  emCalCellLogical->SetSensitiveDetector(emCalorimeter);

  // Hadron calorimeter sensitive detector
  G4VSensitiveDetector* hadCalorimeter = new MyHadCalSD(SDname="/HadCalorimeter");
  SDman->AddNewDetector(hadCalorimeter);
  hadCalScintLogical->SetSensitiveDetector(hadCalorimeter);
}