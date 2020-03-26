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



void RootFit(){

TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/hist_sum_PARA_30320_31057.root";

TFile *comp_file = TFile::Open(C_pathWay);
TFile *pi0_file = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);
          
int a = 0;
int j = 1;
int k = 2;
int l = 3;
int m = 4;
int n = 5;   
/*-----------------------------------------------------------------------------------------------*/

TString hist = "SigTrans-vs-Variables/";
    
TString deltaPhi[2] = {"Delta_Phi_1D"}; 
TString deltaTheta[2] = {"Delta_Theta_O", "Delta_Theta_Up"};
TString deltaEnergy[2] = {"Delta_Energy_O", "Delta_Energy_Up"};
dPhi = hist + deltaPhi[a];
dTheta_O = hist + deltaTheta[a];
dEnergy_O = hist + deltaEnergy[a];
dTheta_Up = hist + deltaTheta[j];
dEnergy_Up = hist + deltaEnergy[j];

Roovar_data = (TH1F*)Para->Get(dPhi);
Roovar_comp = (TH1F*)comp_file->Get(dPhi);
Roovar_pi0 = (TH1F*)pi0_file->Get(dPhi);

/*-----------------------------------------------------------------------------------------------*/

gStyle->SetOptStat(1111111111);
Roovar_data->Draw();

//#if 0
int maxBins = Roovar_data->GetXaxis()->GetNbins();
cout << maxBins << endl;
for(int i=0; i< maxBins; i++){
        if(Roovar_data->GetBinContent(i) < 0.001 ){
                Roovar_data->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_comp->GetBinContent(i) < 0.001 ){
                Roovar_comp->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_pi0->GetBinContent(i) < 0.001){
                Roovar_pi0->SetBinContent(i,1/1.0E+45);}}

RooRealVar x("x","x", 172, 188);


RooDataHist data("data", "data", RooArgList(x), Roovar_data);
RooDataHist mcComp("mcComp", "mcComp", RooArgList(x), Roovar_comp);
RooDataHist mcPi0("mcPi0", "mcPi0", RooArgList(x), Roovar_pi0);

//Make PDFs of the histograms 
RooHistPdf pdf_data("pdf_data", "pdf_data", x, data);
RooHistPdf pdf_mcComp("pdf_mcComp", "pdf_mcComp", x, mcComp);
RooHistPdf pdf_mcPi0("pdf_mcPi0", "pdf_mcPi0", x, mcPi0);



RooRealVar yieldComp("yieldComp", "yieldComp", 172, Roovar_data->Integral());
RooRealVar yieldPi0("yieldPi0", "yieldPi0", 172, Roovar_data->Integral());

//Combine the MC PDFs into one model
RooAddPdf combine("combine", "combine", RooArgList(pdf_mcComp, pdf_mcPi0),  RooArgList(yieldComp, yieldPi0));

//Fit the combined MC PDFs to data
////------------------------------

combine.fitTo(data, Extended(kTRUE));

//Plots both on the same histogrami
//SigTrans
RooPlot* fitframe = x.frame(170,190);

data.plotOn(fitframe, RooFit::LineColor(kRed));

/*______________________________________________________________________________________________________________________________________*/
// 
#if 0
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.0005); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.005); //#if 0

//SigTransInt_t binx1 = Roovar_data->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data->GetXaxis()->FindBin(0.01);
Int_t binx1 = Roovar_data->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data->GetXaxis()->FindBin(0.01);

//SigTheta
//Int_t binx1 = Roovar_data->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data->GetXaxis()->FindBin(0.003);

//SigLong
//Int_t binx1 = Roovar_data->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data->GetXaxis()->FindBin(10);

Float_t entries_Comp = Roovar_comp->Integral(binx1, binx2); //4227.0; 
Float_t entries_Pi0 = Roovar_pi0->Integral(binx1, binx2); //69605.0;
Float_t data_scale = Roovar_data->Integral(binx1, binx2);

//cout<< entries_Comp << endl;

//Float_t scaleFactor_SigLongComp = 322.71247;//(670/851)*4.09893E02;
//Float_t scaleFactor_SigLongPi0 = 347.31588;//(670/851)*4.41143E02;
// Trans
Float_t scaleFactor_SigTransComp = ((617/data_scale)*484);//501);
Float_t scaleFactor_SigTransPi0 = ((617/data_scale)*133);//155);

Float_t scaleComp = (scaleFactor_SigTransComp)/entries_Comp;
Float_t scalePi0 =  (scaleFactor_SigTransPi0)/entries_Pi0;


//Old sig Trans 1449
//Float_t scaleFactor_SigTransComp = ((1563.20/data_scale)*7.50977);
//Float_t scaleFactor_SigTransPi0 = ((1563.20/data_scale)*1.55569E03);
//
//Float_t scaleComp = (scaleFactor_SigTransComp)/entries_Comp;
//Float_t scalePi0 =  (scaleFactor_SigTransPi0)/entries_Pi0;
//SigTheta
//Float_t scaleFactor_SigThetaComp = ((613/data_scale)*521);
//Float_t scaleFactor_SigThetaPi0 = ((613/data_scale)*92);

//Float_t scaleComp =  (scaleFactor_SigThetaComp)/entries_Comp;
//Float_t scalePi0 =  (scaleFactor_SigThetaPi0)/entries_Pi0;

//SigLong
//Float_t scaleFactor_SigLongComp = ((537/data_scale)*138);
//Float_t scaleFactor_SigLongPi0 = ((537/data_scale)*348);

//Float_t scaleComp = (scaleFactor_SigLongComp)/entries_Comp;
//Float_t scalePi0 =  (scaleFactor_SigLongPi0)/entries_Pi0;

//cout<< scaleComp << endl;

TH1F *Roovar_comp_Fin = (TH1F*)Roovar_comp->Clone("Roovar_comp_Fin");
Roovar_comp_Fin->Scale(scaleComp);
//Roovar_comp_Fin->Draw();

TH1F *Roovar_pi0_Fin = (TH1F*)Roovar_pi0->Clone("Roovar_pi0_Fin");
Roovar_pi0_Fin->Scale(scalePi0);



cout<< Roovar_comp_Fin->Integral(binx1, binx2) << endl;
cout<< Roovar_pi0_Fin->Integral(binx1, binx2)<< endl;
cout<< data_scale <<endl;

#if 0 
RooDataHist mcComp_Scale("mcComp", "mcComp", RooArgList(x), Roovar_comp_Fin);

RooDataHist mcPi0_Scale("mcPi0", "mcPi0", RooArgList(x), Roovar_pi0_Fin);

RooHistPdf pdf_mcComp_Scale("pdf_mcComp", "pdf_mcComp", x, mcComp_Scale);

RooHistPdf pdf_mcPi0_Scale("pdf_mcPi0", "pdf_mcPi0", x, mcPi0_Scale);
#endif 

//RooPlot* mframe = x.frame() ;
//mcComp_Scale.plotOn(mframe) ;
//mframe->Draw();

#endif
//pdf_mcComp.plotOn(fitframe, RooFit::LineColor(kOrange));
//pdf_mcPi0.plotOn(fitframe, RooFit::LineColor(kGreen));
combine.plotOn(fitframe, LineColor(kBlue));
combine.paramOn(fitframe);

//cout<< combine.Integral(binx1, binx2) <<endl;
//combine.plotOn(fitframe, Components("mcComp"), LineColor(kGreen));
//combine.plotOn(fitframe, Components("mcPi0"), LineColor(kBlue)); 


TCanvas* main = new TCanvas("main", "SigTheta RooFit Histogram ", 800, 400);
//fitframe->SetAxisRange(0, 500, "Y"); 
//gStyle->SetOptStat();
//fitframe->Rebin(1);
fitframe->Draw();

#if 0 

TCanvas* secondary = new TCanvas("secondary", "RooFit Histogram ", 800, 400);
Roovar_data->SetLineColor(kRed);
//Roovar_data->SetAxisRange(0, 50, "Y");
Roovar_data->Draw();
Roovar_comp_Fin->SetLineColor(kOrange);
//Roovar_comp_Fin->SetLineWidth(2);
Roovar_comp_Fin->Draw("same h");
Roovar_pi0_Fin->SetLineColor(kGreen);
//Roovar_pi0_Fin->SetLineWidth(2);
Roovar_pi0_Fin->Draw("same h");
//RooArgSet* parameters = combine.getParameters(x);
//cout << parameters << endl;
#endif
//#endif


return;}
