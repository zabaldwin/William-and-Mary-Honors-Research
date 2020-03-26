#include <iostream>
#include <string>
void Minuit(){

TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30274_31057.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);

TString front = "Histograms/Egamma5_6/";
int i = 0;
int j = 1;
int k = 2;
TString back[3] = {"SigLong YieldEgamma5_6","SigTheta YieldEgamma5_6","SigTrans YieldEgamma5_6"};
Name = front+back[i];
Name2 = front+back[j];
Name3 = front+back[k];
/*
cc = new TCanvas("cc","SigLong",800,400);
cc->Divide(3,1);
Out_come= (TH2F*)openData->Get(Name);
Out_comeComp= (TH2F*)openData2->Get(Name); 
Out_comepi0= (TH2F*)openData3->Get(Name);
cc->cd(1);
Out_come->SetAxisRange(0, 200, "Y"); 
Out_come->Draw();
cc->cd(2);
Out_comeComp->SetAxisRange(0, 150, "Y");
Out_comeComp->Draw(); 
cc->cd(3);
Out_comepi0->SetAxisRange(0, 150, "Y");
Out_comepi0->Draw();
    
cc->Print(back[i]+".pdf");
c = new TCanvas("c","SigTheta",800,400);
c->Divide(3,1);
Out_come2 = (TH2F*)openData->Get(Name2);
Out_comeComp2 = (TH2F*)openData2->Get(Name2);
Out_comepi02 = (TH2F*)openData3->Get(Name2);
c->cd(1);
Out_come2->SetAxisRange(0, 500, "Y");
Out_come2->Draw();
c->cd(2);
Out_comeComp2->SetAxisRange(0, 500, "Y");
Out_comeComp2->Draw();
c->cd(3);
Out_comepi02->SetAxisRange(0, 250, "Y");
Out_comepi02->Draw();

c->Print(back[j]+".pdf");

ccc = new TCanvas("ccc","SigTrans",800,400);
ccc->Divide(3,1);
Out_come3= (TH2F*)openData->Get(Name3);
Out_comeComp3= (TH2F*)openData2->Get(Name3);
Out_comepi03= (TH2F*)openData3->Get(Name3);
ccc->cd(1);
Out_come3->SetAxisRange(0, 800, "Y");
Out_come3->Draw();
ccc->cd(2);
Out_comeComp3->SetAxisRange(0, 800, "Y");
Out_comeComp3->Draw();
ccc->cd(3);
Out_comepi03->SetAxisRange(0, 450, "Y");
Out_comepi03->Draw();

ccc->Print(back[k]+".pdf");
*/
cc = new TCanvas("cc","Same",800,400);
Out_come= (TH2F*)openData->Get(Name);
Out_comeComp= (TH2F*)openData2->Get(Name);
Out_comepi0= (TH2F*)openData3->Get(Name);

Out_come->SetLineColor(1);
Out_come->SetAxisRange(0, 200, "Y");
Out_come->Draw();
Out_comeComp->SetLineColor(2);
Out_comeComp->Draw("SAME");
Out_comepi0->SetLineColor(3);
Out_comepi0->Draw("SAME");

cc->Print(back[i]+".pdf");

ccc = new TCanvas("ccc","Same2",800,400);
Out_come2= (TH2F*)openData->Get(Name2);
Out_comeComp2= (TH2F*)openData2->Get(Name2);
Out_comepi02= (TH2F*)openData3->Get(Name2);

Out_come2->SetLineColor(1);
Out_come2->SetAxisRange(0, 800, "Y");
Out_come2->Draw();
Out_comeComp2->SetLineColor(2);
Out_comeComp2->Draw("SAME");
Out_comepi02->SetLineColor(3);
Out_comepi02->Draw("SAME");

ccc->Print(back[j]+".pdf");

cccc = new TCanvas("cccc","Same3",800,400);
Out_come3= (TH2F*)openData->Get(Name3);
Out_comeComp3= (TH2F*)openData2->Get(Name3);
Out_comepi03= (TH2F*)openData3->Get(Name3);

Out_come3->SetLineColor(1);
Out_come3->SetAxisRange(0, 1200, "Y");
Out_come3->Draw();
Out_comeComp3->SetLineColor(2);
Out_comeComp3->Draw("SAME");
Out_comepi03->SetLineColor(3);
Out_comepi03->Draw("SAME");
cccc->Print(back[k]+".pdf");

gSystem->Exec("mv *.pdf /sciclone/home10/zabaldwin/wm_gluex/analysis/compton/selector/macroFolder/ProtonPhi/PDF/");
return;}
