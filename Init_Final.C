#include <string>
#include <iostream>
using namespace std;


void Init_Final(){
        //Remember to write the Hist_Total later



        TString Path1 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path4 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);

        TFile *MCPath = TFile::Open(Path2);
        TFile *MCPath2 = TFile::Open(Path4);
        TFile *RegPath = TFile::Open(Path1);
        TFile *TotalPath = TFile::Open(Path3);

        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        string input;
        cout << "Which Histogram do you want to access (write similialy to 'ProtonP_Theta_Init'):\n"
;
        getline(cin, input);

        string input2;
        cout << "Write for the final (ie. 'ProtonP_Theta_Final_'):\n"
;
        getline(cin, input2);

        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        TString hist = "Histograms/";
        hist += bin;;
        hist += "/";
        hist += input;
        hist += bin;;
        
        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += input2;
        hist2 += bin;

        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += input;
        Acci += bin;

        TString Acc2 = "Acci_";
        TString Acci2 = "Histograms/";
        Acci2 += Acc2;
        Acci2 += bin;
        Acci2 += "/";
        Acci2 += Acc2;
        Acci2 += input2;
        Acci2 += bin;

        //string input3;
        //cout << "Since I have made new Init and Final versions, there are different Monte Carlo simulation names. Type in the correct name (i.e. 'VertexZ'):\n";
        //cin >> input3;

        TString MC = "Histograms/";
        MC += bin;
        MC += "/";
        MC += input2;
        MC += bin;

        TString MC2 = "Histograms/";
        MC2 += bin;
        MC2 += "/";
        MC2 += input2;
        MC2 += bin;
        
        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        TH2F* h = (TH2F*)RegPath->Get(hist);
        TH2F* h1 = (TH2F*)RegPath->Get(hist2);
        TH2F* h2 = (TH2F*)TotalPath->Get(hist);
        TH2F* h5 = (TH2F*)MCPath->Get(MC);
        TH2F* h6 = (TH2F*)MCPath2->Get(MC2);

        TH2F* h3 = (TH2F*)RegPath->Get(Acci);
        TH2F* h4 = (TH2F*)RegPath->Get(Acci2);

        if(yes=="yes"){
        //h->Add(h3,-0.25);
        h1->Add(h4,-0.25);}

        TString name = "Monte Carlo (10005)\n";
        //name += input2;

        TString name2 = "Monte Carlo(10105)\n";
        //name2 += input2;


cc->Divide(2,3);

        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc->cd(1);
        h->Draw("colz");
        cc->cd(2);
        h1->SetMinimum(0);
        h1->Draw("colz");
        cc->cd(3);
        h5->SetName(name);
        h5->Draw("colz");
        cc->cd(4);
        h6->SetName(name2);
        h6->Draw("colz");
        return;}
