#include <iostream>
#include <cstddef>

#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

#include "construction.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    // Creating default Run Manager
    G4RunManager *runManager = new G4RunManager(); 

    // Set and Initialize user defined detector construction class for runManager
    runManager->SetUserInitialization(new MyDetectorConstruction());

    // Getting predefined Physics List from FTFP_BERT class
    G4VModularPhysicsList *physicsList = new FTFP_BERT();
    // Step limiter physics to limits the step size of traversing particles
    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    // Set and Initialize physics list
    runManager->SetUserInitialization(physicsList);

    // Set and Initialize user defined action initialization class for runManager
    runManager->SetUserInitialization(new MyActionInitialization());

    runManager->Initialize();

    // Graphical user interface (GUI) for visualization and interactive control
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // Visualisation manager 
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Pointer to manage user interface
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    // Commands to user interface for interactive mode
    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/scene/add/hits");
    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    
    

    ui->SessionStart();

    return 0;
}