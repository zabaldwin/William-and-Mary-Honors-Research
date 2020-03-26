#include <string>
#include <iostream>
using namespace std;

void fixingNewdata(){

        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10206);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_lowint.acc.root");

        TString Path4 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10005);
        TString Path5 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10206);
        TString Path6 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_total.acc.root");

        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_medint.acc.root");
        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_highint.acc.root");

        TFile *MCpath = TFile::Open(Path1);
        TFile *MC2path = TFile::Open(Path2);
        TFile *Totalpath = TFile::Open(Path3);

        TFile *TotalpathNew1 = TFile::Open(Path7);
        TFile *TotalpathNew2 = TFile::Open(Path8);

        TCanvas *cc = new TCanvas("cc","MM2 Pre", 800,400);
        TCanvas *z1 = new TCanvas("z1","ME Pre", 800,400);
        TCanvas *z2 = new TCanvas("z2","DeltaPhi Pre", 800,400);
        TCanvas *ccc = new TCanvas("ccc","MM2 1st", 800,400);
        TCanvas *cc2 = new TCanvas("cc2","ME 1st", 800,400);
        TCanvas *cc1 = new TCanvas("cc1","DeltaPhi 1st", 800,400);
        TCanvas *cc3 = new TCanvas("cc3","MM2 Init", 800,400);
        TCanvas *cc4 = new TCanvas("cc4","ME Final", 800,400);
        cc->Divide(3,2);
        z1->Divide(3,2);
        z2->Divide(3,2);
        ccc->Divide(3,2);
        cc1->Divide(3,2);
        cc2->Divide(3,2);
        cc3->Divide(3,2);
        cc4->Divide(3,2);

        TString histSigMMPre = "Histograms/Egamma5_6/MissingMassSquared_PreCutEgamma5_6";
        TString histSigMEPre = "Histograms/Egamma5_6/MissingEnergy_PreCutEgamma5_6";
        TString histSigDPPre = "Histograms/Egamma5_6/DeltaPhi_PreCutEgamma5_6";

        TString histSigMM1 = "Histograms/Egamma5_6/MissingMassSquared_1stCutEgamma5_6";
        TString histSigME1 = "Histograms/Egamma5_6/MissingEnergy_1stCutEgamma5_6";
        TString histSigDP1 = "Histograms/Egamma5_6/DeltaPhi_1stCutEgamma5_6";

        TString Acci_histSigAMMPre = "Histograms/Acci_Egamma5_6/Acci_MissingMassSquared_PreCutEgamma5_6";
        TString Acci_histSigAMEPre = "Histograms/Acci_Egamma5_6/Acci_MissingEnergy_PreCutEgamma5_6";
        TString Acci_histSigADPPre = "Histograms/Acci_Egamma5_6/Acci_DeltaPhi_PreCutEgamma5_6";

        TString Acci_histSigAMM1 = "Histograms/Acci_Egamma5_6/Acci_MissingMassSquared_1stCutEgamma5_6";
        TString Acci_histSigAME1 = "Histograms/Acci_Egamma5_6/Acci_MissingEnergy_1stCutEgamma5_6";
        TString Acci_histSigADP1 = "Histograms/Acci_Egamma5_6/Acci_DeltaPhi_1stCutEgamma5_6";

        TString histSigMMInit = "Histograms/Egamma5_6/MissingMassSquared_InitEgamma5_6";
        TString Acci_histSigMMInit = "Histograms/Acci_Egamma5_6/Acci_MissingMassSquared_InitEgamma5_6";

        TString histSigMEFinal = "Histograms/Egamma5_6/MissingEnergy_Final_Egamma5_6";
        TString Acci_histSigMEFinal = "Histograms/Acci_Egamma5_6/Acci_MissingEnergy_Final_Egamma5_6";
        //TH2F* h = (TH2F*)MCpath->Get(histSig);
        //TH2F* h1 = (TH2F*)MC2path->Get(histSig);

        TH2F* MMInit1 = (TH2F*)Totalpath->Get(histSigMMInit);
        TH2F* MMInit2 = (TH2F*)TotalpathNew1->Get(histSigMMInit);
        TH2F* MMInit3 = (TH2F*)TotalpathNew2->Get(histSigMMInit);

TH2F* MEFinal1 = (TH2F*)Totalpath->Get(histSigMEFinal);
        TH2F* MEFinal2 = (TH2F*)TotalpathNew1->Get(histSigMEFinal);
        TH2F* MEFinal3 = (TH2F*)TotalpathNew2->Get(histSigMEFinal);

        TH2F* MMInit_1 = (TH2F*)Totalpath->Get(Acci_histSigMMInit);
        TH2F* MMInit_2 = (TH2F*)TotalpathNew1->Get(Acci_histSigMMInit);
        TH2F* MMInit_3 = (TH2F*)TotalpathNew2->Get(Acci_histSigMMInit);

        TH2F* MEFinal_1 = (TH2F*)Totalpath->Get(Acci_histSigMEFinal);
        TH2F* MEFinal_2 = (TH2F*)TotalpathNew1->Get(Acci_histSigMEFinal);
        TH2F* MEFinal_3 = (TH2F*)TotalpathNew2->Get(Acci_histSigMEFinal);



        TH2F* h2 = (TH2F*)Totalpath->Get(histSigMMPre);
        TH2F* h22 = (TH2F*)TotalpathNew1->Get(histSigMMPre);
        TH2F* h222 = (TH2F*)TotalpathNew2->Get(histSigMMPre);

        TH2F* h3 = (TH2F*)Totalpath->Get(histSigMEPre);
        TH2F* h33 = (TH2F*)TotalpathNew1->Get(histSigMEPre);
        TH2F* h333 = (TH2F*)TotalpathNew2->Get(histSigMEPre);

        TH2F* h4 = (TH2F*)Totalpath->Get(histSigDPPre);
        TH2F* h44 = (TH2F*)TotalpathNew1->Get(histSigDPPre);
        TH2F* h444 = (TH2F*)TotalpathNew2->Get(histSigDPPre);

        TH2F* h_2 = (TH2F*)Totalpath->Get(Acci_histSigAMMPre);
        TH2F* h_22 = (TH2F*)TotalpathNew1->Get(Acci_histSigAMMPre);
        TH2F* h_222 = (TH2F*)TotalpathNew2->Get(Acci_histSigAMMPre);

        TH2F* h_3 = (TH2F*)Totalpath->Get(Acci_histSigAMEPre);
        TH2F* h_33 = (TH2F*)TotalpathNew1->Get(Acci_histSigAMEPre);
        TH2F* h_333 = (TH2F*)TotalpathNew2->Get(Acci_histSigAMEPre);

        TH2F* h_4 = (TH2F*)Totalpath->Get(Acci_histSigADPPre);
        TH2F* h_44 = (TH2F*)TotalpathNew1->Get(Acci_histSigADPPre);
        TH2F* h_444 = (TH2F*)TotalpathNew2->Get(Acci_histSigADPPre);
        
        TH2F* h5 = (TH2F*)Totalpath->Get(histSigMM1);
        TH2F* h55 = (TH2F*)TotalpathNew1->Get(histSigMM1);
        TH2F* h555 = (TH2F*)TotalpathNew2->Get(histSigMM1);

        TH2F* h8 = (TH2F*)Totalpath->Get(histSigME1);
        TH2F* h88 = (TH2F*)TotalpathNew1->Get(histSigME1);
        TH2F* h888 = (TH2F*)TotalpathNew2->Get(histSigME1);

        TH2F* h7 = (TH2F*)Totalpath->Get(histSigDP1);
        TH2F* h77 = (TH2F*)TotalpathNew1->Get(histSigDP1);
        TH2F* h777 = (TH2F*)TotalpathNew2->Get(histSigDP1);

        TH2F* h_5 = (TH2F*)Totalpath->Get(Acci_histSigAMM1);
        TH2F* h_55 = (TH2F*)TotalpathNew1->Get(Acci_histSigAMM1);
        TH2F* h_555 = (TH2F*)TotalpathNew2->Get(Acci_histSigAMM1);

        TH2F* h_8 = (TH2F*)Totalpath->Get(Acci_histSigAME1);
        TH2F* h_88 = (TH2F*)TotalpathNew1->Get(Acci_histSigAME1);
        TH2F* h_888 = (TH2F*)TotalpathNew2->Get(Acci_histSigAME1);

        TH2F* h_7 = (TH2F*)Totalpath->Get(Acci_histSigADP1);
        TH2F* h_77 = (TH2F*)TotalpathNew1->Get(Acci_histSigADP1);
        TH2F* h_777 = (TH2F*)TotalpathNew2->Get(Acci_histSigADP1);


        h2->Add(h_2,-0.25);
        h22->Add(h_22,-0.25);
        h222->Add(h_222,-0.25);

        //h3->Add(h_3,-0.25);
        //h33->Add(h_33,-0.25);
        //h333->Add(h_333,-0.25);

        //h4->Add(h_4,-0.25);
        //h44->Add(h_44,-0.25);
        //h444->Add(h_444,-0.25);
        
         h5->Add(h_5,-0.25);
        h55->Add(h_55,-0.25);
        h555->Add(h_555,-0.25);

        h8->Add(h_8,-0.25);
        h88->Add(h_88,-0.25);
        h888->Add(h_888,-0.25);

        h7->Add(h_7,-0.25);
        h77->Add(h_77,-0.25);
        h777->Add(h_777,-0.25);

        MMInit1->Add(MMInit_1,-0.25);
        MMInit2->Add(MMInit_2,-0.25);
        MMInit3->Add(MMInit_3,-0.25);

        MEFinal1->Add(MEFinal_1,-0.25);
        MEFinal2->Add(MEFinal_2,-0.25);
        MEFinal3->Add(MEFinal_3,-0.25);

        gStyle->SetOptFit();
        gStyle->SetOptStat();


        cc->cd(1);
        h2->Draw();
        cc->cd(2);
        h22->Draw();
        cc->cd(3);
        h222->Draw();
        cc->Print("MM2_PreCut.pdf");

        z1->cd(1);
        h3->Draw();
        z1->cd(2);
        h33->Draw();
        z1->cd(3);
        h333->Draw();
        z1->Print("ME_PreCut.pdf");
        
        z2->cd(1);
        h4->Draw();
        z2->cd(2);
        h44->Draw();
        z2->cd(3);
        h444->Draw();
        z2->Print("DPhi_PreCut.pdf");


        ccc->cd(1);
        h5->Draw();
        ccc->cd(2);
        h55->Draw();
        ccc->cd(3);
        h555->Draw();
        ccc->Print("MM2_1stCut.pdf");

        cc1->cd(1);
        h8->Draw();
        cc1->cd(2);
        h88->Draw();
        cc1->cd(3);
        h888->Draw();
        cc1->Print("ME_1stCut.pdf");

        cc2->cd(1);
        h7->Draw();
        cc2->cd(2);
        h77->Draw();
        cc2->cd(3);
        h777->Draw();
        cc2->Print("DPhi_1stCut.pdf");
        
        cc3->cd(1);
        MMInit1->Draw();
        cc3->cd(2);
        MMInit2->Draw();
        cc3->cd(3);
        MMInit3->Draw();
        cc3->Print("MMInit.pdf");

        cc3->cd(1);
        MEFinal1->Draw();
        cc3->cd(2);
        MEFinal2->Draw();
        cc3->cd(3);
        MEFinal3->Draw();
        cc3->Print("MMInit.pdf");
        //Monte Carlo??
        return;}
