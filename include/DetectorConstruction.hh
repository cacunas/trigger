#ifndef _DETECTORCONSTRUCTION_H_
#define _DETECTORCONSTRUCTION_H_

#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
 
    DetectorConstruction();
    ~DetectorConstruction();
    G4VPhysicalVolume *Construct();

  private:

    G4VPhysicalVolume *World;

};

#endif
