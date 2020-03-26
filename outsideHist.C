#include <string>
#include <iostream>
using namespace std;

void outsideHist(){

        TString Path1 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11555);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path4 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);

        TFile *MCPath = TFile::Open(Path2);
        TFile *MCPath2 = TFile::Open(Path4);
        TFile *RegPath = TFile::Open(Path1);
        TFile *TotalPath = TFile::Open(Path3);

        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        string input;
        cout << "Which Histogram do you want to access outside the Egamma directories (write similialy to 'BeamEnergy'):\n"
;
        getline(cin, input);


        TString name = "Histograms/";
        name += input;


        TH2F* h1 = (TH2F*)RegPath->Get(name);
        //TH2F* h2 = (TH2F*)TotalPath->Get(hist);
        TH2F* h5 = (TH2F*)MCPath->Get(name);

        cc->Divide(2,1);
        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc->cd(1);
        h5->Draw("colz");
        cc->cd(2);
        h1->Draw("colz");
        return;}
