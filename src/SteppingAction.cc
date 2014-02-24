/* Código copiado del ejemplo novice/N03->SteppingAction */

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4ParticleTypes.hh"
#include "G4String.hh"

#include "G4VProcess.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"

SteppingAction::SteppingAction()                                         
{
  detector = (DetectorConstruction*) G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  eventAction = (EventAction*) G4RunManager::GetRunManager()->GetUserEventAction();               
 }

 SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // get volume of the current step
  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
    
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();
  if(aStep->GetTrack()->GetDefinition()->GetParticleType() == "gamma" &&
     //(
     // (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "phot") ||
     // (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "compt")
     // )
    edep)
    {
      /* DEBUG =======================================================*/
      G4cout << "DEBUG: Hello World!\n";
      G4String out = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
      if (out != NULL) G4cout << out << G4endl;
      G4cout << "Energy deposited:\t" << edep << G4endl;
      /*==============================================================*/

      if (volume == detector->GetTrigger())	eventAction->AddNOTP();
      if (volume == detector->GetSensor())	eventAction->AddNOSP();
    }      
}
