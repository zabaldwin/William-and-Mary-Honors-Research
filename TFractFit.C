#include <iostream>
#include <string>
void TFractFit(){

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
SigLong = front+back[i];
SigTheta = front+back[j];
SigTrans = front+back[k];

cc = new TCanvas("cc","Same",800,400);
cc->Divide(3,1);
Out_come= (TH2F*)openData->Get(SigLong);
Out_comeComp= (TH2F*)openData2->Get(SigLong);
Out_comepi0= (TH2F*)openData3->Get(SigLong);
cc->cd(1);
Out_comeComp->Draw();
cc->cd(2);
Out_comepi0->Draw();

TObjArray *mctot = new TObjArray(2);
mctot->Add(Out_comeComp);
mctot->Add(Out_comepi0);

TFractionFitter* myfit = new TFractionFitter(Out_come, mctot);


Out_come->SetAxisRange(0, 800, "Y");
//Out_come->SetAxisRange(0.1, 0.004, "X");

//myfit->Draw("SAME");

//myfit->SetRangeX(1,15);
Int_t status = myfit->Fit();

if(status==0){

        TH1F* result = (TH1F*) myfit->GetPlot();
        cc->cd(3);
        Out_come->Draw("ep");
        result->SetLineColor(2);
        result->Draw("same");
        cc->Print(back[i]+"_fit(new).pdf");
        }
        //Out_comeComp->SetLineColor(1);
        //Out_comeComp->Draw("SAME");
        //Out_comepi0->SetLineColor(3);
        //Out_comepi0->Draw("SAME");}   
/*
TH1F *Out_comeCompFin = (TH1F*)Out_comeComp->Clone("Out_comeCompFin");
Out_comeCompFin->Scale(1.01);
TCanvas *c = new TCanvas("c","c", 800, 300);
c->Divide(4,1);
Out_comeComp->SetLineColor(3);
c->cd(1); Out_comeComp->Draw();
c->cd(2); Out_comeCompFin->Draw();

TH1F *Out_comepi0Fin = (TH1F*)Out_comepi0->Clone("Out_comepi0Fin");
Out_comepi0Fin->Scale(-.0143);
Out_comepi0->SetLineColor(2);
c->cd(3); Out_comepi0->Draw();
c->cd(4); Out_comepi0Fin->Draw();
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
*/
//gSystem->Exec("mv *.pdf /sciclone/home10/zabaldwin/wm_gluex/analysis/compton/selector/macroFolder/ProtonPhi/PDF/");

return;}
