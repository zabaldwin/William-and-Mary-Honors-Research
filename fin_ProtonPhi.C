void fin_ProtonPhi(){
//string input;
//cout << "Medium intensity or high intensity? Para or Perp? (med/para or high/perp etc.):\n";
//getline(cin, input);
//if(input=="med/para"){
TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30276_30788.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);

TString FCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)Original"};

TString FCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)2Original"};

TString BCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)Original"};

TString BCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)2Original"};
TString Prename[18] = {"BeamAsymmetry/PreCut/DeltaPhiFCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhiBCALprePreCut", "BeamAsymmetry/PreCut/ShowerFCALprePreCut", "BeamAsymmetry/PreCut/ShowerBCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1.5_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_BCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1,5_BCALprePreCut","BeamAsymmetry/PreCut/DeltaE-Theta_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaE-Theta_BCALprePreCut", "BeamAsymmetry/PreCut/SigTrans_FCALprePreCut", "BeamAsymmetry/PreCut/SigTrans_BCALprePreCut","BeamAsymmetry/PreCut/SigLong_FCALprePreCut", "BeamAsymmetry/PreCut/SigLong_BCALprePreCut", "BeamAsymmetry/PreCut/SigTheta_FCALprePreCut", "BeamAsymmetry/PreCut/SigTheta_BCALprePreCut"};
TString Postname[18] = {"BeamAsymmetry/PreCut/DeltaPhiFCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhiBCALpostPreCut", "BeamAsymmetry/PreCut/ShowerFCALpostPreCut", "BeamAsymmetry/PreCut/ShowerBCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1.5_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_BCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1,5_BCALpostPreCut","BeamAsymmetry/PreCut/DeltaE-Theta_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaE-Theta_BCALpostPreCut", "BeamAsymmetry/PreCut/SigTrans_FCALpostPreCut", "BeamAsymmetry/PreCut/SigTrans_BCALpostPreCut","BeamAsymmetry/PreCut/SigLong_FCALpostPreCut", "BeamAsymmetry/PreCut/SigLong_BCALpostPreCut", "BeamAsymmetry/PreCut/SigTheta_FCALpostPreCut", "BeamAsymmetry/PreCut/SigTheta_BCALpostPreCut"};

TString name[9] = {"Original", "Shower", "Dphi<1.5","DE", "DTheta", "SigTrans", "SigTheta", "SigLong"};

TString name2[7] = {"Dphi>1.5","DE", "DTheta2", "SigTrans2", "SigTheta2", "SigLong2"};

int i=0;
int j=0;
int maxi=10;
int count=1;
int steady=0;
TCanvas *cc[9];
TCanvas *c[9];
c[1]= new TCanvas("Compare","cc",800,400);
TH2F* s = (TH2F*)openData->Get("Histograms/Egamma5_6/SigTheta_SigLong_Final_Egamma5_6");
TH2F* s2 = (TH2F*)openData2->Get("Histograms/Egamma5_6/SigTheta_SigLong_Final_Egamma5_6");
TH2F* s3 = (TH2F*)openData3->Get("Histograms/Egamma5_6/SigTheta_SigLong_Final_Egamma5_6");

c[1]->Divide(3,1);
c[1]->cd(1);
//s->SetLineColor(2);
gStyle->SetOptStat();
s->Draw("colz");
c[1]->cd(2);
gStyle->SetOptStat();
s2->Draw("colz");
c[1]->cd(3);
gStyle->SetOptStat();
s3->Draw("colz");

c[1]->Print("Sig_Theta-Long.pdf");

TH2F* h[9];
TH2F* z[9];
TH2F* b[9];
TH2F* g[9];
TH2F* f[9];
TH2F* d[9];

/*
cc[1]= new TCanvas("Compare","cc",800,400);
cc[1]->Divide(2,1);
TH2F* h0 =(TH2F*)openData->Get("Other Histograms/Photon SigTrans BCAL Shower");
cc[1]->cd(1);
gStyle->SetOptStat();
//h0->SetAxisRange(-50.,50.,"X");
//h0->GetXaxis()->SetRangeUser(50, -50.);
h0->Draw();
TH2F* h1 =(TH2F*)openData->Get(Postname[9]);
cc[1]->cd(2);
gStyle->SetOptStat();
//h1->SetAxisRange(-50,50,"X");
h1->Draw();

cc[1]->Print("DE_DTheta Cut.pdf");

gStyle->SetOptStat();
h0->SetAxisRange(0,10,"X");
h0->Draw();*/
#if 0
for(i;i<8;i++){
        cc[i] = new TCanvas("FCAL","cc", 800, 400);
        h[i]=(TH2F*)openData->Get(FCALname[i]);
        z[i]=(TH2F*)openData->Get(BCALname[i]);
        b[i]=(TH2F*)openData2->Get(FCALname[i]);
        g[i]=(TH2F*)openData2->Get(BCALname[i]);
        cc[i]->Divide(2,2);
        if(count % 2 !=0){
        cc[i]->cd(1);
        gStyle->SetOptStat();

        h[i]->Draw();
        cc[i]->cd(2);
        gStyle->SetOptStat();

        z[i]->Draw();}
        count++;
        if(count % 2 == 0){
        cc[i]->cd(3);
        gStyle->SetOptStat();
        b[i]->GetYaxis()->SetRange(-2.,2.);
        b[i]->SetLineColor(2);
        b[i]->Draw();
        cc[i]->cd(4);
        gStyle->SetOptStat();
        g[i]->SetLineColor(2);
        g[i]->SetAxisRange(-2,2,"Y");
        g[i]->GetYaxis()->SetRange(-2.,2.);
        g[i]->Draw();}
        count++;

        cc[i]->Print(name[i]+".pdf");}
        #elif 0
TH2F* h[9];
for(i;i<2;i++){
        h[i]=(TH2F*)openData->Get(FCALname[i]);
        h[i]->Draw();}
//for(i;i<i;i++){

while(i=+i){    
        cc += count;
        TH2F* h = (TH2F*)openData->Get(FCALname[i]);
        h += count;
        cc->cd(steady+1);
        gStyle->SetOptStat();
        h->Draw();
        TH2F* z = (TH2F*)openData->Get(BCALname[i]);
        z += count;
        cc->cd(steady+2);
        gStyle->SetOptStat();
        z->Draw();
        /*TH2F* a = (TH2F*)openData->Get(Prename[i+1]);
        a += count;
        cc->cd(steady+3);
        gStyle->SetOptStat();
        a->Draw();
        TH2F* b = (TH2F*)openData->Get(Postname[i+1]);
        b += count;
        cc->cd(steady+4);
        gStyle->SetOptStat();
        b->Draw();*/
        TH2F* c = (TH2F*)openData2->Get(FCALname[i]);
        c += count;
        cc->cd(steady+3);
        gStyle->SetOptStat();
        c->SetLineColor(2);
        c->Draw();
        TH2F* d = (TH2F*)openData2->Get(BCALname[i]);
        d += count;
        cc->cd(steady+4);
        gStyle->SetOptStat();
        d->SetLineColor(2);
        d->Draw();
        i++;
        cc->Print("SigTrans.pdf");      
        count++;}


for(i;i<6;i++){
        cc[i] = new TCanvas("FCAL","cc", 800, 400);
        c[i] = new TCanvas("BCAL","c",800,400);
        h[i]=(TH2F*)openData->Get(FCAL2name[i]);
        z[i]=(TH2F*)openData->Get(BCAL2name[i]);
        b[i]=(TH2F*)openData2->Get(FCAL2name[i]);
        g[i]=(TH2F*)openData2->Get(BCAL2name[i]);
        f[i]=(TH2F*)openData3->Get(FCAL2name[i]);
        d[i]=(TH2F*)openData3->Get(BCAL2name[i]);
        
        
        cc[i]->Divide(3,1);
        cc[i]->cd(1);
        gStyle->SetOptStat();
        h[i]->SetLineColor(2);
        h[i]->Draw();
        cc[i]->cd(2);
        gStyle->SetOptStat();
        b[i]->Draw();
        cc[i]->cd(3);
        gStyle->SetOptStat();
        //f[i]->GetYaxis()->SetRange(-2.,2.);
        f[i]->Draw();
        
        cc[i]->Print(name2[i]+"-FCAL.pdf");
        
        
        c[i]->Divide(3,1);
        c[i]->cd(1);
        gStyle->SetOptStat();
        z[i]->SetLineColor(2);
        z[i]->Draw();
        c[i]->cd(2);
        gStyle->SetOptStat();
        //g[i]->SetAxisRange(-3.,3.,"Y");
        g[i]->Draw();
        c[i]->cd(3);
        gStyle->SetOptStat();
        //f[i]->GetYaxis()->SetRange(-2.,2.);
        d[i]->Draw();
        c[i]->Print(name2[i]+"-BCAL.pdf");}
#endif





return;}
