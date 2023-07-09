#include "parameter.hh"

// EM Calorimeter cell parameterisation
EMCellParameterisation::EMCellParameterisation()
{
    // Define the cell positions
    for (G4int copyNo=0;copyNo<80;copyNo++)
    {
        G4int column = copyNo / 4;
        G4int row = copyNo % 4;
        fXCell[copyNo] = (column-9)*15.*cm - 7.5*cm;
        fYCell[copyNo] = (row-1)*15*cm - 7.5*cm;
    }
}


EMCellParameterisation::~EMCellParameterisation()
{}

// Geometry transformation to place cells
void EMCellParameterisation::ComputeTransformation
(const G4int copyNo,G4VPhysicalVolume *physVol) const
{
    physVol->SetTranslation(G4ThreeVector(fXCell[copyNo],fYCell[copyNo],0.));
}