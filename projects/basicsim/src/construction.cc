#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();


    // Fused Silica
    G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);


    // Water
    G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);


    // Carbon
    G4Element *C = nist->FindOrBuildElement("C");


    // Aerogel
    G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    Aerogel->AddMaterial(SiO2, 62.5*perCent);
    Aerogel->AddMaterial(H2O, 37.4*perCent);
    Aerogel->AddElement(C, 0.1*perCent);

    // Cherenkov radiation is generated when a particle travels faster than the speed of light in that medium
    // In our simulation, the protons are moving very fast, faster than the speed of light in aerogel
    // Cherenkov angle is calculated from the refrective index of the material
    // so we need to define the R. I. associated with a photon momentum

    // Momentum of photon?
    // Watch for explanation: https://www.youtube.com/watch?v=-H-QEIphAsA&t=840s 
    // Note: The tutorial had blue light first and red light second, but that gives an error!
    //       Find out why, and what is correct
    G4double energy[2] = {
        1.239841939*eV/0.9,     // red light
        1.239841939*eV/0.2      // blue light
    };      

    // R. I. of Aerogel
    // For simplicity ignore effects of dispersion and only one R. I.
    G4double rindexAerogel[2] = {1.1, 1.1};

    // Add the RINDEX property to Aerogel
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    Aerogel->SetMaterialPropertiesTable(mptAerogel);

    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    // R. I. of air i.e. of worldMat
    G4double rindexmptWorld[2] = {1.0, 1.0};
    // Add the RINDEX property to Air
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexmptWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    // Solid Volume
    // The 0.5s are half-size dimensions so its 1m x 1m x 1m box
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);     

    // Logical Volume
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Physical Volume
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);



    // The radiator
    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);


    // Create a 100x100 grid of photosensors
    // The solid volume and logical volume objects will be common to all the sensors
    // The physical volume objects will be distinct for each sensor
    G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

    // The logical volume has to be referred to from outside construction.cc, so we define it in construction.hh
    // The only purpose of the detector volume is to detect photons
    // We don't want to simulate an actual physical detector here in this example
    // So we set the material to worldMat, i.e. air
    logicDetector = new G4LogicalVolume (solidDetector, worldMat, "logicDetector");

    // Create the grid of physical volumes
    for (G4int i=0; i < 100; i++) {
        for (G4int j=0; j < 100; j++) {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(
                0, 
                G4ThreeVector( -0.5*m+(i+0.5)*m/100, 
                                -0.5*m+(j+0.5)*m/100,
                                0.49*m),
                logicDetector,
                "physDetector",
                logicWorld,
                false,
                i*100+j,
                true);
        }
    }


    // Return the highest mother volume
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
}