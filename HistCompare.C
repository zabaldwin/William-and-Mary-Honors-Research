#include <string>
#include <iostream>
using namespace std;

void HistCompare(){
        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10206);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *MCpath = TFile::Open(Path1);
        TFile *MC2path = TFile::Open(Path2);
        TFile *Totalpath = TFile::Open(Path3);

        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);



        TString Sig[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

        string input;
        cout << "Which Histogram do you want to access (write similialy to 'SigTrans_SigLong_'):\n"
;
        getline(cin, input);
        
        int count=0;
        cc->Divide(3,4);
        for(int i=0;i<5;i++){
                TString histSig = "Histograms/";
                histSig += Sig[i];
                histSig += "/";
                histSig += input;
                histSig += Sig[i];

                TString Acc = "Acci_"; 
                TString AcciSig = "Histograms/";
                AcciSig += Acc;
                AcciSig += Sig[i];
                AcciSig += "/";
                AcciSig += Acc; 
                AcciSig += input;
                AcciSig += Sig[i];
                TH2F* h = (TH2F*)MCpath->Get(histSig);
                TH2F* h1 = (TH2F*)MC2path->Get(histSig);
                TH2F* h2 = (TH2F*)Totalpath->Get(histSig);

                TH2F* h3 = (TH2F*)MCpath->Get(AcciSig);
                TH2F* h4 = (TH2F*)MC2path->Get(AcciSig);

                h->Add(h3,-0.25);
                h1->Add(h4,-0.25);

                gStyle->SetOptFit();
                if (count==0){
                cc->cd(1);
                h->Draw("box colz");
                cc->cd(2);
                h1->Draw("box colz");
                cc->cd(3);
                h2->Draw("box colz");}
                else if(count==1){
                cc->cd(4);
                h->Draw("box colz");
                cc->cd(5);
                h1->Draw("box colz");
                cc->cd(6);
                h2->Draw("box colz");}
                else if(count==2){
                cc->cd(7);
                h->Draw("box colz");
                cc->cd(8);
                h1->Draw("box colz");
                cc->cd(9);
                h2->Draw("box colz");}
                else if(count==3){
                cc->cd(10);
                h->Draw("box colz");
                cc->cd(11);
                h1->Draw("box colz");
                cc->cd(12);
                h2->Draw("box colz");}
                else if(count==4){
                cc->cd(13);
                h->Draw("box colz");
                cc->cd(14);
                h1->Draw("box colz");
                cc->cd(15);
                h2->Draw("box colz");}
                count++;}

        return;}
