#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

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

	//G4double phi = twopi*G4UniformRand();
	//G4double costheta = G4UniformRand();
	//G4double theta = std::acos(costheta);
	/*G4double sintheta = std::sin(theta);
	G4double sinphi = std::sin(phi);
	G4double cosphi = std::cos(phi);*/
//	G4ThreeVector direction(sintheta*sinphi,sintheta*cosphi,costheta);

	G4double x,y,z;
	G4double r = 1.*mm;
	do{
		x = 2*r*G4UniformRand()-r;
		y = 2*r*G4UniformRand()-r;	
	}while(x*x+y*y>r*r);

	z = -0.6*cm + 0.1*(2.0*G4UniformRand()-1.0)*cm;

	G4ThreeVector position(x,y,z);
	G4ThreeVector direction(0.,0.,1.);

	particleGun->SetParticlePosition(position);

	particleGun->SetParticleMomentumDirection(direction);
	particleGun->GeneratePrimaryVertex(Event);

	//particleGun->SetParticleMomentumDirection(-direction);
	//particleGun->GeneratePrimaryVertex(Event);

//	particleSource->GeneratePrimaryVertex(Event);

}
