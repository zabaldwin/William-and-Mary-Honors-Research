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


void Rootfit_appliedWeights(){


TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/hist_sum_PARA_30320_31057.root";
TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TFile *comp_file = TFile::Open(C_pathWay);
TFile *pi0_file = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

int a = 0;
int j = 1;
int k = 2;
         
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

TString hist = "SigTrans-vs-Variables/";
      
TString deltaPhi = "DeltaPhi_t";

dPhi_t = hist + deltaPhi; 
    
Roovar_data_twoVar = (TH2F*)Para->Get(dPhi_t);
Roovar_comp_twoVar = (TH2F*)comp_file->Get(dPhi_t);
Roovar_pi0_twoVar = (TH2F*)pi0_file->Get(dPhi_t);

//Roovar_data_twoVar->GetXaxis()->SetRangeUser(0.0,0.015);

//Roovar_data_twoVar->SetAxisRange(0, 0.015);
// For Long
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.5); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(10.0); 
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(0.015);
// For Long/Theta
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.0005); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.005); 
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.002); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);







/*_______________________________________________________________________________________________________________________________________________________________________________________________________*/
//Phi
Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(170); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(190);
//t
Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(5.0);


Float_t entries_Comp = Roovar_comp_twoVar->Integral(binx1, binx2, biny1, biny2); //4227.0; 
Float_t entries_Pi0 = Roovar_pi0_twoVar->Integral(binx1, binx2, biny1, biny2); //69605.0;



Float_t scaleComp =   8.34897E03/entries_Comp;
Float_t scalePi0 =  9.00269E-11/entries_Pi0;


TH2F *Roovar_comp_twoVarFin = (TH2F*)Roovar_comp_twoVar->Clone("Roovar_comp_twoVarFin");
Roovar_comp_twoVarFin->Scale(scaleComp);

TH2F *Roovar_pi0_twoVarFin = (TH2F*)Roovar_pi0_twoVar->Clone("Roovar_pi0_twoVarFin");
Roovar_pi0_twoVarFin->Scale(scalePi0);

#if 0
TCanvas *c = new TCanvas("c","c", 800, 400);
c->Divide(3,1);
c->cd(1);
Roovar_data_twoVar->Draw("colz");
c->cd(2);
Roovar_comp_twoVar->Draw("colz");
c->cd(3);
Roovar_pi0_twoVar->Draw("colz");

TCanvas *cc = new TCanvas("cc", "cc", 800, 400);
cc->Divide(2,3);
//cc->cd(1);
//Roovar_data_twoVar->Draw("colz");
cc->cd(3);
Roovar_comp_twoVar->Draw("colz");
cc->cd(4);
Roovar_comp_twoVarFin->Draw("colz");
cc->cd(5);
Roovar_pi0_twoVar->Draw("colz");
cc->cd(6);
Roovar_pi0_twoVarFin->Draw("colz");
//cc->cd(2);

//TH2F* histAdd = (TH2F*)Roovar_comp_twoVarFin->Clone("histAdd");
//histAdd->Add(Roovar_pi0_twoVarFin);
//histAdd->Draw("colz");
#endif
TCanvas *ccc = new TCanvas("ccc", "ccc", 800, 400);
ccc->Divide(4,1);
ccc->cd(2);
TH2F* histAdd = (TH2F*)Roovar_comp_twoVarFin->Clone("histAdd");
histAdd->Reset();
histAdd->Add(Roovar_pi0_twoVarFin);
//histAdd->GetXaxis()->SetRangeUser(0.0,0.003);
//histAdd->GetYaxis()->SetRangeUser(0.0,0.02);

//histAdd->Rebin2D(5,5);
// Trans/Theta
//histAdd->GetXaxis()->SetRangeUser(0.0,0.006);
//histAdd->GetYaxis()->SetRangeUser(0.004,0.01);
//Long/Trans
//histAdd->GetXaxis()->SetRangeUser(1.0,6.0);
//histAdd->GetYaxis()->SetRangeUser(0.004,0.008);
//Long/Theta
//histAdd->GetXaxis()->SetRangeUser(1.0,7.0);
//histAdd->GetYaxis()->SetRangeUser(0.0006,0.0015);
gStyle->SetOptStat(0);
histAdd->Draw("colz");

ccc->cd(3);
TH2F* histResidual = (TH2F*)Roovar_data_twoVar->Clone("histResidual");
int maxBins = (Roovar_data_twoVar->GetXaxis()->GetNbins())*(Roovar_data_twoVar->GetYaxis()->GetNbins());
histResidual->Reset();
//Roovar_data_twoVar->GetXaxis()->SetRangeUser(0.0,0.015);
//histResidual->GetXaxis()->SetRangeUser(0.0,0.015);
for(i=0; i<maxBins; i++){
        if(Roovar_data_twoVar->GetBinContent(i) == 0)
                continue;

        Double_t res = (Roovar_data_twoVar->GetBinContent(i) - histAdd->GetBinContent(i))/ sqrt(Roovar_data_twoVar->GetBinContent(i));
        histResidual->SetBinContent(i,res);}

//histResidual->GetXaxis()->SetRangeUser(0.0,0.003);
//histResidual->GetYaxis()->SetRangeUser(0.0,0.02);       
//histResidual->Rebin2D(5,5);
// Trans/Theta
//histResidual->GetXaxis()->SetRangeUser(0.0,0.006);
//histResidual->GetYaxis()->SetRangeUser(0.004,0.01);
// Long/Trans
//histResidual->GetXaxis()->SetRangeUser(1.0,6.0);
//histResidual->GetYaxis()->SetRangeUser(0.004,0.008);
//Long/Theta
//histResidual->GetXaxis()->SetRangeUser(1.0,7.0);
//histResidual->GetYaxis()->SetRangeUser(0.0006,0.0015);
gStyle->SetOptStat(0);
histResidual->Draw("colz");

ccc->cd(1);
//Roovar_data_twoVar->Reset();
//Roovar_data_twoVar->GetXaxis()->SetRangeUser(0.0,0.003);
//Roovar_data_twoVar->GetYaxis()->SetRangeUser(0.0,0.02);

//Roovar_data_twoVar->Rebin2D(5,5);
//Trans/Theta
//Roovar_data_twoVar->GetXaxis()->SetRangeUser(0.0,0.006);
//Roovar_data_twoVar->GetYaxis()->SetRangeUser(0.004,0.01);
//Long/Trans
//Roovar_data_twoVar->GetXaxis()->SetRangeUser(1.0,6.0);
//Roovar_data_twoVar->GetYaxis()->SetRangeUser(0.004,0.008);
//Long/Theta
//Roovar_data_twoVar->GetXaxis()->SetRangeUser(1.0,7.0);
//Roovar_data_twoVar->GetYaxis()->SetRangeUser(0.0006,0.0015);

gStyle->SetOptStat(0);
Roovar_data_twoVar->Draw("colz");
#if 0
ccc->cd(2);
TH2F* histAdd = (TH2F*)Roovar_comp_twoVarFin->Clone("histAdd");

histAdd->Add(Roovar_pi0_twoVarFin);
histAdd->Rebin2D(5,5);
histAdd->GetXaxis()->SetRangeUser(0.0,0.004);
histAdd->GetYaxis()->SetRangeUser(0.004,0.008);
histAdd->Draw("colz");
#endif

#if 0
ccc->cd(4);
TH2F* histSub = (TH2F*)Roovar_data_twoVar->Clone("histSub");
histSub->Add(histAdd,-1);
//histSub->Rebin2D(5,5);
gStyle->SetOptStat(0);
//Trans/Theta
histSub->GetXaxis()->SetRangeUser(0.0,0.006);
histSub->GetYaxis()->SetRangeUser(0.004,0.01);
//Long/Theta
//histSub->GetXaxis()->SetRangeUser(1.0,6.0);
//histSub->GetYaxis()->SetRangeUser(0.004,0.008);
//histSub->GetXaxis()->SetRangeUser(1.0,7.0);
//histSub->GetYaxis()->SetRangeUser(0.0006,0.0015);
//histSub->SetMinimum(0.01);
//histSub->Draw("colz");
#endif
//TCanvas *cccc = new TCanvas("cccc", "cccc", 800, 400);
//cccc->Divide(2,1);
#if 0
ccc->cd(4);
TH2F* histResidual = (TH2F*)Roovar_data_twoVar->Clone("histResidual");
int maxBins = (Roovar_data_twoVar->GetXaxis()->GetNbins())*(Roovar_data_twoVar->GetYaxis()->GetNbins());
histResidual->Reset();
for(i=0; i<maxBins; i++){
        if(Roovar_comp_twoVar->GetBinContent(i) == 0)
                continue;

        Double_t res = (Roovar_comp_twoVar->GetBinContent(i) - histAdd->GetBinContent(i))/ sqrt(Roovar_data_twoVar->GetBinContent(i));
        histResidual->SetBinContent(i,res);}

//histResidual->Rebin2D(5,5);
//histResidual->SetMinimum(0.1);
//histResidual->GetXaxis()->SetRangeUser(0.0,0.004);
//histResidual->GetYaxis()->SetRangeUser(0.004,0.008);
histResidual->Draw("colz");
#endif

//TRatioPlot* rp1 = new TRatioPlot(Roovar_data_twoVar, histAdd);
//rp1->Draw();

TCanvas *c = new TCanvas("c", "c", 800, 400);
c->Divide(3,1);

c->cd(1);
Roovar_data_twoVar->Draw("colz");
c->cd(2);
//Roovar_comp_twoVar->GetXaxis()->SetRangeUser(0.0,0.003);
//Roovar_comp_twoVar->GetYaxis()->SetRangeUser(0.0,0.02);
//Roovar_comp_twoVar->Draw("colz");
c->cd(3);
//Roovar_pi0_twoVar->GetXaxis()->SetRangeUser(0.0,0.003);
//Roovar_pi0_twoVar->GetYaxis()->SetRangeUser(0.0,0.02);
Roovar_pi0_twoVar->Draw("colz");
#if 0
TCanvas *bc = new TCanvas("bc", "bc", 800, 400);
bc->Divide(3,1);

TString variable[4] = {"EPreEShower_PhotonThetaDet", "EPreShower_PhotonThetaDet"};

EPreShower_PTD = front + variable[1];
EPreEShower_PTD = front + variable[0];

data_ = (TH2F*)Para->Get(EPreEShower_PTD);
comp_ = (TH2F*)comp->Get(EPreEShower_PTD);
pi0_ = (TH2F*)pi0->Get(EPreEShower_PTD);

bc->cd(1);
data_->GetXaxis()->SetRangeUser(0.0,1);
data_->Draw("colz");
bc->cd(2);
comp_->GetXaxis()->SetRangeUser(0.0,1);
comp_->Draw("colz");
bc->cd(3);
pi0_->GetXaxis()->SetRangeUser(0.0,1);
pi0_->Draw("colz");
#endif}
