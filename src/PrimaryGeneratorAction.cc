#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
	: G4VUserPrimaryGeneratorAction(),
	  particleSource(NULL),
	  particleGun(NULL)
{
	G4int particles = 1;
	particleGun = new G4ParticleGun(particles);
	particleGun->SetParticleDefinition(G4Gamma::Gamma());
	particleGun->SetParticleEnergy(511*keV);


//	particleSource = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete particleGun;
//	delete particleSource;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* Event)
{
  G4double cosAlpha = 1. - G4UniformRand()*(1.- std::cos(15*deg));
  G4double sinAlpha = std::sqrt(1. - cosAlpha*cosAlpha);
  G4double psi      = twopi*G4UniformRand();  //psi uniform in [0, 2*pi]  
  G4ThreeVector direction(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha);

  G4double x,y,z;
  G4double r = (25.7/2)*mm;
  do{
    x = 2*r*G4UniformRand()-r;
    y = 2*r*G4UniformRand()-r;	
  } while (x*x+y*y>r*r);

  z = -1.5*mm + 1.5*(2.0*G4UniformRand()-1.0)*mm;


  G4ThreeVector position(x,y,z);

  particleGun->SetParticlePosition(position);

  particleGun->SetParticleMomentumDirection(direction);
  particleGun->GeneratePrimaryVertex(Event);


  particleGun->SetParticlePosition(position);
  G4ThreeVector dir = -1.*direction;
  particleGun->SetParticleMomentumDirection(dir);
  particleGun->GeneratePrimaryVertex(Event);

}
