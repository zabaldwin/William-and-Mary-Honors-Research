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



void RootFit_2Variable_old(){

//Set up input files
//------------------------------
//Using the normal MC files
//TString C_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/Oct1/hist_compton_30001.acc.root";
//TString P0_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/Oct1/hist_compton_30002.acc.root";
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

//TString front = "Histograms/Egamma5_6/";
//TString front = "ComptonPurity/";
//TString back_2varComp[3] = {"SigTrans_SigTheta_DPlessThan_B_SignalCutComp","SigLong_SigTrans_DPlessThan_B_SignalCutComp","SigLong_SigTheta_DPlessThan_B_SignalCutComp"};
//TString back_2varPi0[3] = {"SigTrans_SigTheta_DPlessThan_B_SignalCutPi0","SigLong_SigTrans_DPlessThan_B_SignalCutPi0","SigLong_SigTheta_DPlessThan_B_SignalCutPi0"};

//TString back_DPlessSignal[6] = {"SigLong Pure DPlessThan BCAL SignalCutComp","SigTheta Pure DPlessThan BCAL SignalCutComp","SigTrans Pure DPlessThan BCAL SignalCutComp", "SigLong Pure DPlessThan BCAL SignalCutPi0","SigTheta Pure DPlessThan BCAL SignalCutPi0","SigTrans Pure DPlessThan BCAL SignalCutPi0"};
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//#if 0
TString front = "SigTrans-vs-Variables/";
TString back_2var[3] ={"SigTrans SigTheta varyMore PBCALPreShower", "SigTrans SigLong varyMore PBCALPreShower", "SigLong SigTheta varyMore PBCALPreShower"};

SigTrans_SigTheta = front + back_2var[a];
SigTrans_SigLong = front + back_2var[j];
SigLong_SigTheta = front + back_2var[k];

Roovar_data_twoVar = (TH2F*)Para->Get(SigTrans_SigTheta);
Roovar_comp_twoVar = (TH2F*)comp->Get(SigTrans_SigTheta);
Roovar_pi0_twoVar = (TH2F*)pi0->Get(SigTrans_SigTheta);
//#endif

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#if 0
SigTrans_SigTheta_Comp = front + back_2varComp[a];
SigLong_SigTrans_Comp = front + back_2varComp[j];
SigLong_SigTheta_Comp = front + back_2varComp[k];

SigTrans_SigTheta_Pi0 = front + back_2varPi0[a];
SigLong_SigTrans_Pi0 = front + back_2varPi0[j];
SigLong_SigTheta_Pi0 = front + back_2varPi0[k];

//SigLong_DPlessSignalComp = front+back_DPlessSignal[i];
//SigTheta_DPlessSignalComp = front+back_DPlessSignal[j];
//SigTrans_DPlessSignalComp = front+back_DPlessSignal[k];
//#endif

//Change the different Sig variable
//#if 0
Roovar_data_Trans = (TH2F*)Para->Get(SigTrans_DPlessSignalComp);
Roovar_comp_Trans = (TH2F*)comp->Get(SigTrans_DPlessSignalComp);
Roovar_pi0_Trans = (TH2F*)pi0->Get(SigTrans_DPlessSignalComp);

Roovar_data_Theta= (TH2F*)Para->Get(SigTheta_DPlessSignalComp);
Roovar_comp_Theta= (TH2F*)comp->Get(SigTheta_DPlessSignalComp);
Roovar_pi0_Theta= (TH2F*)pi0->Get(SigTheta_DPlessSignalComp);
//#endif

Roovar_data_twoVar = (TH2F*)Para->Get(SigLong_SigTrans_Comp);
Roovar_comp_twoVar = (TH2F*)comp->Get(SigLong_SigTrans_Comp);
Roovar_pi0_twoVar = (TH2F*)pi0->Get(SigLong_SigTrans_Comp);
#endif

//______________________________________________________________________________________________________//
int maxBins = (Roovar_data_twoVar->GetXaxis()->GetNbins())*(Roovar_data_twoVar->GetYaxis()->GetNbins());

for(int i=0; i< maxBins; i++){
        if(Roovar_data_twoVar->GetBinContent(i) < 0.001 ){
                Roovar_data_twoVar->SetBinContent(i,1/1.0E+45);}}
//gStyle->SetOptStat(1111111);
//Roovar_data_twoVar->SetMinimum(0.01);
//Roovar_data_twoVar->Draw("colz");

for(int i=0; i< maxBins; i++) {
        if(Roovar_comp_twoVar->GetBinContent(i) < 0.001 ){
                Roovar_comp_twoVar->SetBinContent(i,1/1.0E+45);}}

for(int i=0; i< maxBins; i++) {
        if(Roovar_pi0_twoVar->GetBinContent(i) < 0.001){
                Roovar_pi0_twoVar->SetBinContent(i,1/1.0E+45);}}
//#endif
//gStyle->SetOptStat(1111111);
//Roovar_data_twoVar->Draw("colz");

//Roovar_data_Trans->Add(Roovar_data_Theta);
//Roovar_comp_Trans->Add(Roovar_comp_Theta);
//Roovar_pi0_Trans->Add(Roovar_pi0_Theta);
/*
TCanvas* main = new TCanvas("main", "SigTrans SigTheta RooFit Histogram ", 800, 400);
main->Divide(2,1);
main->cd(1);
Roovar_data_Trans->SetLineColor(kBlack);
Roovar_comp_Trans->SetLineColor(kRed);
Roovar_pi0_Trans->SetLineColor(kGreen);
Roovar_comp_Trans->Draw();
Roovar_data_Trans->Draw("SAME");
Roovar_pi0_Trans->Draw("SAME");
main->cd(2);
Roovar_data_Theta->SetLineColor(kBlack);
Roovar_comp_Theta->SetLineColor(kRed);
Roovar_pi0_Theta->SetLineColor(kGreen);
Roovar_pi0_Theta->Draw();
Roovar_data_Theta->Draw("SAME");
Roovar_comp_Theta->Draw("SAME");
*/
//Roovar_data_Trans->Multiply(Roovar_data_Theta);
//Roovar_data_Trans->Draw("colz");

RooRealVar x_Long("x_Long", "x_Long", 0.5, 10.0);

RooRealVar x_Trans("x_Trans","x_Trans", 0.004, 0.02);
RooRealVar x_Theta("x_Theta", "x_Theta", 0.0004, 0.01);


//Old_SigTheta
//RooRealVar x_Theta("x_Theta", "x_Theta", 0.0004, 0.05);
//Old_SigTheta for SigTheta/Long
//RooRealVar x_Theta("x_Theta", "x_Theta", 0.0004, 0.005);
#if 0
//Long/Trans
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Long, x_Trans), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Long, x_Trans), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Long, x_Trans), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), mcPi0_twoVar);
#endif
#if 0
//Theta/Long
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Theta, x_Long), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Theta, x_Long), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Theta, x_Long), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Theta, x_Long), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Theta, x_Long), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Theta, x_Long), mcPi0_twoVar);
#endif

//#if 0
//SigTheta/Trans
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Theta, x_Trans), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Theta, x_Trans), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Theta, x_Trans), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), mcPi0_twoVar);
//#endif 

/*______________________________________________________________________________________________________________________________________________________________________________________________________*/
//Old_Trans/Theta
#if 0
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Theta, x_Trans), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Theta, x_Trans), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Theta, x_Trans), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Theta, x_Trans), mcPi0_twoVar);
#endif

#if 0
//Old_Theta/Long
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Long, x_Theta), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Long, x_Theta), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Long, x_Theta), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Long, x_Theta), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Long, x_Theta), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Long, x_Theta), mcPi0_twoVar);
#endif

#if 0
//Old_Long/Trans
RooDataHist data_twoVar("twoVar_data", "twoVar_data", RooArgList(x_Long, x_Trans), Roovar_data_twoVar);
RooDataHist mcPi0_twoVar("twoVarPi0", "twoVarPi0", RooArgList(x_Long, x_Trans), Roovar_pi0_twoVar);
RooDataHist mcComp_twoVar("twoVarComp", "twoVarComp", RooArgList(x_Long, x_Trans), Roovar_comp_twoVar);

RooHistPdf pdf_data_twoVar("pdf_data_twoVar", "pdf_data_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), data_twoVar);
RooHistPdf pdf_mcComp_twoVar("pdf_mcComp_twoVar", "pdf_mcComp_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), mcComp_twoVar);
RooHistPdf pdf_mcPi0_twoVar("pdf_mcPi0_twoVar", "pdf_mcPi0_twoVar", RooArgList(), RooArgList(x_Long, x_Trans), mcPi0_twoVar);
#endif
/*_______________________________________________________________________________________________________________________________________________________________________________________________________*/
/*_______For Recent Long/Trans___________________________________________________________________________________________________________________*/
//Trans
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.004); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);
//Long
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.5); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(10.0);





/*_______For Recent Theta/Trans__________________________________________________________________________________________________________________*/
//Trans
Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.004); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);
//Theta
Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0004); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(0.01);



/*_______For Recent Theta/Long__________________________________________________________________________________________________________________*/
//Long
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.5); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(10.);
//Theta
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0004); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(0.01);
/*______________________________________________________________________________________________________________________________________________________________________________________________________*/





/*______For Old Trans/Theta____________________________________________________________________________________________________________________*/
//Old_Trans
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.004); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);
//Old_Theta
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0004); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(0.05);



/*_____For Old Theta/Long__________________________________________________________________________________________________________________*/
//Old_Long
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.5); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(10.);
//Old_Theta
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.0004); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.005);



/*_______For Old Long/Trans___________________________________________________________________________________________________________________*/
//Old_Trans
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.004); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);
//Old_Long
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.5); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(10.0);


///*__________________________________________________________________________________________________________________________________________________*/
//

/*_____________________________________________________________________________________________________________________________________*/

RooRealVar yieldComp_twoVar("yieldComp_twoVar", "yieldComp_twoVar", 0, Roovar_data_twoVar->Integral(binx1, binx2, biny1, biny2));
RooRealVar yieldPi0_twoVar("yieldPi0_twoVar", "yieldPi0_twoVar", 0 , Roovar_data_twoVar->Integral(binx1, binx2, biny1, biny2));

RooAddPdf combine_twoVar("combine_twoVar", "combine_twoVar", RooArgList(pdf_mcComp_twoVar, pdf_mcPi0_twoVar),  RooArgList(yieldComp_twoVar, yieldPi0_twoVar));

combine_twoVar.fitTo(data_twoVar, Extended(kTRUE));

//RooPlot* fitframe = x_Trans_Theta.frame(0,0.05);
//combine_twoVar.paramOn(fitframe);
//data_twoVar.plotOn(fitframe);
//combine_twoVar.plotOn(fitframe);
//fitframe->Draw();


//Draws both plots (nonPDF) on a frame
//RooPlot* dataframe = x_Trans.frame(0, 0.015);
//data_Trans.plotOn(dataframe, LineColor(kBlue));
//data_Theta.plotOn(dataframe, LineColor(kGreen));
//dataframe->Draw();

//Plot Trans and Theta histograms
//RooPlot* dataframe_Trans = x_Trans.frame(0,0.015);
//data_Trans.plotOn(dataframe_Trans);
//mcComp_Theta.plotOn(dataframe_Theta, LineColor(kBlue));
//mcPi0_Trans.plotOn(dataframe_Theta, LineColor(kGreen));
//dataframe_Trans->Draw();

//Plot Both variables 


//Make PDFs of the histograms 
//RooHistPdf pdf_data1("pdf_data1", "pdf_data1", x, data1);
//RooHistPdf pdf_data2("pdf_data2", "pdf_data2", y, data2);
//RooProdPdf prod("product", "product", pdf_data1, pdf_data2);
//RooProdPdf add("addition", "addition", x_Trans, data_Trans);

//RooPlot* dataframe = x.frame(0,0.05);
//prod.plotOn(dataframe);
/*
RooHistPdf pdf_data("pdf_data", "pdf_data", x_Trans, data_Trans);
RooHistPdf pdf_mcComp("pdf_mcComp", "pdf_mcComp", x_TransComp, mcComp_Trans);
RooHistPdf pdf_mcPi0("pdf_mcPi0", "pdf_mcPi0", x_TransPi0, mcPi0_Trans);

//dataframe->Draw();
RooRealVar yieldComp("yieldComp", "yieldComp", 0, Roovar_data_Trans->Integral());
RooRealVar yieldPi0("yieldPi0", "yieldPi0", 0 , Roovar_data_Trans->Integral());

//Combine the MC PDFs into on model (may not be necessary)
RooAddPdf combine("combine", "combine", RooArgList(pdf_mcComp, pdf_mcPi0),  RooArgList(yieldComp, yieldPi0));

//Sets Canvas _____ Change Canvas Title 
TCanvas* cc = new TCanvas("cc", "SigLong Histograms", 800, 400);
cc->Divide(3,2);
cc->cd(1);
dataframe->SetAxisRange(0, 800, "Y"); dataframe->Draw();
cc->cd(2);
comptonframe->SetAxisRange(0, 800, "Y");   comptonframe->Draw();
cc->cd(3);
pi0frame->SetAxisRange(0, 800, "Y");   pi0frame->Draw();
//cc->cd(4);
//mcComp.plotOn(dataframe); mcPi0.plotOn(dataframe); dataframe->Draw();

//Fit the combined MC PDFs to data
////------------------------------

combine.fitTo(data_Trans, Extended(kTRUE));

//Plots both on the same histogram
RooPlot* fitframe = x_Trans.frame(0,0.015);

combine.paramOn(fitframe);
data_Trans.plotOn(fitframe, RooFit::LineColor(kRed));
combine.plotOn(fitframe, LineColor(kBlue));
//combine.plotOn(fitframe, Components("mcComp"), LineColor(kGreen));
//combine.plotOn(fitframe, Components("mcPi0"), LineColor(kBlue)); 

TCanvas* main = new TCanvas("main", "SigTrans SigTheta RooFit Histogram ", 800, 400);
//fitframe->SetAxisRange(0, 60, "Y"); fitframe->Draw();

RooArgSet* parameters = combine.getParameters(x);
cout << parameters << endl;
*/

return;}
