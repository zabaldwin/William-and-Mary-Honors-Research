#include <sstream>

void Purity_Eff_Sigma(){

TString D_pathWay = "/sciclone/gluex10/zabaldwin/tree_g_B4_F0_Merged/Apr23/hist_sum_PARA_30274_31057.root";

TString C_pathWay = "/sciclone/gluex10/zabaldwin/ComptonMC/Apr23/hist_sum_PARA_30320_31057.root";
TString P0_pathWay = "/sciclone/gluex10/zabaldwin/pi0MC/Apr23/hist_sum_PARA_30320_31057.root";

TFile *comp = TFile::Open(C_pathWay);
TFile *pi0 = TFile::Open(P0_pathWay);
TFile *Para = TFile::Open(D_pathWay);


//TString numb[14] = {".80", ".825", ".85", ".875", ".90", ".925", ".95", ".975", "1.05", "1.1", "1.15", "1.2", "1.25", "1.3"};


TString front = "SigTrans-vs-Variables/";
TString back_2var[2] ={"SigTrans_varyMore_.925_PBCALPreShowerE", "SigTheta_varyMore_.95_PBCALPreShowerE"};

TString back_2var2[1] ={"SigTheta_varyMore_PBCALPreShowerE"};

Double_t arr[14];

int a=0, k=1;


//#if 0
sigTrans = front + back_2var[a];
sigTheta = front + back_2var[k];

sigTheta_MC = front + back_2var2[a];

Roovar_dataTrans_Original = (TH1F*)Para->Get(sigTrans);
Roovar_compTrans_Original = (TH1F*)comp->Get(sigTrans);
Roovar_pi0Trans_Original = (TH1F*)pi0->Get(sigTrans);

Roovar_dataTheta_Original = (TH1F*)Para->Get(sigTheta);
Roovar_compTheta_Original = (TH1F*)comp->Get(sigTheta_MC);
Roovar_pi0Theta_Original = (TH1F*)pi0->Get(sigTheta_MC);
//#endif 
//Roovar_comp = (TH1F*)comp->Get(SigTrans_MC);
//Roovar_pi0 = (TH1F*)pi0->Get(SigTrans_MC);

int maxTrans = Roovar_dataTrans_Original->GetXaxis()->GetNbins();

//Int_t binx1 = Roovar_dataTrans_Original->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_dataTrans_Original->GetXaxis()->FindBin(0.0245);

//Int_t binx1 = Roovar_compTrans_Original->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_compTrans_Original->GetXaxis()->FindBin(0.0085);
//#if 0
Int_t binx11 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx12 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.003);

Float_t entries_Comp = Roovar_compTheta_Original->Integral(binx11, binx12);
Float_t entries_Pi0 = Roovar_pi0Theta_Original->Integral(binx11, binx12);
Float_t data_scale = Roovar_dataTheta_Original->Integral(binx11, binx12);

cout << entries_Comp << " "<< entries_Pi0<< "," << data_scale << endl;

//Float_t scaleFactor_SigThetaComp = (((entries_Comp+entries_Pi0)/data_scale)*entries_Comp);
//Float_t scaleFactor_SigThetaPi0 = (((entries_Comp+entries_Pi0)/data_scale)*entries_Pi0);

Float_t scaleFactor_SigThetaComp = (( 613/data_scale)*521);
Float_t scaleFactor_SigThetaPi0 = ((613/data_scale)*92);

Float_t scaleComp =  (scaleFactor_SigThetaComp)/entries_Comp;
Float_t scalePi0 =  (scaleFactor_SigThetaPi0)/entries_Pi0;
//#endif
TH1F *Roovar_comp_Fin = (TH1F*)Roovar_compTheta_Original->Clone("Roovar_comp_Fin");
//Roovar_comp_Fin->Scale(scaleComp);

TH1F *Roovar_pi0_Fin = (TH1F*)Roovar_pi0Theta_Original->Clone("Roovar_pi0_Fin");
//Roovar_pi0_Fin->Scale(scalePi0);


//#if 0
TCanvas* secondary = new TCanvas("secondary", "RooFit Histogram ", 800, 400);
Roovar_dataTheta_Original->SetAxisRange(0, 50, "Y");
Roovar_dataTheta_Original->SetLineColor(kRed);
//Roovar_dataTheta_Original->Draw();
Roovar_comp_Fin->SetLineColor(kOrange);
Roovar_comp_Fin->Draw("same h");
Roovar_pi0_Fin->SetLineColor(kGreen);
//Roovar_pi0_Fin->Draw("same h");

//#endif 




//#if 0

for(float i=0.587E-3; i < 0.0022 ; i+= 0.00005){


        Int_t binx1 = Roovar_comp_Fin->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_comp_Fin->GetXaxis()->FindBin(i);

        Int_t binx3 = Roovar_pi0_Fin->GetXaxis()->FindBin(0.0); Int_t binx4 = Roovar_pi0_Fin->GetXaxis()->FindBin(i);

        Float_t purIntegralComp = Roovar_compTheta_Original->Integral(binx1, binx2);

        Float_t purIntegralpi0 = Roovar_pi0Theta_Original->Integral(binx3, binx4);

Int_t binx5 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx6 = Roovar_compTheta_Original->GetXaxis()->FindBin(i);

        Int_t binx7 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx8 = Roovar_compTheta_Original->GetXaxis()->FindBin(maxTrans);

        Float_t effIntegralComp = Roovar_compTheta_Original->Integral(binx5, binx6);

        Float_t effIntegralComp_tot = Roovar_compTheta_Original->Integral(binx7, binx8);

        Float_t Purity = purIntegralComp/(purIntegralComp + purIntegralpi0);
        Float_t Efficiency = effIntegralComp/effIntegralComp_tot;

        Float_t tot = (purIntegralComp + purIntegralpi0);
        cout << i << endl;
        //cout << effIntegralComp << endl;
        //cout << effIntegralComp_tot << endl;
        //cout << "__________________________________PURITY_______" << endl;
        //cout << "" << endl;
        //cout << Purity << endl;

        //cout << "__________________________________EFFICIENCY_______" << endl;
//        cout << Efficiency << endl;
        //cout << "" << endl;
}

#if 0
        Int_t binx11 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx12 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.003);
        
        Float_t entries_Comp = Roovar_compTheta_Original->Integral(binx11, binx12);  
        Float_t entries_Pi0 = Roovar_pi0Theta_Original->Integral(binx11, binx12);
        Float_t data_scale = Roovar_dataTheta_Original->Integral(binx11, binx12);       

        Float_t scaleFactor_SigThetaComp = ((613/data_scale)*521);
        Float_t scaleFactor_SigThetaPi0 = ((613/data_scale)*92);

        Float_t scaleComp =  (scaleFactor_SigThetaComp)/entries_Comp;
        Float_t scalePi0 =  (scaleFactor_SigThetaPi0)/entries_Pi0;
                
        TH1F *Roovar_comp_Fin = (TH1F*)Roovar_compTheta_Original->Clone("Roovar_comp_Fin");
        Roovar_comp_Fin->Scale(scaleComp);

        TH1F *Roovar_pi0_Fin = (TH1F*)Roovar_pi0Theta_Original->Clone("Roovar_pi0_Fin");
        Roovar_pi0_Fin->Scale(scalePi0);
        

        TCanvas* secondary = new TCanvas("secondary", "RooFit Histogram ", 800, 400);
        Roovar_dataTheta_Original->SetLineColor(kRed);
        Roovar_dataTheta_Original->Draw();
        Roovar_comp_Fin->SetLineColor(kOrange);
        Roovar_comp_Fin->Draw("same h");
        Roovar_pi0_Fin->SetLineColor(kGreen);
        Roovar_pi0_Fin->Draw("same h");
#endif

#if 0
Int_t binx1 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx2 = Roovar_compTheta_Original->GetXaxis()->FindBin(0.0009);
Int_t binx3 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0); Int_t binx4 = Roovar_dataTheta_Original->GetXaxis()->FindBin(0.0009);

Float_t purIntegralComp = Roovar_compTheta_Original->Integral(binx1, binx2);
Float_t purIntegralData = Roovar_dataTheta_Original->Integral(binx3, binx4);

Float_t Purity = purIntegralComp/purIntegralData;
cout << Purity << endl;

#endif

 return;}
