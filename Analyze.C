void Analyze(){

        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10206);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *MCpath = TFile::Open(Path1);
        TFile *MC2path = TFile::Open(Path2);
        TFile *Totalpath = TFile::Open(Path3);

        TCanvas *cc = new TCanvas("cc","Simulation Comparison(SigTrans/Theta)", 800,400);
        TCanvas *c1 = new TCanvas("c1","Simulation Comparison(SigTrans/Long)", 800,400);

        //This will compare the SigTrans and the SigTheta
        TString Sig[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};

        cc->Divide(3,1);
        for(int i=0;i<5;i++){
                TString histSig = "Histograms/";
                histSig += Sig[i];
                histSig += "/SigTrans_SigTheta_";
                histSig += Sig[i];

                TString Acc = "Acci_";
                TString AcciSig = "Histograms/";
                AcciSig += Acc;
                AcciSig += Sig[i];
                AcciSig += "/";
                AcciSig += Acc;
                AcciSig += "SigTrans_SigTheta_";
                AcciSig += Sig[i];

                TH2F* h = (TH2F*)MCpath->Get(histSig);
                TH2F* h1 = (TH2F*)MC2path->Get(histSig);
                TH2F* h2 = (TH2F*)Totalpath->Get(histSig);

                TH2F* h3 = (TH2F*)MCpath->Get(AcciSig);
                TH2F* h4 = (TH2F*)MC2path->Get(AcciSig);

                h->Add(h3,-0.25);
                h1->Add(h4,-0.25);
gStyle->SetOptFit();
                cc->cd(1);
                h->Draw("box color");
                cc->cd(2);
                h1->Draw("box colz");
                cc->cd(3);
                h2->Draw("box colz");}

        cc->Print("SigTrans_SigTheta.png");

        c1->Divide(3,1);
                //This will compare the SigTrans and the SigLong
        TString Sig2[5] = {"Egamma5_6","Egamma6_7","Egamma7_8.4","Egamma8.4_9","Egamma9_12"};
        for(int j=0;j<5;j++){
                TString histSig2 = "Histograms/";
                histSig2 += Sig[j];                                                             histSig2 += "/SigTrans_SigTheta_";
                histSig2 += Sig[j];

                TString Acc = "Acci_";
                TString AcciSig2 = "Histograms/";
                AcciSig2 += Acc;
                AcciSig2 += Sig[j];
                AcciSig2 += "/";
                AcciSig2 += Acc;
                AcciSig2 += "SigTrans_SigTheta_";
                AcciSig2 += Sig[j];

                TH2F* f = (TH2F*)MCpath->Get(histSig2);
                TH2F* f1 = (TH2F*)MC2path->Get(histSig2);
                TH2F* f2 = (TH2F*)Totalpath->Get(histSig2);

                TH2F* f3 = (TH2F*)MCpath->Get(AcciSig2);
                TH2F* f4 = (TH2F*)MC2path->Get(AcciSig2);

                f->Add(f3,-0.25);
                f1->Add(f4,-0.25);
                               gStyle->SetOptFit();
                c1->cd(1);
                f->Draw("box color");
                c1->cd(2);
                f1->Draw("box colz");
                c1->cd(3);
                f2->Draw("box colz");}

        c1->Print("SigTrans_SigLong.png");
        return;



}
