void ShowAccid(){

        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 11481);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TFile *RegPath = TFile::Open(Path1);
        TFile *MCPath = TFile::Open(Path2);
        TCanvas *cc = new TCanvas("cc","Showing Cuts", 800,400);
        TCanvas *c1 = new TCanvas("c1","Showing Final Cuts", 800,400);

        TString hist = "Histograms/Egamma5_6/ProtonP_Theta_InitEgamma5_6";
        TString hist2 = "Histograms/Egamma5_6/ProtonP_Theta_Final2_Egamma5_6";
        TString hist3 = "Histograms/Egamma5_6/ProtonP_Theta_Final3_Egamma5_6";
        TString hist4 = "Histograms/Egamma5_6/ProtonP_Theta_Final4_Egamma5_6";
        TString hist5 = "Histograms/Egamma5_6/ProtonP_Theta_Final5_Egamma5_6";
        TString hist6 = "Histograms/Egamma5_6/ProtonP_Theta_Final6_Egamma5_6";
        TString hist7 = "Histograms/Egamma5_6/ProtonP_Theta_Final_Egamma5_6";

        TString Acci = "Histograms/Acci_Egamma5_6/Acci_ProtonP_Theta_Final_Egamma5_6";

        TH2F* h = (TH2F*)RegPath->Get(hist);
        TH2F* h1 = (TH2F*)RegPath->Get(hist2);
        TH2F* h2 = (TH2F*)RegPath->Get(hist3);
        TH2F* h3 = (TH2F*)RegPath->Get(hist4);
        TH2F* h4 = (TH2F*)RegPath->Get(hist5);
        TH2F* h5 = (TH2F*)RegPath->Get(hist6);
        TH2F* h6 = (TH2F*)MCPath->Get(hist7);
        TH2F* h0 = (TH2F*)RegPath->Get(Acci);
        TH2F* h15 = (TH2F*)RegPath->Get(hist6);
        cc->Divide(2,1);
        gStyle->SetOptFit(1011);
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        gStyle->SetStatX(0.9);
        cc->cd(1);
        h->Draw("colz");
        cc->cd(2);
        h6->Draw("colz");
        c1->Divide(4,2);
        gStyle->SetOptFit(1011);
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        gStyle->SetStatX(0.9);
        c1->cd(1);
        h1->Draw("colz");
        c1->cd(2);
        h2->Draw("colz");
        c1->cd(3);
        h3->Draw("colz");
        c1->cd(4);
        //h5->Add(h0,1);
        h15->Draw("colz");
        c1->cd(6);
        h5->Add(h0,-0.25);
        h5->SetMinimum(0);
        h5->Draw("colz");
        c1->cd(7);
        h6->Draw("colz");
        return;}
        
