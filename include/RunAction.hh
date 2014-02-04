#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//#include "TNtupleD.h"
//#include "TFile.h"

class G4Run;

class RunAction : public G4UserRunAction {
public:
    RunAction();
    ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

/*    TNtupleD* tupleDetector0;
    TNtupleD* tupleDetector1;
    TNtupleD* tupleDetector2;*/

private:

//    TFile* file;
};

#endif

