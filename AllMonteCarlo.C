void AllMonteCarlo(){

        TString fileName = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TFile *fName = TFile::Open(fileName);
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10006);
        TFile *fName2 = TFile::Open(fileName2);
        TString fileName3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName3 = TFile::Open(fileName3);
        TString fileName4 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10106);
        TFile *fName4 = TFile::Open(fileName4);
        TString fileName5 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10205);
        TFile *fName5 = TFile::Open(fileName5);
        TString fileName6 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10206);
        TFile *fName6 = TFile::Open(fileName6);

        TCanvas *cc= new TCanvas("cc", "cc", 800, 400);

        string input;
        cout << "Which Histogram do you want to access (write similarly to 'SigTrans_SigLong_'):\n"
;
        getline(cin, input);

        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        cc->Divide(3,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += input;
        hist += bin;
TH2F* h = (TH2F*)fName->Get(hist);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist);
        TH2F* h5 = (TH2F*)fName5->Get(hist);
        TH2F* h6 = (TH2F*)fName6->Get(hist);

        cc->cd(1);
        h->Draw("box colz");
        cc->cd(2);
        h2->Draw("box colz");
        cc->cd(3);
        h3->Draw("box colz");
        cc->cd(4);
        h4->Draw("box colz");
        cc->cd(5);
        h5->Draw("box colz");
        cc->cd(6);
        h6->Draw("box colz");

        return;}
