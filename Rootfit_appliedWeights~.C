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


TString C_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/Oct1/hist_compton_30001.acc.root";
TString P0_pathWay = "/sciclone/data10/zabaldwin/tree_g_Merged/Oct1/hist_compton_30002.acc.root";
TString D_pathWay = "/sciclone/data10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

int i = 0;
int j = 1;
int k = 2;
int l = 3;
int m = 4;
int n = 5;

TString front = "ComptonPurity/";

TString back_2varComp[3] = {"SigTrans_SigTheta_DPlessThan_B_SignalCutComp","SigLong_SigTrans_DPlessThan_B_SignalCutComp","SigLong_SigTheta_DPlessThan_B_SignalCutComp"};
TString back_2varPi0[3] = {"SigTrans_SigTheta_DPlessThan_B_SignalCutPi0","SigLong_SigTrans_DPlessThan_B_SignalCutPi0","SigLong_SigTheta_DPlessThan_B_SignalCutPi0"};

SigTrans_SigTheta_Comp = front + back_2varComp[i];
SigLong_SigTrans_Comp = front + back_2varComp[j];
SigLong_SigTheta_Comp = front + back_2varComp[k];

SigTrans_SigTheta_Pi0 = front + back_2varPi0[i];
SigLong_SigTrans_Pi0 = front + back_2varPi0[j];
SigLong_SigTheta_Pi0 = front + back_2varPi0[k];

TH2F* Roovar_data_twoVar = (TH2F*)Para->Get(SigLong_SigTrans_Comp);
TH2F* Roovar_comp_twoVar = (TH2F*)comp->Get(SigLong_SigTrans_Comp);
TH2F* Roovar_pi0_twoVar = (TH2F*)pi0->Get(SigLong_SigTrans_Comp);

//Roovar_data_twoVar->SetAxisRange(0, 0.015);
// For Long
Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.5); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(10.0);
//Int_t binx1 = Roovar_data_twoVar->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_data_twoVar->GetXaxis()->FindBin(0.015);
// For Long/Theta
//Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.0005); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.005); 
Int_t biny1 = Roovar_data_twoVar->GetYaxis()->FindBin(0.002); Int_t biny2 = Roovar_data_twoVar->GetYaxis()->FindBin(0.02);


Float_t entries_Comp = Roovar_comp_twoVar->Integral(binx1, binx2, biny1, biny2); //4227.0; 
Float_t entries_Pi0 = Roovar_pi0_twoVar->Integral(binx1, binx2, biny1, biny2); //69605.0;

Float_t scaleComp = 1.71388E3/entries_Comp;
Float_t scalePi0 = 7.6134E1/entries_Pi0;

cout << Roovar_pi0_twoVar->Integral() << endl;
cout << Roovar_comp_twoVar->Integral() << endl;

TH2F *Roovar_comp_twoVarFin = (TH2F*)Roovar_comp_twoVar->Clone("Roovar_comp_twoVarFin");
Roovar_comp_twoVarFin->Scale(scaleComp);

TH2F *Roovar_pi0_twoVarFin = (TH2F*)Roovar_pi0_twoVar->Clone("Roovar_pi0_twoVarFin");
Roovar_pi0_twoVarFin->Scale(scalePi0);

cout << Roovar_pi0_twoVarFin->Integral() << endl;
cout << Roovar_comp_twoVarFin->Integral() << endl;

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

TCanvas *ccc = new TCanvas("ccc", "ccc", 800, 400);
ccc->Divide(3,1);
ccc->cd(1);
//Roovar_data_twoVar->GetXaxis()->SetRange(0,0.015);
Roovar_data_twoVar->Draw("colz");
ccc->cd(2);
TH2F* histAdd = (TH2F*)Roovar_comp_twoVarFin->Clone("histAdd");
histAdd->Add(Roovar_pi0_twoVarFin);
histAdd->Draw("colz");
ccc->cd(3);
TH2F* histSub = (TH2F*)Roovar_comp_twoVarFin->Clone("histSub");
histSub->Add(Roovar_pi0_twoVarFin,-1);
histSub->SetMinimum(0.01);
histSub->Draw("colz");

TCanvas *cccc = new TCanvas("cccc", "cccc", 800, 400);
cccc->Divide(2,1);
cccc->cd(2);
TH2F* histResidual = (TH2F*)Roovar_data_twoVar->Clone("histResidual");
int maxBins = (Roovar_data_twoVar->GetXaxis()->GetNbins())*(Roovar_data_twoVar->GetYaxis()->GetNbins());
histResidual->Reset();
for(i=0; i<maxBins; i++){
        Double_t res = (Roovar_comp_twoVar->GetBinContent(i) - histAdd->GetBinContent(i))/ sqrt(Roovar_data_twoVar->GetBinContent(i));
        histResidual->SetBinContent(i,res);}

histResidual->Rebin2D(1,2);
histResidual->SetMinimum(0.4);
histResidual->Draw("colz");

//TRatioPlot* rp1 = new TRatioPlot(Roovar_data_twoVar, histAdd);
//rp1->Draw();


}
