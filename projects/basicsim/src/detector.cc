# include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}
MySensitiveDetector::~MySensitiveDetector() {}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {

    G4Track *track = aStep->GetTrack();

    // To make sure only the photons entering from the front surface are detected
    // We kill any photons that are detected so that they can't be detected by other detectors
    track->SetTrackStatus(fStopAndKill);
    
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();       // Point where photon enters detector    
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();     // Point where photon leaves detector

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    // This prints the exact position of the photon, which would not be known in a real experiment!
    // G4cout << "Photon position: " << posPhoton << G4endl;


    // Get the copy-number of the detector physical volume, which we defined in the nested for loop
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();

    // G4cout << "Copy number: " << copyNo << G4endl;

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << "Detector position: " << posDetector << G4endl;
}