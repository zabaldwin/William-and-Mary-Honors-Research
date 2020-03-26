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
#include <sstream>

void Chi2(){

TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/Apr29/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/Apr29/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/Apr29/hist_sum_PARA_30320_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

          
TString numb[14] = {".80", ".825", ".85", ".875", ".90", ".925", ".95", ".975", "1.05", "1.1", "1.15", "1.2", "1.25", "1.3"};
          
//Double_t z[10] = {.90, .925, .95, .975, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3};
        
TH1F *Data_Trans[14], *Comp_Trans[14], *Pi0_Trans[14];
TH1F *Data_Theta[14], *Comp_Theta[14], *Pi0_Theta[14];
      


for(int x=0; x< 14; x++){ 
TString SigTrans = "SigTrans-vs-Variables/SigTrans_varyMore_";
                SigTrans += numb[x]; 
                SigTrans += "_PBCALPreShowerE";
                
                TString SigTheta = "SigTrans-vs-Variables/SigTheta_varyMore_";
                SigTheta += numb[x];
                SigTheta += "_PBCALPreShowerE";

                Data_Trans[x] = (TH1F*)Para->Get(SigTrans);
                //Comp_Trans[x] = (TH1F*)comp->Get(SigTrans);
                //Pi0_Trans[x] = (TH1F*)pi0->Get(SigTrans);             

                Data_Theta[x] = (TH1F*)Para->Get(SigTheta);
                //Comp_Theta[x] = (TH1F*)comp->Get(SigTheta);
                //Pi0_Theta[x] = (TH1F*)pi0->Get(SigTheta);

                }
TString front = "SigTrans-vs-Variables/";
TString back_2var[2] ={"SigTrans_varyMore_PBCALPreShowerE", "SigTheta_varyMore_PBCALPreShowerE"};


Double_t arr[14];

int a=0, k=1;
sigTrans = front + back_2var[a];
sigTheta = front + back_2var[k];
Roovar_dataTrans_Original = (TH1F*)Para->Get(sigTrans);
Roovar_compTrans_Original = (TH1F*)comp->Get(sigTrans);
Roovar_pi0Trans_Original = (TH1F*)pi0->Get(sigTrans);

Roovar_dataTheta_Original = (TH1F*)Para->Get(sigTheta);
Roovar_compTheta_Original = (TH1F*)comp->Get(sigTheta);
Roovar_pi0Theta_Original = (TH1F*)pi0->Get(sigTheta);

TH1F* Roovar_dataTrans = Data_Trans[14];
TH1F* Roovar_compTrans = Comp_Trans[14];
TH1F* Roovar_pi0Trans = Pi0_Trans[14];

TH1F* Roovar_dataTheta = Data_Theta[14];
TH1F* Roovar_compTheta = Comp_Theta[14];
TH1F* Roovar_pi0Theta = Pi0_Theta[14];

Roovar_compTrans = Roovar_compTrans_Original;
Roovar_pi0Trans = Roovar_pi0Trans_Original;

Roovar_compTheta = Roovar_compTheta_Original;
Roovar_pi0Theta = Roovar_pi0Theta_Original;


///Roovar_compTheta->Draw("colz");

int count =0;

TH2F *chiHist = new TH2F("chiHist","chiHist", 300, 0, 1.5, 200, 0, .0405);
//chiHist->Draw();
for(count; count <15; count ++){
//for(int count=0; count<2; coutn ++){  
        //#if 0
#if 0      
Roovar_dataTrans = Data_Trans[count];
                
                        
                if(count==14){
                        Roovar_dataTrans = Roovar_dataTrans_Original;
                        //Roovar_compTrans = Roovar_compTrans_Original;
                        //Roovar_pi0Trans = Roovar_pi0Trans_Original;
                        }
                

                int maxBins = (Roovar_dataTrans->GetXaxis()->GetNbins())*(Roovar_dataTrans->GetYaxis()->GetNbins());

                for(int i=0; i< maxBins; i++){
                        if(Roovar_dataTrans->GetBinContent(i) < 0.001 ){
                                Roovar_dataTrans->SetBinContent(i,1/1.0E+45);}}

                for(int i=0; i< maxBins; i++) {
                        if(Roovar_compTrans->GetBinContent(i) < 0.001 ){
                                Roovar_compTrans->SetBinContent(i,1/1.0E+45);}}

                for(int i=0; i< maxBins; i++) {
                        if(Roovar_pi0Trans->GetBinContent(i) < 0.001){
                                Roovar_pi0Trans->SetBinContent(i,1/1.0E+45);}}

                RooRealVar x("x","x", 0, 0.02);
                        
                RooDataHist data("data", "data", RooArgList(x), Roovar_dataTrans);
                RooDataHist mcComp("mcComp", "mcComp", RooArgList(x), Roovar_compTrans);
                RooDataHist mcPi0("mcPi0", "mcPi0", RooArgList(x), Roovar_pi0Trans);

                RooHistPdf pdf_data("pdf_data", "pdf_data", x, data);
                RooHistPdf pdf_mcComp("pdf_mcComp", "pdf_mcComp", x, mcComp);
                RooHistPdf pdf_mcPi0("pdf_mcPi0", "pdf_mcPi0", x, mcPi0);
                RooRealVar yieldComp("yieldComp", "yieldComp", 0, Roovar_dataTrans->Integral());
                RooRealVar yieldPi0("yieldPi0", "yieldPi0", 0, Roovar_dataTrans->Integral());
        
                RooAddPdf combine("combine", "combine", RooArgList(pdf_mcComp, pdf_mcPi0),  RooArgList(yieldComp, yieldPi0));

                combine.fitTo(data, Extended(kTRUE));

                RooPlot* fitframe = x.frame(0.003,0.02);

                data.plotOn(fitframe, RooFit::LineColor(kRed));

                combine.plotOn(fitframe, LineColor(kBlue));
                combine.paramOn(fitframe);
                
                //combine.plotOn(fitframe, DrawOption("F"), FillColor(kGreen));
                fitframe->Draw();               
                RooChi2Var chi2("chi2","chi2", combine, data) ;
                cout << chi2.getVal() << endl ;
                cout << "______________________________________________________________________"<<endl;
                
                int arr[14];
                arr[count] = chi2.getVal();
                
                //cout << arr[count] << endl;           
                cout << count << endl;
                cout << "_______________________________________________________________________________________________________________________________________________"<<endl;
                //chiHist->Fill(arr[count], (chi2.getVal()));
                                
}

//chiHist->Rebin2D(2,2);
//chiHist->Draw("colz");
#endif
//#if 0

 Roovar_dataTheta = Data_Theta[count];

                if(count==14){
                        Roovar_dataTheta = Roovar_dataTheta_Original;
                        }

                int maxBins = (Roovar_dataTheta->GetXaxis()->GetNbins())*(Roovar_dataTheta->GetYaxis()->GetNbins());

                for(int i=0; i< maxBins; i++){
                        if(Roovar_dataTheta->GetBinContent(i) < 0.001 ){
                                Roovar_dataTheta->SetBinContent(i,1/1.0E+45);}}

                for(int i=0; i< maxBins; i++) {
                        if(Roovar_compTheta->GetBinContent(i) < 0.001 ){
                                Roovar_compTheta->SetBinContent(i,1/1.0E+45);}}

                for(int i=0; i< maxBins; i++) {
                        if(Roovar_pi0Theta->GetBinContent(i) < 0.001){
                                Roovar_pi0Theta->SetBinContent(i,1/1.0E+45);}}

                RooRealVar x("x","x", 0, 0.003);

                RooDataHist data("data", "data", RooArgList(x), Roovar_dataTheta);
                RooDataHist mcComp("mcComp", "mcComp", RooArgList(x), Roovar_compTheta);
                RooDataHist mcPi0("mcPi0", "mcPi0", RooArgList(x), Roovar_pi0Theta);

                RooHistPdf pdf_data("pdf_data", "pdf_data", x, data);
                RooHistPdf pdf_mcComp("pdf_mcComp", "pdf_mcComp", x, mcComp);
                RooHistPdf pdf_mcPi0("pdf_mcPi0", "pdf_mcPi0", x, mcPi0);
                RooRealVar yieldComp("yieldComp", "yieldComp", 0, Roovar_dataTheta->Integral());
                RooRealVar yieldPi0("yieldPi0", "yieldPi0", 0, Roovar_dataTheta->Integral());

                RooAddPdf combine("combine", "combine", RooArgList(pdf_mcComp, pdf_mcPi0),  RooArgList(yieldComp, yieldPi0));

                combine.fitTo(data, Extended(kTRUE));

                RooPlot* fitframe = x.frame(0,0.003);

                data.plotOn(fitframe, RooFit::LineColor(kRed));

                combine.plotOn(fitframe, LineColor(kBlue));
                combine.paramOn(fitframe);

                fitframe->Draw();
                RooChi2Var chi2("chi2","chi2", combine, data) ;
                cout << chi2.getVal() << endl ;
                cout << "______________________________________________________________________"<<endl;

                //Double_t arr[14];
                arr[count] = chi2.getVal();

                //cout << arr[1] << endl;               
                cout << count << endl;
                cout << "_______________________________________________________________________________________________________________________________________________"<<endl;   
                //chiHist->Fill(z[count], (chi2.getVal())/10E48);
                //return arr[count];
        }
//#endif
//chiHist->Draw("colz");
//TCanvas *c1 = new TCanvas("c1","Chi2 Trans", 800, 400);       
//TH1F *h = new TH1F("h","test", 300, 0, 3.5, 200,0, 5);
//h->Fill(numb[6]);
#if 0
Int_t n= 14;
Double_t z[14] = {.80, .825, .85, .875, .90, .925, .95, .975, 1, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3};
Double_t b[14];// = {1.67526E46, 5.18741E45, 1.01704E46, 2.21752E46, 2.57152E47, 3.99014E47, 1.15662E48, 2.6104E48, 5.85024E48, 8.60066E48};



for (Int_t i=0; i<n; i++) {
        z[i];//, .925, .95, .975, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3};
        b[i] = arr[14];//, 5.18741E45, 1.01704E46, 2.21752E46, 2.57152E47, 3.99014E47, 1.15662E48, 2.6104E48, 5.85024E48, 8.60066E48, 6.0086E46};
}


TGraph* chi2Hist;
chi2Hist->SetPoint(n, z, b);
chi2Hist->Draw("AC*");
#endif





return;}
