#include <string>
#include <iostream>
using namespace std;

void MonteCarlo(){


        int input;
        cout << "Which Monte Carlo run number do you want to access (10005/6,10105/6,10205/6):\n";
        cin >> input;
        TString Path = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", input);

        /*string decision;
        cout << "Do you want to look are the data of all the histograms (all) or an individual run number(ind)?\n";
        if(decision=="all"){
                TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
                TFile *TotalPath= TFile::Open(Path3);}
        else if(decision=="ind"){
                int input2;
                cout << "Which Histogram run number do you want to access (11366-11555):\n";
                cin >> input2;
                TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", input2);
                TFile *RegPath= TFile::Open(Path2);}*/
        TFile *MCPath= TFile::Open(Path);
        //TFile *RegPath= TFile::Open(Path2);
        //TFile *TotalPath= TFile::Open(Path3);
        TCanvas *cc = new TCanvas("cc", "Monte Carlo",800, 400);

        string  decision;
        cout << "Do you want to look at the data of the total histograms (tot) or an individual run number(ind)?\n";
        cin >> decision;
        if(decision=="tot"){
                TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
                TFile *TotalPath= TFile::Open(Path3);
                TString Eg[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

                string input3;
                cout << "Which Histogram do you want to access (write similialy to 'SigTrans_SigLong_'):\n"
;
                cin >> input3;
                cc->Divide(2,1);
                for(int i=0;i<5;i++){
                        TString hist = "Histograms/";
                        hist += Eg[i];
                        hist += "/";
                        hist += input3;
                        hist += Eg[i];

                        TString Acc = "Acci_";
                        TString Acci = "Histograms/";
                        Acci += Acc;
                        Acci += Eg[i];
                        Acci += "/";
                        Acci += Acc;
                        Acci += input3;
                        Acci += Eg[i];

                        TH2F* h = (TH2F*)MCPath->Get(hist);
                        TH2F* h1 = (TH2F*)TotalPath->Get(hist);

                        TH2F* h2 = (TH2F*)MCPath->Get(Acci);
                        TH2F* h3 = (TH2F*)TotalPath->Get(Acci);

                        h->Add(h2,-0.25);
                        h1->Add(h3,-0.25);

                        gStyle->SetOptFit();
                        cc->cd(1);
                        h->Draw("box color");
                        cc->cd(2);
                        h1->Draw("box colz");}}

        else{
int input4;
                cout << "Which Histogram run number do you want to access (11366-11555):\n";
                cin >> input4;
                TString Path2 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", input4);
                TFile *RegPath2= TFile::Open(Path2);
                TString Eg[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

                string input5;
                cout << "Which Histogram do you want to access (write similialy to 'SigTrans_SigLong_'):\n"
;
                cin >> input5;
                /*if(input5=="BeamEnergy"){
                        cc->Divide(2,1);
                        for(int i=0;i<5;i++){
                                TString hist2 = "Histograms/";
                                hist2 += input5;


                                TH2F* f = (TH2F*)MCPath->Get(hist2);
                                TH2F* f1 = (TH2F*)RegPath2->Get(hist2);

                                gStyle->SetOptFit();
                                gStyle->SetOptStat();
                                cc->cd(1);
                                f->Draw("box color");
                                cc->cd(2);
                                f1->Draw("box colz");}
                */cc->Divide(2,1);
                if(input5!="BeamEnergy"){
                for(int i=0;i<5;i++){
                        TString hist2 = "Histograms/";
                        hist2 += Eg[i];
                        hist2 += "/";
                        hist2 += input5;
                        hist2 += Eg[i];
                         TString Acc = "Acci_";
                        TString Acci2 = "Histograms/";
                        Acci2 += Acc;
                        Acci2 += Eg[i];
                        Acci2 += "/";
                        Acci2 += Acc;
                        Acci2 += input5;
                        Acci2 += Eg[i];

                        TH2F* f = (TH2F*)MCPath->Get(hist2);
                        TH2F* f1 = (TH2F*)RegPath2->Get(hist2);

                        TH2F* f2 = (TH2F*)MCPath->Get(Acci2);
                        TH2F* f3 = (TH2F*)RegPath2->Get(Acci2);

                        //f->Add(f2,-0.25);
                        //f1->Add(f3,-0.25);
                        gStyle->SetOptStat();
                        gStyle->SetOptFit();
                        cc->cd(1);
                        f->Draw("box color");
                        cc->cd(2);
                        f1->Draw("box colz");}}
        return;

}}
