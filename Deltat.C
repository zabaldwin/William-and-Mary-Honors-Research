void Deltat(){
        TString Path1 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *RegPath = TFile::Open(Path1);
        TFile *MCPath = TFile::Open(Path2);
        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        //TString hist ="Histograms/Deltat_Final_";
        TString hist = "Histograms/Egamma8.4_9/Deltat_Final_Egamma8.4_9";
        TString hist2 = "Other Histograms/Deltat_Init";


        TString Acci = "Histograms/Acci_Egamma8.4_9/Acci_Deltat_Final_Egamma8.4_9";

        TH2F* h1 = (TH2F*)RegPath->Get(hist);
        TH2F* h = (TH2F*)RegPath->Get(hist2);
        TH2F* h3 = (TH2F*)RegPath->Get(Acci);
        TH2F* h4 = (TH2F*)MCPath->Get(hist);

        h1->Add(h3,-1.);

        cc->Divide(2,2);

        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc->cd(1);
        h->Draw("colz");
        cc->cd(2);
        h1->SetMinimum(0);
        h1->Draw("colz");
        cc->cd(3);
        h3->Draw();
        cc->cd(4);
        h3->Add(h3,-0.25);
        h1->Draw();

        return;
}
