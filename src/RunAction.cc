#include "globals.hh"
#include "RunAction.hh"
#include "G4Run.hh"

//#include "TFile.h"
//#include "TNtupleD.h"

#include <iostream>

RunAction::RunAction()
: G4UserRunAction()
//tupleDetector0(NULL), tupleDetector1(NULL), tupleDetector2(NULL), file(NULL)
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "Run " << run->GetRunID() << " start." << G4endl;

 /*   std::ostringstream filename;
  filename << "hist.root";

    file = new TFile(filename.str().c_str(), "RECREATE");
    tupleDetector0 = new TNtupleD("Tuple0", "event - position - detector - nhits - energy",
            "eventID:eID:det:nhits:energy");
    tupleDetector1 = new TNtupleD("Tuple1", "event - position - detector - nhits - energy",
            "eventID:eID:det:nhits:energy");
    tupleDetector2 = new TNtupleD("Tuple2", "event - position - detector - nhits - energy",
            "eventID:eID:det:nhits:energy");
*/
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4cout << "Run " << run->GetRunID() << " done." << G4endl;

/*    tupleDetector0->Write("Tuple0");
    delete tupleDetector0;
    tupleDetector1->Write("Tuple1");
    delete tupleDetector1;
    tupleDetector2->Write("Tuple2");
    delete tupleDetector2;
    file->Close();
*/
}
