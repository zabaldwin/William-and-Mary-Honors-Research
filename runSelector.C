// macro to process analysis TTree with TSelector
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"

//void runSelector(TString runNumber = "30496PARA", TString myPath = "/sciclone/home10/zabaldwin/wm_gluex/batch/simulation/TTree/") 
//void runSelector(TString runNumber = "30274", TString myPath = "/sciclone/data10/jrstevens01/RunPeriod-2017-01/analysis/ver20/tree_g__B4_F0/merged/")
void runSelector(TString runNumber = "30274", TString myPath = "/sciclone/gluex10/RunPeriod-2017-01/analysis/ver20/tree_g__B4_F0/merged/")                                               //DATA
//void runSelector(TString runNumber = "30320", TString myPath = "/sciclone/gluex10/gluex_simulations/recon-2017_01-ver03/gen_compton/ver03_beamProp/analysis/tree_g__B4_F0/merged/")     //COMPTON
//void runSelector(TString runNumber = "30320", TString myPath = "/sciclone/gluex10/gluex_simulations/recon-2017_01-ver03/gen_pi0/ver03_beamProp/analysis/tree_g__B4_F0/merged/")            //PI0
//void runSelector(TString runNumber = "30320", TString myPath = "/sciclone/gluex10/gluex_simulations/recon-2017_01-ver03/gen_pi0/ver03_beamProp/analysis/tree_g__B4_F0/merged/")
//void runSelector(TString runNumber = "030274", TString myPath = "/sciclone/data10/jrstevens01/RunPeriod-2017-01/analysis/ver08/tree_g__F0_B3/merged/") 
//void runSelector(TString runNumber = "30274", TString myPath = "/sciclone/data10/jrstevens01/RunPeriod-2017-01/analysis/private-2017-07-14/compton/")  
//void runSelector(TString runNumber = "11367", TString myPath = "/sciclone/data10/jrstevens01/RunPeriod-2016-02/analysis/private-2017-05-30/compton/")

{
  // Load DSelector library
  gROOT->ProcessLine(".x $(ROOT_ANALYSIS_HOME)/scripts/Load_DSelector.C");

  int Proof_Nthreads = 8;

  // process signal 
  TString sampleDir = myPath;
  //sampleDir += Form(runNumber.Data());
  //sampleDir += Form("0%sPARA/", runNumber.Data());
  //sampleDir += Form("0%s/", runNumber.Data());
  //sampleDir += Form("%s/", runNumber.Data());
  cout<<"running selector on files in: "<<sampleDir.Data()<<endl;
  TChain *chain = new TChain("g__B4_F0_Tree");
  //TChain *chain = new TChain("compton_Tree");
  TSystemDirectory dir(sampleDir, sampleDir);
  TList *files = dir.GetListOfFiles();
  if(files) {
          TSystemFile *file;
          TString fileName;
          TIter next(files);

          // loop over files
          while ((file=(TSystemFile*)next())) {
                  fileName = file->GetName();
                  if(fileName.Contains(runNumber)) {
                          cout<<fileName.Data()<<endl;

                          // check if file corrupted
                          TFile f(sampleDir+fileName);
                          if(f.TestBit(TFile::kRecovered)) {
                                  cout<<"file corrupted -> skipping"<<endl;
                                  continue;
                          }
                          if(f.IsZombie()) {
                                  cout<<"file is a Zombie -> skipping"<<endl;
                                  continue;
                          }

                          // add file to chain
                          chain->Add(sampleDir+fileName);
                  }
          }

          cout<<"total entries in TChain = "<<chain->GetEntries()<<endl;
          DPROOFLiteManager::Process_Chain(chain, "DSelector_compton.C+", Proof_Nthreads, Form("hist_compton_%s.acc.root", runNumber.Data()));
  }

  return;
}
                                                                                                                                                                69,1          Bot
