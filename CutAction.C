void CutAction(){
        TString Path1 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10005);
        TString Path2 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_compton_%d.acc.root", 10206);
        TString Path3 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_total.acc.root");

        TFile *Totalpath = TFile::Open(Path3);


        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        TString Sig[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

        TString histSig = "Histograms/Fiducial/ProtonPhi_t_Final0_Fiducial";
        TString histSig1 = "Histograms/UE/ProtonPhi_t_Final1_UE";
        TString histSig2 = "Histograms/DeltaTheta/ProtonPhi_t_Final2_DeltaTheta";
        TString histSig3 = "Histograms/DeltaPhiSignal/ProtonPhi_t_Final3_DeltaPhiSignal";

        TString AcciSig = "Histograms/Acci_Fiducial/Acci_ProtonPhi_t_Final0_Fiducial";
        TString AcciSig1 = "Histograms/Acci_UE/Acci_ProtonPhi_t_Final1_UE";
        TString AcciSig2 = "Histograms/Acci_DeltaTheta/Acci_ProtonPhi_t_Final2_DeltaTheta";

        TString AcciSig3 = "Histograms/Acci_DeltaPhiSignal/Acci_ProtonPhi_t_Final3_DeltaPhiSignal";
        /*TH2F* h = (TH2F*)MCpath->Get(histSig);
        TH2F* h = (TH2F*)MCpath->Get(histSig);
        TH2F* h1 = (TH2F*)MC2path->Get(histSig2);
        TH2F* h1 = (TH2F*)MC2path->Get(histSig2);
        TH2F* h = (TH2F*)MCpath->Get(histSig2);
        TH2F* h1 = (TH2F*)MC2path->Get(histSig2);*/

        TH2F* h = (TH2F*)Totalpath->Get(histSig);
        TH2F* h1 = (TH2F*)Totalpath->Get(histSig1);
        TH2F* h2 = (TH2F*)Totalpath->Get(histSig2);
        TH2F* h3 = (TH2F*)Totalpath->Get(histSig3);

        TH2F* f = (TH2F*)Totalpath->Get(AcciSig);
        TH2F* f1 = (TH2F*)Totalpath->Get(AcciSig1);
        TH2F* f2 = (TH2F*)Totalpath->Get(AcciSig2);
        TH2F* f3 = (TH2F*)Totalpath->Get(AcciSig3);

        h->Add(f,-0.25);
        h1->Add(f1,-0.25);
        h2->Add(f2,-0.25);
        h3->Add(f3,-0.25);

        gStyle->SetOptFit();
        gStyle->SetOptStat();

        /*h->Draw();    
        h->GetXaxis()->SetRangeUser(0., 2.5);
        h1->Draw();
        h1->GetXaxis()->SetRangeUser(2.5,5.);
        h2->Draw();
        h2->GetXaxis()->SetRangeUser(5.,7.5);   
        h3->Draw();
        h3->GetXaxis()->SetRangeUser(7.5,9.);
        */

 h->GetYaxis()->SetRange(0,2);
        h->Draw();
        h1->GetYaxis()->SetRange(2,4);
        h1->Draw("same");
        h2->GetYaxis()->SetRange(4,6);
        h2->Draw("same");
        h3->GetYaxis()->SetRange(6,8);
        h3->Draw("same");
return;}
