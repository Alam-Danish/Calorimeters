#ifndef PARAMETER_HH
#define PARAMETER_HH

#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"


// EM Calorimeter cell parameterisation

class EMCellParameterisation : public G4VPVParameterisation
{
public:
    EMCellParameterisation();
    virtual ~EMCellParameterisation();
    
    virtual void ComputeTransformation(const G4int copyNo,G4VPhysicalVolume *physVol) const;
    
private:
    G4double fXCell[80];
    G4double fYCell[80];
};

#endif