#include <string>
#include <iostream>
using namespace std;

void PARAproton_phi(){


        string input;
        cout << "Do you want to access MonteCarlo run# 30497PARA?\n"
;
        getline(cin, input);
        if(input=="no"){
                string input2;
                cout << "Which real data intensity do you want to access? (high,med,low,total(for the new data))\n"
;
                getline(cin, input2);
                if(input2=="high"){

                        string input3;
                        cout << "Do you want shifted data?\n"
;
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
                                        
                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi1";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}
                        else{
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
                                        
                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*((x*3.14159/180.))))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*((x*3.14159/180.+(3.14159/4.)))))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}}
                if(input2=="med"){
                        string input3;
                        cout << "Do you want shifted data?\n"
;
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
                                
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){


                                        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_30788.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TString dataName = "Other Histograms/Proton_Phi1";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}
                        else{

string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi22";

                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30274_30788.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.+3.14159/4)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi11";

                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30274_30788.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}}
                if(input2=="total"){
string input3;
                        cout << "Do you want shifted data?\n"
;
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_31056.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_31056.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}
                        else{

string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30274_31056.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.+3.14159/4)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30274_31056.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path8);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.+3.14159/4)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}}
                if(input2=="low"){

string input3;
                        cout << "Do you want shifted data?\n"
;
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString Path7 = Form("/sciclone/data10/zabaldwin/compton/hist_sum_PARA_11366_11555.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString Path7 = Form("/sciclone/data10/zabaldwin/compton/hist_sum_PARA_11366_11555.root");
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PARAdata = TFile::Open(Path7);
                                        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);


                                        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPara->Fit(fPARA, "","");
                                        gStyle->SetOptStat();
                                        fPARA->Draw("SAME");}}
                        else{

 cout<<"There are no shift files\n";}}
          //                      TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_45_135_30274_31057.root");
        //                        TString dataName = "Other Histograms/Proton_Phi";
      //                          TString dataBeam = "Histograms/BeamEnrgy_Final_";
    //                            TFile *PARAdata = TFile::Open(Path8);
  //                              TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
//

//                                TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
  //                              dataPara->Fit(fPARA, "","");
    //                            gStyle->SetOptStat();
      //                          fPARA->Draw("SAME");}}
        }
        else{

        TString Path9 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%dPARA.acc.root", 30497);

        //TFile *MCpath = TFile::Open(Path1);
        //TFile *MC2path = TFile::Open(Path2);
        //TFile *Totalpath = TFile::Open(Path3);

        //TFile *MCpathNew = TFile::Open(Path4);
        //TFile *MC2pathNew = TFile::Open(Path5);
        TFile *PARAdata = TFile::Open(Path9);
        //TFile *PERPdata = TFile::Open(Path10);

        TString dataName = "Other Histograms/Proton_Phi";
        TString dataBeam = "Histograms/BeamEnrgy_Final_";

        TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
           //TH1D* dataPerp = (TH1D*)PERPdata->Get(dataName);
        //TCanvas *c1 = new TCanvas("c1","Comparison", 800,400);
        /*c1->Divide(1,2);
        c1->cd(1);
        dataPara->Draw();
        c1->cd(2);
        dataPerp->Draw();*/

//      int binLow = dataBeam->FindBin(8.2);
//      int binHigh = dataBeam->FindBin(8.8);
//      int x = 0;
//      int Egamma = (x>binLow && x<binHigh);


        //TCanvas *c1 = new TCanvas("c1","Phi vs Proton PERP", 800,400);
        TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        dataPara->Fit(fPARA, "","");
        gStyle->SetOptStat();
        fPARA->Draw("SAME");}
        //Double_t param[2];
        //fPARA->GetParameters(param);
        //TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        //dataPerp->Fit(fPERP, "","");
        //c1->Divide(2,1);
        //cc->cd(2);
        //fPARA->Draw("SAME");
        //fPERP->Draw("SAME");
        /*cc->cd(1);    
        fPARA->Draw();
        cc->cd(2);
        fPiERP->Draw();*/
        //fPARA->SetLineColor(kRed);
        //fPERP->SetLineColor(kBlue);
        //fPARA->SetParameter(-180,1400.0);
        //fPERP->SetParameter(-180,2040.0);
        //dataPara->FillRandom(fPARA,10000);
        
        return; }
