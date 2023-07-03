#include <iostream>
#include <cstddef>

#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"


int main(int argc, char** argv)
{
    // Creating default Run Manager
    G4RunManager *runManager = new G4RunManager(); 

    // Graphical user interface (GUI) for visualization and interactive control
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // Visualisation
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    // Pointer to manage user interface
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    

    ui->SessionStart();

    return 0;
}