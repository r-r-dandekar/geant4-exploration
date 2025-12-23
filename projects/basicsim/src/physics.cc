#include "physics.hh"

MyPhysicsList::MyPhysicsList() 
{
    // Which physics to use will depend on your application!
    // Don't just use this template as is without thinking!
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}