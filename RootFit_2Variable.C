#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;



void RootFit_2Variable(){

//Set up input files
//------------------------------
TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/hist_sum_PARA_30320_31057.root";

TFile *comp_file = TFile::Open(C_pathWay);
TFile *pi0_file = TFile::Open(P0_pathWay); 
TFile *Para = TFile::Open(D_pathWay);
          
int a = 0;
int j = 1;
int k = 2;
             
      
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//TString front = "SigTrans-vs-Variables/";
//TString back_2var[3] ={"SigTrans SigTheta varyMore PBCALPreShower", "SigTrans SigLong varyMore PBCALPreShower", "SigLong SigTheta varyMore PBCALPreShower"};

TString hist = "SigTrans-vs-Variables/";
    
TString deltaPhi = "DeltaPhi_t";
    
dPhi_t = hist + deltaPhi;

Roovar_data_twoVar = (TH2F*)Para->Get(dPhi_t);
Roovar_comp_twoVar = (TH2F*)comp_file->Get(dPhi_t);
Roovar_pi0_twoVar = (TH2F*)pi0_file->Get(dPhi_t);


/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int maxBins = (Roovar_data_twoVar->GetXaxis()->GetNbins())*(Roovar_data_twoVar->GetYaxis()->GetNbins());

for(int i=0; i< maxBins; i++){
        if(Roovar_data_twoVar->GetBinContent(i) < 0.001 ){
                Roovar_data_twoVar->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_comp_twoVar->GetBinContent(i) < 0.001 ){
                Roovar_comp_twoVar->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_pi0_twoVar->GetBinContent(i) < 0.001){
                Roovar_pi0_twoVar->SetBinContent(i,1/1.0E+45);}}

gStyle->SetOptStat(1111111);
Roovar_data_twoVar->Draw("colz");


RooRealVar x_Phi("x_Phi", "x_Phi", 170.0, 190.0);

RooRealVar x_t("x_Trans","x_Trans", 0.0, 5.0);
//dPhi/t
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_t, x_Phi), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_t, x_Phi), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_t, x_Phi), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_t, x_Phi), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_t, x_Phi), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_t, x_Phi), mcPi0_twoVar);

/*___________________________________________________________________________________________________________________________________________*/
//dPhi
Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(170.0); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(190.0);
//t
Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(5.0);

/*___________________________________________________________________________________________________________________________________________*/

RooRealVar yieldComp_twoVar("yieldComp_twoVar", "yieldComp_twoVar", 0, Roovar_data_twoVar->Integral(binx1, binx2, biny1, biny2));
RooRealVar yieldPi0_twoVar("yieldPi0_twoVar", "yieldPi0_twoVar", 0 , Roovar_data_twoVar->Integral(binx1, binx2, biny1, biny2));

RooAddPdf combine_twoVar("combine_twoVar", "combine_twoVar", RooArgList(pdf_mcComp_twoVar, pdf_mcPi0_twoVar),  RooArgList(yieldComp_twoVar, yieldPi0_twoVar));

combine_twoVar.fitTo(data_twoVar, Extended(kTRUE));


return;}
