/* Código copiado del ejemplo novice/N03->SteppingAction */

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4ParticleTypes.hh"

SteppingAction::SteppingAction()                                         
{
  detector = (DetectorConstruction*)
             G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  eventAction = (EventAction*)
                G4RunManager::GetRunManager()->GetUserEventAction();               
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
  if(aStep->GetTrack()->GetDefinition()->GetParticleType() == "gamma")
    {
      if (volume == detector->GetTrigger())	eventAction->AddNOTP();
      if (volume == detector->GetSensor())	eventAction->AddNOSP();
    }      
}
