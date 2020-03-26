void InitialCuts(){
        for(int count=0; count<1; count++){

        /*TString fileName = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);        
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        TCanvas *cc1= new TCanvas("cc1", "PhotonP_Theta", 800, 400);
        TCanvas *cc2= new TCanvas("cc2", "ProtonP_Theta", 800, 400);
        TCanvas *cc3= new TCanvas("cc3", "PhotonTheta_ThetaDet", 800, 400);
        TCanvas *cc4= new TCanvas("cc4", "VertexZ", 800, 400);  
        TCanvas *cc5= new TCanvas("cc5", "VertexR", 800, 400);
        

        
        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;
        
        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;*/

        if(count==0){
        TString fileName = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        TCanvas *cc1= new TCanvas("cc1", "DeltaPhi vs t", 800, 400);
       // TCanvas *cc2= new TCanvas("cc2", "ProtonP_Theta", 800, 400);
        //TCanvas *cc3= new TCanvas("cc3", "PhotonTheta_ThetaDet", 800, 400);
        //TCanvas *cc4= new TCanvas("cc4", "VertexZ", 800, 400);
        //TCanvas *cc5= new TCanvas("cc5", "VertexR", 800, 400);
        
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
        hist += "UnusedEnergyTotal_t_Init";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "UnusedEnergyTotal_t_Init";
        hist2 += bin;


        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "UnusedEnergyTotal_t_Init";
        Acci += bin;


        TH2F* h = (TH2F*)fName4->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist2);
        TH2F* h1 = (TH2F*)fName4->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);
        
         if(yes=="yes"){
        h->Add(h1,-0.25);}

        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc1->cd(1);
        h4->SetName("DeltaEnergy v DeltaTheta Inital");
        h4->Draw("box colz");
        cc1->cd(2);
        TH1D * projh2Y = h->ProjectionY();
        projh2Y->SetName("Projected on Y axis");
        projh2Y->Draw("box colz");
        cc1->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc1->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}

        if(count==1){
        TString fileName = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        //TCanvas *cc1= new TCanvas("cc1", "PhotonP_Theta", 800, 400);
        TCanvas *cc2= new TCanvas("cc2", "DeltaE vs DeltaTheta", 800, 400);
        //TCanvas *cc3= new TCanvas("cc3", "PhotonTheta_ThetaDet", 800, 400);
        //TCanvas *cc4= new TCanvas("cc4", "VertexZ", 800, 400);
        //TCanvas *cc5= new TCanvas("cc5", "VertexR", 800, 400);
        
         string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc2->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "DeltaE_DeltaTheta_BCAL_Final_";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "DeltaE_DeltaTheta_BCAL_Init";
        hist2 += bin;



        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "DeltaE_DeltaTheta_BCAL_Final_";
        Acci += bin;

        TH2F* h = (TH2F*)fName4->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist2);
        TH2F* h1 = (TH2F*)fName4->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);
        
         if(yes=="yes"){
        h->Add(h1,-0.25);}

        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc2->cd(1);
        h4->Draw("box colz");
        cc2->cd(2);
        h->SetName("Delta Energy vs Delta Theta");
        h->SetMinimum(0);
        h->Draw("box colz");
        cc2->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc2->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}

        if(count==2){
        TString fileName = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        //TCanvas *cc1= new TCanvas("cc1", "PhotonP_Theta", 800, 400);
        //TCanvas *cc2= new TCanvas("cc2", "ProtonP_Theta", 800, 400);
        TCanvas *cc3= new TCanvas("cc3", "DeltaPhi vs DeltaTheta", 800, 400);
        //TCanvas *cc4= new TCanvas("cc4", "VertexZ", 800, 400);
        //TCanvas *cc5= new TCanvas("cc5", "VertexR", 800, 400);


string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc3->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "DeltaPhi_DeltaTheta_BCAL_Final_";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "DeltaPhi_DeltaTheta_BCAL_Init";
        hist2 += bin;

        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "DeltaPhi_DeltaTheta_BCAL_Final_";
        Acci += bin;

        TH2F* h = (TH2F*)fName4->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist2);
        TH2F* h1 = (TH2F*)fName4->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);

        if(yes=="yes"){
        h->Add(h1,-0.25);}
        
         gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc3->cd(1);
        h4->Draw("box colz");
        cc3->cd(2);
        h->SetName("Delta Phi vs Delta Theta");
        h->SetMinimum(0);
        h->Draw("box colz");
        cc3->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc3->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}

        if(count==3){
        TString fileName = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        //TCanvas *cc1= new TCanvas("cc1", "PhotonP_Theta", 800, 400);
        //TCanvas *cc2= new TCanvas("cc2", "ProtonP_Theta", 800, 400);
        //TCanvas *cc3= new TCanvas("cc3", "PhotonTheta_ThetaDet", 800, 400);
        TCanvas *cc4= new TCanvas("cc4", "SigTrans vs SigTheta", 800, 400);
        //TCanvas *cc5= new TCanvas("cc5", "VertexR", 800, 400);

string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc4->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "SigTrans_SigTheta_Final2_";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "SigTrans_SigTheta_Init";
        hist2 += bin;

        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "SigTrans_SigTheta_Final2_";
        Acci += bin;

        TH2F* h = (TH2F*)fName4->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist2);
        TH2F* h1 = (TH2F*)fName4->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);

        if(yes=="yes"){
        h->Add(h1,-0.25);}
        
        gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc4->cd(1);
        h4->Draw("box colz");
        cc4->cd(2);
        h->SetName("SigTrans vs SigTheta");
        h->SetMinimum(0);
        h->Draw("box colz");
        cc4->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc4->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}

        if(count==4){
        TString fileName = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%d.acc.root", 11366);
        TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        //TCanvas *cc1= new TCanvas("cc1", "PhotonP_Theta", 800, 400);
        //TCanvas *cc2= new TCanvas("cc2", "ProtonP_Theta", 800, 400);
        //TCanvas *cc3= new TCanvas("cc3", "PhotonTheta_ThetaDet", 800, 400);
        //TCanvas *cc4= new TCanvas("cc4", "VertexZ", 800, 400);
        TCanvas *cc5= new TCanvas("cc5", "SigTrans vs SigLong", 800, 400);


string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc5->Divide(2,2);

        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "SigTrans_SigLong_Final2_";
        hist += bin;

        TString hist2 = "Histograms/";
        hist2 += bin;
        hist2 += "/";
        hist2 += "SigTrans_SigLong_Init";
        hist2 += bin;

        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "SigTrans_SigLong_Final2_";
        Acci += bin;

        TH2F* h = (TH2F*)fName4->Get(hist);
        TH2F* h1 = (TH2F*)fName4->Get(Acci);
        TH2F* h2 = (TH2F*)fName2->Get(hist);
        TH2F* h3 = (TH2F*)fName3->Get(hist);
        TH2F* h4 = (TH2F*)fName4->Get(hist2);

        if(yes=="yes"){
        h->Add(h1,-0.25);}
        
         gStyle->SetOptFit();
        gStyle->SetPalette(1);
        gStyle->SetOptStat();
        cc5->cd(1);
        h4->Draw("box colz");
        cc5->cd(2);
        h->SetName("SigTrans vs SigTheta");
        h->SetMinimum(0);
        h->Draw("box colz");
        cc5->cd(3);
        h2->SetName("Monte Carlo(10005)");
        h2->Draw("box colz");
        cc5->cd(4);
        h3->SetName("Monte Carlo(10105)");
        h3->Draw("box colz");}

        /*if(count==5){TString fileName2 = Form("/sciclone/data10/zabaldwin/compton/hist_total.acc.root");
        TFile *fName4 = TFile::Open(fileName2);
        TString Path2 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10005);
        TString Path3 = Form("/sciclone/data10/zabaldwin/compton/hist_compton_%d.acc.root", 10105);
        TFile *fName = TFile::Open(fileName);
        TFile *fName2 = TFile::Open(Path2);
        TFile *fName3 = TFile::Open(Path3);
        TCanvas *cc6= new TCanvas("cc6", "PhotonP_Theta", 800, 400);

        string bin;
        cout << "Which Egamma bin do you want to veiw (write similarly to Egamma5_6):\n";
        cin >> bin;

        string yes;
        cout << "Do you want to do Accidental subtraction on the histograms? \n";
        cin >> yes;

        cc5->Divide(3,1);
        
        TString hist = "Histograms/";
        hist += bin;
        hist += "/";
        hist += "Dele";
        hist += bin;


        TString Acc = "Acci_";
        TString Acci = "Histograms/";
        Acci += Acc;
        Acci += bin;
        Acci += "/";
        Acci += Acc;
        Acci += "EnergyLoss_P";
        Acci += bin;




*/


}}
              
