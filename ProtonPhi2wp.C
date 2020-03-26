#include <string>
#include <iostream>
using namespace std;

void ProtonPhi2wq(){
TCanvas *cc= new TCanvas("cc", "cc", 800, 400);
TCanvas *c1= new TCanvas("c1", "cc", 800, 400);
cc->Divide(2,1);

/*TString Path8 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_30274.acc.root");
TString dataName = "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original";
TFile *PARAdata = TFile::Open(Path8);
TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
dataPara->Fit(fPARA, "","");
gStyle->SetOptStat();
cc->cd(1);
fPARA->Draw("SAME");
*/
TString Path9 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_30274.acc.root");
TString dataName2 = "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)2Original";
TFile *PARAdata2 = TFile::Open(Path9);
TH1D* dataPara2 = (TH1D*)PARAdata2->Get(dataName2);


TF1 *fPARA2 = new TF1("Phi_ProtonPARA2", "[0]*(1-[0]*cos(2*(x*3.14159/180.)))",-180, 180);
dataPara2->Fit(fPARA2, "","");
gStyle->SetOptStat();
//cc->cd(2);
fPARA2->Draw("SAME");



return;}
