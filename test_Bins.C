#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
//using namespace RooFit;



void test_Bins(){

//Set up input files
//------------------------------
//Using the normal MC files
TString C_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root";
TString P0_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root";
TString D_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30274_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

TString front = "Histograms/Egamma5_6/";
TString back[3] = {"SigLong YieldEgamma5_6","SigTheta YieldEgamma5_6","SigTrans YieldEgamma5_6"};
SigLong = front + back[0];
SigTheta = front + back[1];
SigTrans = front + back[2];

TFile* iFile = new TFile(C_pathWay, "read");
TTree* iTree = (TTree*)iFile->Get(SigLong);

TCut *noZero = new TCut("locPhotonSigLongBCALShower < 1");
iTree->Draw(*noZero);

//Change the different Sig variable
/*Roovar_data = (TH1F*)Para->Get(SigLong);
Roovar_comp = (TH1F*)comp->Get(SigLong);
Roovar_pi0 = (TH1F*)pi0->Get(SigLong);
Roovar_pi0->SetAxisRange(0, 200, "Y");
//Roovar_comp->Draw();
int  bin;
Roovar_comp->SetBinContent(bin, 1); 
Double_t bincontent = Roovar_comp->GetBinContent(bin);
//TAxis *getaxis = Roovar_data->GetXaxis();
//Double_t bincontent = getaxis->GetXmax();
//Roovar_comp->SetAxisRange(0, 200, "Y");
cout << bincontent << endl;

Roovar_comp->Draw();

*/
return;}
