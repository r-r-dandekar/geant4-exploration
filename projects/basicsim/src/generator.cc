#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}
MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Making the particle gun shoot particles

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "proton"; // What was the point of this? Is this needed? Should it be used in the next line?
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");

    G4ThreeVector pos(0., 0., 0.);
    G4ThreeVector mom(0., 0., 1.);  // Typically we create particles moving in z direction

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);    // This is just the direction
    fParticleGun->SetParticleMomentum(100.*GeV);    // And this is the momentum
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
