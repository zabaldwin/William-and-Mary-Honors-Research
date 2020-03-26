void sameCompare(){
        TString Path1 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root",11555);
        TString Path2 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root",11555);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");

        TFile *Regpath = TFile::Open(Path1);
        TFile *Reg2path = TFile::Open(Path2);
        TFile *Totalpath = TFile::Open(Path3);

        TCanvas *cc = new TCanvas("cc","Comparison", 800,400);

        string input;
        cout << "Which Histogram do you want to access (write similialy to 'SigTrans_SigLong_'):\n"
;
        getline(cin, input);

        if(input=="BeamEnergy_Init"){
                TString name = "Histograms/";
                name += input;

                TH2F* b = (TH2F*)Reg2path->Get(name);

                gStyle->SetOptStat();
                gStyle->SetOptFit();
                cc->cd(1);
                b->Draw("box colz");}


        string input2;
        cout << "What other Histogram do you want to access (write similialy to 'ProtonP_Theta_Init'):\n"
;
getline(cin, input2);

        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        cc->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += input;
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += input2;
        hist2 += bin;

        TH2F* h = (TH2F*)Reg2path->Get(hist);
        TH2F* h1 = (TH2F*)Reg2path->Get(hist2);
        TH2F* h2 = (TH2F*)Totalpath->Get(hist);
        //TH2F* h3 = (TH2F*)Totalpath->Get(hist2);

        gStyle->SetOptFit();
        cc->cd(1);
        h->Draw("box colz");
        //cc->cd(2);
        //h2->Draw("box colz");
        cc->cd(3);
        h1->Draw("box colz");
        //cc->cd(4);
        //h3->Draw("colz");

        return;}
