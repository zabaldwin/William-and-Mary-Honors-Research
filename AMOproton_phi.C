#include <string>
#include <iostream>
using namespace std;

void AMOproton_phi(){


        string input;
        cout << "Do you want to access MonteCarlo run# 30497PERP?\n"
;
        getline(cin, input);
        if(input=="no"){
                string input2;
                cout << "Which real data intensity do you want to access? (high,med,low)\n"
;
                //when adding the phase shift in AMO (3.14159/4.) it seems like it doesnt need anything

                getline(cin, input2);
                if(input2=="med"){
                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_AMO_30274_30788.root");
                        TString dataName = "Other Histograms/Proton_Phi11";
                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                        TFile *AMOdata = TFile::Open(Path8);
                        TH1D* dataAMO = (TH1D*)AMOdata->Get(dataName);
                        
                        TF1 *fAMO = new TF1("Phi_ProtonAMO", "[0]*(1+[1]*cos(2*((x*3.14159/180.))))",-180, 180);
                        dataAMO->Fit(fAMO, "","");
                        gStyle->SetOptStat();
                        fAMO->Draw("SAME");}
                if(input2=="high"){
                        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_AMO_30796_31056.root");
                        TString dataName = "Other Histograms/Proton_Phi11";
                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                        TFile *AMOdata = TFile::Open(Path7);
                        TH1D* dataAMO = (TH1D*)AMOdata->Get(dataName);

                        TF1 *fAMO = new TF1("Phi_ProtonAMO", "[0]*(1+[1]*cos(2*(x*(3.14159/180.))))",-180, 180);
                        dataAMO->Fit(fAMO, "","");
                        gStyle->SetOptStat();
                        fAMO->Draw("SAME");}
                if(input2=="low"){
                        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_sum_AMO_11366_11555.root");
                        TString dataName = "Other Histograms/Proton_Phi11";
                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                        TFile *AMOdata = TFile::Open(Path3);
                        TH1D* dataAMO = (TH1D*)AMOdata->Get(dataName);

                        TF1 *fAMO = new TF1("Phi_ProtonAMO", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                        dataAMO->Fit(fAMO, "","");
                        gStyle->SetOptStat();
                        fAMO->Draw("SAME");}}
        else{
                cout << "There is no Monte Carlo simulation for AMO";
/*
        TString Path9 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%dPARA.acc.root", 30497);
        TString dataName = "Other Histograms/Proton_Phi";

        TFile *AMOdata = TFile::Open(Path9);
//      TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
        TH1D* dataPerp = (TH1D*)AMOdata->Get(dataName);

        // TCanvas *c1 = new TCanvas("c1","Phi vs Proton AMO", 800,400);
        //cc->Divide(3,2);
        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        //                //dataPara->Fit(fPARA, "","");
        //                        //cc->cd(1);
        gStyle->SetOptStat();
        //                                       // fPARA->Draw("SAME");
        //                                               //Double_t param[2];
        //                                                       //fPARA->GetParameters(param);
        TF1 *fAMO = new TF1("Phi_ProtonAMO", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        dataPerp->Fit(fAMO, "","");
        //                                                                               //c1->Divide(2,1);
        //                                                                                       //cc->cd(2);
        //                                                                                               //fPARA->Draw("SAME");
        fAMO->Draw("SAME");}




*/
return;}}
