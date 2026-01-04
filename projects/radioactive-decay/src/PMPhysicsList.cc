#include "PMPhysicsList.hh"

PMPhysicsList::PMPhysicsList()
{
    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Radioactive Decay Physics
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // Decay Physics
    RegisterPhysics(new G4DecayPhysics());
}
PMPhysicsList::~PMPhysicsList() {} 