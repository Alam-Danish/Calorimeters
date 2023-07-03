#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"

/// Action initialization class.

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization();
    virtual ~MyActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif