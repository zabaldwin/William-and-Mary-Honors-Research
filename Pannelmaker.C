#include <iostream>
#include <string>
void Pannelmaker(){

TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30274_30788.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);

TString a = "Histograms/Egamma5_6/";
TString comptonName[3] = { "SigTheta SigLong ComptonEgamma5_6","SigTrans SigLong ComptonEgamma5_6","SigTrans SigTheta ComptonEgamma5_6"};
TString pizeroName[3] = { "SigTheta SigLong Pi-zeroEgamma5_6","SigTrans SigLong Pi-zeroEgamma5_6","SigTrans SigTheta Pi-zeroEgamma5_6"};
TString regular[3] = {"SigTrans_SigTheta_Final2_Egamma5_6","SigTrans_SigLong_Final2_Egamma5_6", "SigTheta_SigLong_Final_Egamma5_6"};

TH2F* cpannel[3];
TH2F* mccpannel[3];
TH2F* mcpipannel[3];
TH2F* ccpannel[3];
TH2F* mmccpannel[3];
TH2F* mmcpipannel[3];
TCanvas* cc[3];
TCanvas* c[3];
i=0;
cc[i]= new TCanvas("Compare","cc",800,400);
        cc[i]->Divide(3,1);
        cpannel[i]= (TH2F*)openData->Get(a+regular[i]);
        mccpannel[i]=  (TH2F*)openData2->Get(a+regular[i]);
        mcpipannel[i]= (TH2F*)openData3->Get(a+regular[i]);
        cc[i]->cd(1);
        cpannel[i]->Draw("colz");
        cc[i]->cd(2);
        mccpannel[i]->Draw("colz");
        cc[i]->cd(3);
        mcpipannel[i]->Draw("colz");

        cc[i]->Print(regular[i]+".pdf");
        /*
for(i=0;i<3;i++){
        cc[i]= new TCanvas("Compare","cc",800,400);
        cc[i]->Divide(3,1);
        cpannel[i]= (TH2F*)openData->Get(a+comptonName[i]);
        mccpannel[i]=  (TH2F*)openData2->Get(a+comptonName[i]);
        mcpipannel[i]= (TH2F*)openData3->Get(a+comptonName[i]);
        cc[i]->cd(1);
        cpannel[i]->Draw("colz");
        cc[i]->cd(2);
        mccpannel[i]->Draw("colz");
        cc[i]->cd(3);
        mcpipannel[i]->Draw("colz");
        
        cc[i]->Print(comptonName[i]+".pdf");
        c[i]= new TCanvas("Compare","c",800,400);
        c[i]->Divide(3,1);
        ccpannel[i]= (TH2F*)openData->Get(a+pizeroName[i]);
        mmccpannel[i]=  (TH2F*)openData2->Get(a+pizeroName[i]);
        mmcpipannel[i]= (TH2F*)openData3->Get(a+pizeroName[i]);
        c[i]->cd(1);
        ccpannel[i]->Draw("colz");
        c[i]->cd(2);
        mmccpannel[i]->Draw("colz");
        c[i]->cd(3);
        mmcpipannel[i]->Draw("colz");
        
        c[i]->Print(pizeroName[i]+".pdf");
        cc[i]= new TCanvas("Compare","cc",800,400);
        cc[i]->Divide(3,1);
        cpannel[i]= (TH2F*)openData->Get(a+regular[i]);
        mccpannel[i]=  (TH2F*)openData2->Get(a+regular[i]);
        mcpipannel[i]= (TH2F*)openData3->Get(a+regular[i]);
        cc[i]->cd(1);
        cpannel[i]->Draw("colz");
        cc[i]->cd(2);
        mccpannel[i]->Draw("colz");
        cc[i]->cd(3);
        mcpipannel[i]->Draw("colz");
        cc[i]->Print(regular[i]+".pdf");}*/
return;}
