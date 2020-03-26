#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"



void Sig_variable(){

//Set up input files
////------------------------------
TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/hist_sum_PARA_30320_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);

TString front_Trans = "SigTrans-vs-Variables/";
TString back_2var_Trans[28] = {"SigTrans_PhotonP", "SigTrans_PhotonTheta", "SigTrans_PhotonThetaDet", "SigTrans_ProtonP", "SigTrans_ProtonTheta", "SigTrans_ProtonThetaDet", "SigTrans_PhotonPhi", "SigTrans_PhotonBCALShowerZ", "SigTrans_ThetaCM", "SigTrans_DetlaTheta", "SigTrans_DeltaE", "SigTrans_DeltaPhi","SigTrans_PBCALPreShower", "SigTrans_PBCALSE", "SigTrans_PrBCALSE", "SigTrans_PFCALSE", "SigTrans_t", "SigTrans_s", "SigTrans_u", "SigTrans_MMS",  "SigTrans_ME",  "SigTrans_VertexZ",  "SigTrans_VertexR",  "SigTrans_dEdxCDC",  "SigTrans_dEdxFDC",  "SigTrans_EPreEShower"};

TString front_Theta = "SigTheta-vs-Variables/";
TString back_2var_Theta[28] = {"SigTheta_PhotonP", "SigTheta_PhotonTheta", "SigTheta_PhotonThetaDet", "SigTheta_ProtonP", "SigTheta_ProtonTheta", "SigTheta_ProtonThetaDet", "SigTheta_PhotonPhi", "SigTheta_PhotonBCALShowerZ", "SigTheta_ThetaCM", "SigTheta_DetlaTheta", "SigTheta_DeltaE", "SigTheta_DeltaPhi","SigTheta_PBCALPreShower", "SigTheta_PBCALSE", "SigTheta_PrBCALSE", "SigTheta_PFCALSE", "SigTheta_t", "SigTheta_s", "SigTheta_u", "SigTheta_MMS",  "SigTheta_ME",  "SigTheta_VertexZ",  "SigTheta_VertexR",  "SigTheta_dEdxCDC",  "SigTheta_dEdxFDC",  "SigTheta_EPreEShower"};

TString front_Long = "SigLong-vs-Variables/";
TString back_2var_Long[28] = {"SigLong_PhotonP", "SigLong_PhotonTheta", "SigLong_PhotonThetaDet", "SigLong_ProtonP", "SigLong_ProtonTheta", "SigLong_ProtonThetaDet", "SigLong_PhotonPhi", "SigLong_PhotonBCALShowerZ", "SigLong_ThetaCM", "SigLong_DetlaTheta", "SigLong_DeltaE", "SigLong_DeltaPhi","SigLong_PBCALPreShower", "SigLong_PBCALSE", "SigLong_PrBCALSE", "SigLong_PFCALSE", "SigLong_t", "SigLong_s", "SigLong_u", "SigLong_MMS",  "SigLong_ME",  "SigLong_VertexZ",  "SigLong_VertexR",  "SigLong_dEdxCDC",  "SigLong_dEdxFDC",  "SigLong_EPreEShower"};

/*
for(int i=0; i< 26; i++){
        TString Sig_Var = front_Trans + back_2var_Trans[i];
        

        TH2F* Sig_varComp = (TH2F*)comp->Get(Sig_Var);
        TH2F* Sig_varPi0 = (TH2F*)pi0->Get(Sig_Var);
        TH2F* Sig_varData = (TH2F*)Para->Get(Sig_Var);
        
        TCanvas* cc[i];
        cc[i]= new TCanvas(Sig_Var,Sig_Var,800,400);
        cc[i]->Divide(3,1);     
        cc[i]->cd(1);
        Sig_varData->Draw("colz");
        cc[i]->cd(2);
        Sig_varComp->Draw("colz");
        cc[i]->cd(3);
        Sig_varPi0->Draw("colz");

        cc[i]->Print(back_2var_Trans[i]+".png");
         }

*/
//________________________________________________________________________________________________

TString Hist_Less = "SigTrans-vs-Variables/SigTrans_PhotonThetaDet";
TString Hist_More = "SigTrans-vs-Variables/SigTrans PhotonThetaDet varyMore";

TString var[3] = {"PhotonThetaDet", "ME", "PBCALPreShower"};

TString SigTT = "SigTrans-vs-Variables/SigTrans_SigTheta_Normal";
TString SigTL = "SigTrans-vs-Variables/SigTrans_SigLong_Normal";

for(int i=0; i< 1; i++){
        TString Sig_Var_Less = Hist_Less;
        TString Sig_Var_More = Hist_More;
        cout << Sig_Var_Less;
        TH2F* Sig_varData_Less = (TH2F*)Para->Get(Sig_Var_Less);
        TH2F* Sig_varData_More = (TH2F*)Para->Get(Sig_Var_More);

        TH2F* Sig_varData_Normal = (TH2F*)Para->Get(SigTT);

        TCanvas* cc[i];
        cc[i]= new TCanvas("cc", "cc",800,400);
        cc[i]->Divide(3,1);
        cc[i]->cd(1);
        Sig_varData_Less->Draw("colz");
        cc[i]->cd(2);
        Sig_varData_More->Draw("colz");
        //cc[i]->cd(3);
        //Sig_varData_More->Draw("colz");

        cc[i]->Print("PhotonThetaDet.png");}


return;}
