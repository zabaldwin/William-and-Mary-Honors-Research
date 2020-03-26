#include <iostream>
#include <string>
void Scale(){

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

cc = new TCanvas("cc","Same",800,400);
cc->Divide(2,1);
Out_come= (TH1F*)openData->Get(Name3);
Out_comeComp= (TH1F*)openData2->Get(Name3);
Out_comepi0= (TH1F*)openData3->Get(Name3);
          
Out_comeComp->SetAxisRange(0, 1200, "Y");
Out_comepi0->SetAxisRange(0, 1200, "Y");
//Out_comeComp->SetAxisRange(0, 0.01, "X");
//Out_comepi0->SetAxisRange(0, 0.01, "X");
//Out_comeComp->GetYaxis()->SetMaximum(1200);
//Out_comepi0->GetYaxis()->SetMaximum(1200);

TH1F *Out_comeCompFin = (TH1F*)Out_comeComp->Clone("Out_comeCompFin");
//Out_comeCompFin->SetAxisRange(0, 200, "Y");
//Out_comeCompFin->SetAxisRange(0, 0.01, "X");
//Out_comeCompFin->GetYaxis()->SetRangeUser(0, 200);
//Out_comeCompFin->SetAxisRange(0.0005,0.0015 , "x");
Out_comeCompFin->Scale(0.910192);
TCanvas *c = new TCanvas("c","c", 800, 400);
c->Divide(2,1);
Out_comeCompFin->SetLineColor(3);
c->cd(1); Out_comeComp->Draw();
c->cd(2); Out_comeCompFin->Draw();
c->cd(3); Out_comeCompFin->SetAxisRange(0, 1200, "Y"); Out_comeCompFin->Draw();
c->Print(back[k]+"scale-comp.pdf");
TH1F *Out_comepi0Fin = (TH1F*)Out_comepi0->Clone("Out_comepi0Fin");
//Out_comepi0Fin->SetAxisRange(-1, 1, "Y");
//Out_comepi0Fin->SetAxisRange(0, 0.01, "X");
//Out_comepi0Fin->GetYaxis()->SetMaximum(1200);

Out_comepi0Fin->Scale(0.0898325);
Out_comepi0Fin->SetLineColor(3);
cc->cd(1); Out_comepi0->Draw();
cc->cd(2); Out_comepi0Fin->GetYaxis()->SetRangeUser(-1,200); Out_comepi0Fin->Draw();
cc->Print(back[k]+"scale-pi0.pdf");

ccc = new TCanvas("ccc","Weighted",800,400);
ccc->Divide(1,1);
TH1F *FinalData;
TH1F *totCompton; totCompton = Out_comeCompFin; //Out_comeComp->Multiply(Out_comeCompFin); totCompton = Out_comeComp;
TH1F *totpi0; totpi0 = Out_comepi0Fin;//Out_comepi0->Multiply(Out_comepi0Fin); totpi0 = Out_comepi0;
totCompton->Add(totpi0);
FinalData = totCompton;
ccc->cd(1);
FinalData->GetYaxis()->SetRangeUser(0, 1200);
FinalData->Draw();
ccc->Print(back[k]+"-weighted.pdf");

/*Out_come->SetLineColor(1);
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
*/
//gSystem->Exec("mv *.pdf /sciclone/home10/zabaldwin/wm_gluex/analysis/compton/selector/macroFolder/ProtonPhi/PDF/");

return;}
