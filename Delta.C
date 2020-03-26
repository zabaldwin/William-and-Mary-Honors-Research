void Delta(){
        for(int count=0; count<4; count++){

        if(count==0){
        TString fileName = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName = TFile::Open(fileName);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        TCanvas *cc1= new TCanvas("cc1", "UnusedEnergy", 800, 400);

        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc1->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "UnusedEnergy_Init";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "UnusedEnergy_Final";
         hist2 += bin;
         TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "PhotonP_Theta_Final_";
        Acci += bin;


        TH2F* h = (TH2F*)fName->Get(hist);
        TH2F* h4 = (TH2F*)fName->Get(hist2);
        TH2F* h1 = (TH2F*)fName->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);

        if(yes=="yes"){
        h->Add(h1,-0.25);}

        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc1->cd(1);
        h4->Draw("box colz");
        cc1->cd(2);
        h->SetName("UnusedEnergy");
        h->SetMinimum(0);
        h->Draw("box colz");
        cc1->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc1->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}}
        return;}
