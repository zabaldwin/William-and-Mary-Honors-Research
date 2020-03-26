#include <sstream>

void Purity_Effi(){

TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/Jun6/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/Jun6/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/Jun6/hist_sum_PARA_30320_31057.root";

TFile *comp_file = TFile::Open(C_pathWay);
TFile *pi0_file = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);


//TString numb[14] = {".80", ".825", ".85", ".875", ".90", ".925", ".95", ".975", "1.05", "1.1", "1.15", "1.2", "1.25", "1.3"};

TString hist = "SigTrans-vs-Variables/";

TString deltaPhi = "Delta_Phi_1D";
TString deltaTheta[2] = {"Delta_Theta_O", "Delta_Theta_Up"};
TString deltaEnergy[2] = {"Delta_Energy_O", "Delta_Energy_Up"};

Double_t arr[14];

int a=0, k=1;

dPhi = hist + deltaPhi;
dTheta_O = hist + deltaTheta[a];
dEnergy_O = hist + deltaEnergy[a];
dTheta_Up = hist + deltaTheta[k];
dEnergy_Up = hist + deltaEnergy[k];

data = (TH1F*)Para->Get(dPhi);
comp = (TH1F*)comp_file->Get(dPhi);
pi0 = (TH1F*)pi0_file->Get(dPhi);
int max = data->GetXaxis()->GetNbins();
//Roovar_dataTheta_Original->SetAxisRange(0, 50, "Y");
cout << max<< endl;
//#if 0
Int_t binx1 = data->GetXaxis()->FindBin(0.0); Int_t binx2 = data->GetXaxis()->FindBin(max);

Float_t entries_Comp = comp->Integral(binx1, binx2);
Float_t entries_Pi0 = pi0->Integral(binx1, binx2);
Float_t data_scale = data->Integral(binx1, binx2);

Float_t scaleFactor_Comp = (((entries_Comp+entries_Pi0)/data_scale)*entries_Comp);
Float_t scaleFactor_Pi0 = (((entries_Comp+entries_Pi0)/data_scale)*entries_Pi0);

Float_t scaleComp =  (scaleFactor_Comp)/entries_Comp;
Float_t scalePi0 =  (scaleFactor_Pi0)/entries_Pi0;

TH1F *comp_Fin = (TH1F*)comp->Clone("comp_Fin");
comp_Fin->Scale(scaleComp);

TH1F *pi0_Fin = (TH1F*)pi0->Clone("pi0_Fin");
pi0_Fin->Scale(scalePi0);

//#endif

TCanvas* secondary = new TCanvas("secondary", "RooFit Histogram ", 800, 400);
data->SetLineColor(kRed);
data->Draw();
comp->SetLineColor(kOrange);
comp->Draw("same h");
pi0->SetLineColor(kGreen);
pi0->Draw("same h");
//#if 0
int count = 0;
int placer[32];
int Purity_arr[32];
int Efficiency_arr[32];
int n = 30;
for(float i=170; i < 190; i+= 0.5){


        Int_t binx1 = comp->GetXaxis()->FindBin(170.0); Int_t binx2 = comp->GetXaxis()->FindBin(i);

        Int_t binx3 = pi0->GetXaxis()->FindBin(170.0); Int_t binx4 = pi0->GetXaxis()->FindBin(i);

        Float_t purIntegralComp = comp->Integral(binx1, binx2);

        Float_t purIntegralpi0 = pi0->Integral(binx3, binx4);



        Int_t binx5 = comp->GetXaxis()->FindBin(170.0); Int_t binx6 = comp->GetXaxis()->FindBin(i);

        Int_t binx7 = comp->GetXaxis()->FindBin(170.0); Int_t binx8 = comp->GetXaxis()->FindBin(max);

        Float_t effIntegralComp = comp->Integral(binx5, binx6);

        Float_t effIntegralComp_tot = comp->Integral(binx7, binx8);

        Float_t Purity = purIntegralComp/(purIntegralComp + purIntegralpi0);
        cout << purIntegralComp << endl;
        cout << purIntegralComp+purIntegralpi0 << endl;
        //      Purity_arr[count] = Purity;

        Float_t Efficiency = effIntegralComp/effIntegralComp_tot;

//      Efficiency_arr[count] = Efficiency; 
        Float_t tot = (purIntegralComp + purIntegralpi0);
        //cout << i << endl;
        //cout << effIntegralComp << endl;
        //cout << effIntegralComp_tot << endl;
        //cout << "__________________________________PURITY_______" << endl;
        //cout << "" << endl;
  //      placer[count]=i;
        //cout << Purity << endl;
        count ++;
        //cout << count << endl;        
        //cout << Purity_arr[1] << endl;
        //if(count == 30){
        //      TGraph* gr = new TGraph(n, placer, Purity_arr);
        //      gr->Draw("A*");}

        //cout << "__________________________________EFFICIENCY_______" << endl;
        //cout << Efficiency << endl;
        //cout << "" << endl;
}

//int n = 60;

//TGraph* gr = new TGraph(n, placer, Purity_arr);
//gr->Draw("A*");

#if 0
Int_t binx1 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0009);
Int_t binx3 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx4 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0009);

Float_t purIntegralComp = Roovar_compTheta_Original->Integral(binx1, binx2);
Float_t purIntegralData = Roovar_dataTheta_Original->Integral(binx3, binx4);

Float_t Purity = purIntegralComp/purIntegralData;
cout << Purity << endl;

#endif

 return;}
