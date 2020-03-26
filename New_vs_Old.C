#include <string>
#include <iostream>
using namespace std;

void New_vs_Old(){
        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10206);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");

        TString Path4 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10005);
        TString Path5 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10206);
        //TString Path6 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_total.acc.root");

        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_medint.acc.root");
        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_highint.acc.root");

        TFile *MCpath = TFile::Open(Path1);
        TFile *MC2path = TFile::Open(Path2);
        TFile *Totalpath = TFile::Open(Path3);

        //TFile *MCpathNew = TFile::Open(Path4);
       // TFile *MC2pathNew = TFile::Open(Path5);
        TFile *TotalpathNew1 = TFile::Open(Path7);
        TFile *TotalpathNew2 = TFile::Open(Path8);

        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        //TString Sig[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

        string input;
        cout << "Which Histogram do you want to access (write similialy to 'SigTrans_SigLong_'):\n"
;
getline(cin, input);
        cc->Divide(3,2);
                TString histSig = "Histograms/";
                histSig += "Egamma5_6";
                histSig += "/";
                histSig += input;
                histSig += "Egamma5_6";

                TString Acc = "Acci_";
                TString AcciSig = "Histograms/";
                AcciSig += Acc;
                AcciSig += "Egamma5_6";
                AcciSig += "/";
                AcciSig += Acc;
                AcciSig += input;
                AcciSig += "Egamma5_6";

                TH2F* h = (TH2F*)MCpath->Get(histSig);
                TH2F* h1 = (TH2F*)MC2path->Get(histSig);
                TH2F* h2 = (TH2F*)Totalpath->Get(histSig);
                TH2F* h3 = (TH2F*)TotalpathNew1->Get(histSig);
                TH2F* h6 = (TH2F*)TotalpathNew2->Get(histSig);

                TH2F* h4 = (TH2F*)Totalpath->Get(AcciSig);
                TH2F* h5 = (TH2F*)TotalpathNew1->Get(AcciSig);
                TH2F* h7 = (TH2F*)TotalpathNew2->Get(AcciSig);

                h2->Add(h4,-0.25);
                h3->Add(h5,-0.25);
                h6->Add(h7,-0.25);

                gStyle->SetOptFit();
                gStyle->SetOptStat();
                 cc->cd(1);
                gPad->SetLogx();
                h2->SetMinimum(0);
                //h2->GetXaxis()->SetTitle("Proton Theta");
                //h2->GetYaxis()->SetTitle("Proton Momenetum");
                h2->Draw("box colz");
                cc->cd(2);
                gPad->SetLogx();
                h3->SetMinimum(0);
                h3->Draw("box colz");
                cc->cd(3);
                gPad->SetLogx();
                h6->SetMinimum(0);
                h6->Draw("box colz");
                cc->cd(4);
                gPad->SetLogx();
                h->SetMinimum(0);
                h->Draw("box colz");
                cc->cd(5);
                gPad->SetLogx();
                h1->SetMinimum(0);
                h1->Draw("box colz");
                TString in = input;
                cc->Print(in+"_Logx.pdf");


        return;
}
