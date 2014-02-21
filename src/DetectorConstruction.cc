#include "DetectorConstruction.hh"

#include "globals.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

//#include "G4MaterialPropertyVector.hh"

//#include "SensitiveDetector.hh"




//#include "G4PVParameterised.hh"
//#include "G4VPVParameterisation.hh"

#include "G4VPhysicalVolume.hh"
//#include "DetectorParameterisation.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
//#include "G4SDParticleFilter.hh"
//#include "G4SDManager.hh"

//#include "G4Polycone.hh"
//#include "G4OpticalSurface.hh"
//#include "G4LogicalBorderSurface.hh"


DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	/*** Material Definitions ***/
	G4NistManager* nist = G4NistManager::Instance();	// Manager that use G4's elements database

	G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* Pb = nist->FindOrBuildMaterial("G4_Pb");
	
	G4Element* Br = nist->FindOrBuildElement("Br");
	G4Element* La = nist->FindOrBuildElement("La");
	G4Element* Ce = nist->FindOrBuildElement("Ce");
	
	G4double brillanceDensity = 5.08*g/cm3;
	G4Material* Brillance = new G4Material("Brillance", brillanceDensity, 3);
	Brillance->AddElement(Br, 3);
	Brillance->AddElement(La, 1);
	Brillance->AddElement(Ce, 1);

	/*
	G4Element* C  = nist->FindOrBuildElement("C");
  	G4Element* Si = nist->FindOrBuildElement("Si");
  	G4Element* Cr = nist->FindOrBuildElement("Cr");
  	G4Element* Mn = nist->FindOrBuildElement("Mn");
  	G4Element* Fe = nist->FindOrBuildElement("Fe");
  	G4Element* Ni = nist->FindOrBuildElement("Ni");

  	G4double density;
  	G4int ncomponents;
  	G4double fractionmass;

  	G4Material* StainlessSteel = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
  	StainlessSteel->AddElement(C, fractionmass=0.001);
  	StainlessSteel->AddElement(Si, fractionmass=0.007);
  	StainlessSteel->AddElement(Cr, fractionmass=0.18);
  	StainlessSteel->AddElement(Mn, fractionmass=0.01);
  	StainlessSteel->AddElement(Fe, fractionmass=0.712);
  	StainlessSteel->AddElement(Ni, fractionmass=0.09);
  	*/
	/*** Material Definitions ***/

	/*** Trigger Construction ***/
	G4LogicalVolume* volume[6];	//Colimator, trigger colimator, source, material, sensor.
	G4Tubs* solidVol[6];
	G4ThreeVector positions[6];

	G4double innerRadius = (3/2)*mm;
	G4double outerRadius = (25.7/2)*mm;
	G4double halflenght = (50/2)*mm;
	G4double phi_i = 0.*deg;
	G4double phi_f = 360.*deg;

	G4double worldEdge = 10*cm;

	G4Box* SWorld = new G4Box("solidWorld", worldEdge,worldEdge,worldEdge);
	G4LogicalVolume* LWorld = new G4LogicalVolume(SWorld, Air, "LWorld");
	G4VPhysicalVolume* PWorld = new G4PVPlacement(NULL,G4ThreeVector(0.,0.,0.),LWorld,"World",NULL,false,0,false);

	solidVol[0] = new G4Tubs("Vol_0",0.*cm,outerRadius,halflenght,phi_i,phi_f);			//trigger
	solidVol[1] = new G4Tubs("Vol_1",innerRadius,outerRadius,7.*mm,phi_i,phi_f);	//first collimator
	solidVol[2] = new G4Tubs("Vol_2",0.*cm,outerRadius,1.5*mm,phi_i,phi_f);	//radiation source
	//solidVol[3] = new G4Tubs("Vol_3",innerRadius,outerRadius,halflenght,phi_i,phi_f);	//second collimator
	solidVol[4] = new G4Tubs("Vol_4",0.*cm,outerRadius,5.*mm,phi_i,phi_f);			//material
	solidVol[5] = new G4Tubs("Vol_5",0.*cm,outerRadius,halflenght,phi_i,phi_f);			//sensor

	volume[0] = new G4LogicalVolume(solidVol[0],Brillance,"trigger");
	volume[1] = new G4LogicalVolume(solidVol[1],Pb,"trigger collimator");
	volume[2] = new G4LogicalVolume(solidVol[2],Air,"radiation source");
	//volume[3] = new G4LogicalVolume(solidVol[3],Pb,"radiation collimator");
	volume[4] = new G4LogicalVolume(solidVol[4],Air,"matter");
	volume[5] = new G4LogicalVolume(solidVol[5],Brillance,"sensor");

	positions[0] = G4ThreeVector(0.*cm,0.*cm,-5*halflenght);
	positions[1] = G4ThreeVector(0.*cm,0.*cm,-3*halflenght);
	positions[2] = G4ThreeVector(0.*cm,0.*cm,-1*halflenght);
	//positions[3] = G4ThreeVector(0.*cm,0.*cm,1*halflenght);
	positions[4] = G4ThreeVector(0.*cm,0.*cm,3*halflenght);
	positions[5] = G4ThreeVector(0.*cm,0.*cm,5*halflenght);

	this->Trigger =
	new G4PVPlacement(NULL,positions[0],volume[0],"trigger",	LWorld,false,0,false);
	new G4PVPlacement(NULL,positions[1],volume[1],"tcollimator",LWorld,false,0,false);
	new G4PVPlacement(NULL,positions[2],volume[2],"rsource",	LWorld,false,0,false);
	//new G4PVPlacement(NULL,positions[3],volume[3],"rcollimator",LWorld,false,0,false);
	new G4PVPlacement(NULL,positions[4],volume[4],"matter",		LWorld,false,0,false);
	this->Sensor = 
	new G4PVPlacement(NULL,positions[5],volume[5],"sensor",		LWorld,false,0,false);
	/*** Trigger Construction ***/

	/*** Visual Atributtes ***/
	LWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

	volume[0]->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
	volume[1]->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	volume[2]->SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
	//volume[3]->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	volume[4]->SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
	volume[5]->SetVisAttributes(new G4VisAttributes(G4Colour::Red()));
	/*** Visual Atributtes ***/

	return PWorld;
}
