#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"

// Class to define the generic run
class Run : public G4Run 
{
public:
  Run();
  ~Run();

  virtual void RecordEvent(const G4Event*); // Record event information

  G4double GetEmEnergy() const { return em_ene; } // energy deposited in the EM calorimeter
  G4double GetHadEnergy() const { return had_ene; } // energy deposited in the hadronic calorimeter
  G4double GetShowerShape() const { return shower_shape; } // shower shape
  
private:
  G4double em_ene = 0;
  G4double had_ene = 0;
  G4double shower_shape = 0;
  G4int ECHCID = -1;
  G4int HCHCID = -1;
};

#endif
