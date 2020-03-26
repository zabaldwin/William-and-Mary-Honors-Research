#include <iostream>
#include <string>
void TFractFit_Purity(){

TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30274_31057.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);

TString front = "ComptonPurity/";
int i = 0;
int j = 1;
int k = 2;
int l = 3;
int m = 4;
int n = 5;

TString back_DPless[3] = {"SigLong Pure DPlessThan BCAL","SigTheta Pure DPlessThan BCAL","SigTrans Pure DPlessThan BCAL"};
TString back_DPgra[3] = {"SigLong Pure DPgraThan BCAL","SigTheta Pure DPgraThan BCAL","SigTrans Pure DPgraThan BCAL"};

TString back_DPlessSignal[6] = {"SigLong Pure DPlessThan BCAL SignalCutComp","SigTheta Pure DPlessThan BCAL SignalCutComp","SigTrans Pure DPlessThan BCAL SignalCutComp", "SigLong Pure DPlessThan BCAL SignalCutPi0","SigTheta Pure DPlessThan BCAL SignalCutPi0","SigTrans Pure DPlessThan BCAL SignalCutPi0"};
TString back_DPgraSignal[6] = {"SigLong Pure DPgraThan BCAL SignalCutComp","SigTheta Pure DPgraThan BCAL SignalCutComp","SigTrans Pure DPgraThan BCAL SignalCutComp", "SigLong Pure DPgraThan BCAL SignalCutPi0","SigTheta Pure DPgraThan BCAL SignalCutPi0","SigTrans Pure DPgraThan BCAL SignalCutPi0"};

SigLong_DPless = front+back_DPless[i];
SigTheta_DPless = front+back_DPless[j];
SigTrans_DPless = front+back_DPless[k];

SigLong_DPgra = front+back_DPgra[i];
SigTheta_DPgra = front+back_DPgra[j];
SigTrans_DPgra = front+back_DPgra[k];

SigLong_DPlessSignalComp = front+back_DPlessSignal[i];
SigTheta_DPlessSignalComp = front+back_DPlessSignal[j];
SigTrans_DPlessSignalComp = front+back_DPlessSignal[k];
SigLong_DPlessSignalPi0 = front+back_DPlessSignal[l];
SigTheta_DPlessSignalPi0 = front+back_DPlessSignal[m];
SigTrans_DPlessSignalPi0 = front+back_DPlessSignal[n];

SigLong_DPgraSignalComp = front+back_DPgraSignal[i];
SigTheta_DPgraSignalComp = front+back_DPgraSignal[j];
SigTrans_DPgraSignalComp = front+back_DPgraSignal[k];
SigLong_DPgraSignalPi0 = front+back_DPgraSignal[l];
SigTheta_DPgraSignalPi0 = front+back_DPgraSignal[m];
SigTrans_DPgraSignalPi0 = front+back_DPgraSignal[n];

cc = new TCanvas("cc","Same",800,400);
cc->Divide(3,1);
Out_come= (TH2F*)openData->Get(SigTheta_DPlessSignalComp);
Out_comeComp= (TH2F*)openData2->Get(SigTheta_DPlessSignalComp);
Out_comepi0= (TH2F*)openData3->Get(SigTheta_DPlessSignalComp);

//Out_come->SetAxisRange(0, 10, "X"); 
//Out_comeComp->SetAxisRange(0, 10, "X");
//Out_comepi0->SetAxisRange(0, 10, "X");

for(int i=0; i< Out_come->GetXaxis()->GetNbins(); i++) {
        if(Out_come->GetBinContent(i) < 0.000001){
                Out_come->SetBinContent(i,(1/(1* exp(300))));}
}

cc->cd(1);
Out_comeComp->Draw();
cc->cd(2);
Out_comepi0->Draw();

TObjArray *mctot = new TObjArray(2);
mctot->Add(Out_comeComp);
mctot->Add(Out_comepi0);

TFractionFitter* myfit = new TFractionFitter(Out_come, mctot);


//Out_come->SetAxisRange(0, 100, "Y");
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
        cc->Print(back_DPlessSignal[k]+"_fit(Purity).pdf");
        }

return;}
