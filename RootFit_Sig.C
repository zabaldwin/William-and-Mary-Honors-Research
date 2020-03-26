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



void RootFit_Sig(){

//Set up input files
//------------------------------
//Using the normal MC files
//TString C_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root";
//TString P0_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root";
TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/hist_sum_PARA_30320_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

int a = 0;
int j = 1;
int k = 2;
int l = 3;
int m = 4;
int n = 5;
#if 0
//TString front = "Histograms/Egamma5_6/";
TString front = "ComptonPurity/";
TString back[3] = {"SigLong YieldEgamma5_6","SigTheta YieldEgamma5_6","SigTrans YieldEgamma5_6"};
TString back_DPless[3] = {"SigLong Pure DPlessThan BCAL","SigTheta Pure DPlessThan BCAL","SigTrans Pure DPlessThan BCAL"};
TString back_DPgra[3] = {"SigLong Pure DPgraThan BCAL","SigTheta Pure DPgraThan BCAL","SigTrans Pure DPgraThan BCAL"};

TString back_DPlessSignal[6] = {"SigLong Pure DPlessThan BCAL SignalCutComp","SigTheta Pure DPlessThan BCAL SignalCutComp","SigTrans Pure DPlessThan BCAL SignalCutComp", "SigLong Pure DPlessThan BCAL SignalCutPi0","SigTheta Pure DPlessThan BCAL SignalCutPi0","SigTrans Pure DPlessThan BCAL SignalCutPi0"};
TString back_DPgraSignal[6] = {"SigLong Pure DPgraThan BCAL SignalCutComp","SigTheta Pure DPgraThan BCAL SignalCutComp","SigTrans Pure DPgraThan BCAL SignalCutComp", "SigLong Pure DPgraThan BCAL SignalCutPi0","SigTheta Pure DPgraThan BCAL SignalCutPi0","SigTrans Pure DPgraThan BCAL SignalCutPi0"};
#endif
/*-----------------------------------------------------------------------------------------------*/

//#if 0
TString front = "SigTrans-vs-Variables/";
TString back_2var[3] ={"SigTrans_varyMore_.925_PBCALPreShowerE", "SigLong_varyMore_PBCALPreShowerE","SigTheta_varyMore_.95_PBCALPreShowerE"};// /*"SigTheta_varyMore__piCut_.00115_PBCALPreShowerE"};*/"SigTheta_varyMore_.95_PBCALPreShowerE"};

TString back_2var2[1] ={"SigTrans_varyMore_PBCALPreShowerE"};

SigTrans = front + back_2var[a];
SigLong = front + back_2var[j];
SigTheta = front + back_2var[k];
SigTrans_MC = front + back_2var2[a];

Roovar_data = (TH1F*)Para->Get(SigTrans);
Roovar_comp = (TH1F*)comp->Get(SigTrans_MC);
Roovar_pi0 = (TH1F*)pi0->Get(SigTrans_MC);
//Roovar_comp2 = (TH1F*)comp->Get(SigTheta_MC);
//Roovar_pi02 = (TH1F*)pi0->Get(SigTheta_MC);
//Roovar_data->SetAxisRange(0, 1, "X");
//Roovar_data->Draw("colz");


//gStyle->SetOptStat(11111111);
//Roovar_pi0->Draw();

//Roovar_data->Rebin(1);
//Roovar_comp->Rebin(1);
//Roovar_pi0->Rebin(1);

//Roovar_data->Draw();
//#endif
/*-----------------------------------------------------------------------------------------------*/
#if 0
//int i = 0;
SigLong_DPless = front + back_DPless[a];
SigTheta_DPless = front + back_DPless[j];
SigTrans_DPless = front + back_DPless[k]; 

SigLong_DPgra = front + back_DPgra[a];
SigTheta_DPgra = front + back_DPgra[j];
SigTrans_DPgra = front + back_DPgra[k];
SigLong_DPlessSignalComp = front+back_DPlessSignal[a];
SigTheta_DPlessSignalComp = front+back_DPlessSignal[j];
SigTrans_DPlessSignalComp = front+back_DPlessSignal[k];
SigLong_DPlessSignalPi0 = front+back_DPlessSignal[l];
SigTheta_DPlessSignalPi0 = front+back_DPlessSignal[m];
SigTrans_DPlessSignalPi0 = front+back_DPlessSignal[n];

SigLong_DPgraSignalComp = front+back_DPgraSignal[a];
SigTheta_DPgraSignalComp = front+back_DPgraSignal[j];
SigTrans_DPgraSignalComp = front+back_DPgraSignal[k];
SigLong_DPgraSignalPi0 = front+back_DPgraSignal[l];
SigTheta_DPgraSignalPi0 = front+back_DPgraSignal[m];
SigTrans_DPgraSignalPi0 = front+back_DPgraSignal[n];
//Change the different Sig variable
Roovar_data = (TH2F*)Para->Get(SigTrans_DPlessSignalComp);
Roovar_comp = (TH2F*)comp->Get(SigTrans_DPlessSignalComp);
Roovar_pi0 = (TH2F*)pi0->Get(SigTrans_DPlessSignalComp);
#endif
//#if 0
int maxBins = (Roovar_data->GetXaxis()->GetNbins())*(Roovar_data->GetYaxis()->GetNbins());

for(int i=0; i< maxBins; i++){
        if(Roovar_data->GetBinContent(i) < 0.001 ){
                Roovar_data->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_comp->GetBinContent(i) < 0.001 ){
                Roovar_comp->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_pi0->GetBinContent(i) < 0.001){
                Roovar_pi0->SetBinContent(i,1/1.0E+45);}}

//gStyle->SetOptStat(11111111);
//Roovar_pi0->Draw();
//#endif 
#if 0
for(int i=0; i< Roovar_data->GetXaxis()->GetNbins(); i++) {
        if(Roovar_data->GetBinContent(i) < 0.001){
                Roovar_data->SetBinContent(i,(1/(1* exp(300))));}
}

for(int i=0; i< Roovar_comp->GetXaxis()->GetNbins(); i++) {
        if(Roovar_comp->GetBinContent(i) < 0.001){
                Roovar_comp->SetBinContent(i,(1/(1* exp(300))));}
}


for(int i=0; i< Roovar_pi0->GetXaxis()->GetNbins(); i++) {
        if(Roovar_pi0->GetBinContent(i) < 0.001){
                Roovar_pi0->SetBinContent(i,(1/(1* exp(300))));}
}
#endif
//Make RooFit histograms from the input *___________ DIFFERENT SIG VARIABLES ____________*

//SigTrans
RooRealVar x("x","x", 0, 0.02);

//SigTheta
//RooRealVar x("x","x", 0, 0.003);

//SigLong
//RooRealVar x("x","x", 0, 10);

RooDataHist data("data", "data", RooArgList(x), Roovar_data);
RooDataHist mcComp("mcComp", "mcComp", RooArgList(x), Roovar_comp);
RooDataHist mcPi0("mcPi0", "mcPi0", RooArgList(x), Roovar_pi0);

//Plot the histograms 
#if 0
RooPlot* dataframe = x.frame(0,0.003);
data.plotOn(dataframe);

RooPlot* comptonframe = x.frame(0,0.004);
mcComp.plotOn(comptonframe, LineColor(kBlue));

RooPlot* pi0frame = x.frame(0,0.004);
mcPi0.plotOn(pi0frame, LineColor(kGreen));
#endif

//Make PDFs of the histograms 
RooHistPdf pdf_data("pdf_data", "pdf_data", x, data);
RooHistPdf pdf_mcComp("pdf_mcComp", "pdf_mcComp", x, mcComp);
RooHistPdf pdf_mcPi0("pdf_mcPi0", "pdf_mcPi0", x, mcPi0);



RooRealVar yieldComp("yieldComp", "yieldComp", 0, Roovar_data->Integral());
RooRealVar yieldPi0("yieldPi0", "yieldPi0", 0, Roovar_data->Integral());

//Combine the MC PDFs into on model (may not be necessary)
RooAddPdf combine("combine", "combine", RooArgList(pdf_mcComp, pdf_mcPi0),  RooArgList(yieldComp, yieldPi0));

//Fit the combined MC PDFs to data
////------------------------------

combine.fitTo(data, Extended(kTRUE));
//Plots both on the same histogrami
//SigTrans
RooPlot* fitframe = x.frame(0.003,0.02);

//SigTheta
//RooPlot* fitframe = x.frame(0,0.003);

//SigLong
//RooPlot* fitframe = x.frame(0,10.);

data.plotOn(fitframe, RooFit::LineColor(kRed));
/*______________________________________________________________________________________________________________________________________*/
// 
//#if 0
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

//#endif
//pdf_mcComp.plotOn(fitframe, RooFit::LineColor(kOrange));
//pdf_mcPi0.plotOn(fitframe, RooFit::LineColor(kGreen));
combine.plotOn(fitframe, LineColor(kBlue));
combine.paramOn(fitframe);
//cout<< combine.Integral(binx1, binx2) <<endl;
//combine.plotOn(fitframe, Components("mcComp"), LineColor(kGreen));
//combine.plotOn(fitframe, Components("mcPi0"), LineColor(kBlue)); 


TCanvas* main = new TCanvas("main", "SigTheta RooFit Histogram ", 800, 400);
//fitframe->SetAxisRange(0, 60, "Y"); 
//gStyle->SetOptStat();
//fitframe->Rebin(1);
fitframe->Draw();

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

return;}
