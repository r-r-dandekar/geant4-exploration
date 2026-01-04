#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "PMPhysicsList.hh"
#include "PMDetectorConstruction.hh"
#include "PMActionInitialization.hh"

int main(int argc, char** argv) 
{
    // G4UIExecutive *ui = new G4UIExecutive(argc, argv);   // Uncomment this for the GUI version?
    G4UIExecutive *ui;

    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif



    // Physics List
    runManager->SetUserInitialization(new PMPhysicsList());

    // Detector Construction
    runManager->SetUserInitialization(new PMDetectorConstruction());

    // Action Initialization
    runManager->SetUserInitialization(new PMActionInitialization());


    if (argc==1)    // If exactly one arg, which is the program name, call this for making UI
    {               // Otherwise, it should run in batch modee
        ui = new G4UIExecutive(argc, argv);
    }


    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    if (ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");

        ui->SessionStart();
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
        

    return 0;
}