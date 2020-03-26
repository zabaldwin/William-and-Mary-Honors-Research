#include <string>
#include <iostream>
using namespace std;

void PERPproton_phi(){


        string input;
        cout << "Do you want to access MonteCarlo run# 30497PERP?\n"
;
        getline(cin, input);
        if(input=="no"){
                string input2;
                cout << "Which real data intensity do you want to access? (high,med,low,total (for the new data)\n"
;
                getline(cin, input2);
                if(input2=="med"){
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
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);
                                        //dataPERP->Rebin(4);

                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                 TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);
                                        dataPERP->Rebin(4);

                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}

                        else{
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);
TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}}

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
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);
                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_30788.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}}

                if(input2=="high"){
                        string input3;
                        cout << "Do you want shifted data?\n"
;
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
                                
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}

                        else{
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
                                
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30796_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}}
                if(input2=="total"){
                        string input3;
                        cout << "Do you want shifted data?\n"
                        
                        getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}

                        else{
string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_31056.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}}

                if(input2=="low"){
                        string input3;
                        cout << "Do you want shifted data?\n"

getline(cin, input3);
                        if(input3 == "no"){
                                string input0;
                                cout << "Do you want an FCAL cut or BCAL cut?\n"
;
                                getline(cin, input0);
                                if(input0 == "BCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/compton/hist_sum_PERP_11366_11555.root");
                                        TString dataName = "Other Histograms/Proton_Phi22";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}
                                if(input0 == "FCAL"){
                                        TString Path8 = Form("/sciclone/data10/zabaldwin/compton/hist_sum_PERP_11366_11555.root");
                                        TString dataName = "Other Histograms/Proton_Phi11";
                                        TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                        TFile *PERPdata = TFile::Open(Path8);
                                        TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
                                        dataPERP->Fit(fPERP, "","");
                                        gStyle->SetOptStat();
                                        fPERP->Draw("SAME");}}

                        else{
                                cout<<"There are no shift files\n";}}
                                
                                //TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_45_135_30274_31057.root");
                                //TString dataName = "Other Histograms/Proton_Phi";
                                //TString dataBeam = "Histograms/BeamEnrgy_Final_";
                                //TFile *PERPdata = TFile::Open(Path8);
                                //TH1D* dataPERP = (TH1D*)PERPdata->Get(dataName);


                                //TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*((x*3.14159/180.))))",-180, 180);
                                //dataPERP->Fit(fPERP, "","");
                                //gStyle->SetOptStat();
                                //fPERP->Draw("SAME");}}
}
        else{

        TString Path9 = Form("/sciclone/home10/zabaldwin/batch_run/hist_compton_%dPERP.acc.root", 30497);
        TString dataName = "Other Histograms/Proton_Phi";

        TFile *PERPdata = TFile::Open(Path9);
//      TH1D* dataPara = (TH1D*)PARAdata->Get(dataName);
        TH1D* dataPerp = (TH1D*)PERPdata->Get(dataName);
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

//      TCanvas *cc = new TCanvas("cc","Phi vs Proton PARA", 800,400); 
        TCanvas *c1 = new TCanvas("c1","Phi vs Proton PERP", 800,400);
        //cc->Divide(3,2);
        //TF1 *fPARA = new TF1("Phi_ProtonPARA", "[0]*(1-[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        //dataPara->Fit(fPARA, "","");
        //cc->cd(1);
        gStyle->SetOptStat();
       // fPARA->Draw("SAME");
        //Double_t param[2];
        //fPARA->GetParameters(param);
        TF1 *fPERP = new TF1("Phi_ProtonPERP", "[0]*(1+[1]*cos(2*(x*3.14159/180.)))",-180, 180);
        dataPerp->Fit(fPERP, "","");
        //c1->Divide(2,1);
        //cc->cd(2);
        //fPARA->Draw("SAME");
        fPERP->Draw("SAME");}
        /*cc->cd(1);    
        fPARA->Draw();
        cc->cd(2);
        fPERP->Draw();*/
        //fPARA->SetLineColor(kRed);
        //fPERP->SetLineColor(kBlue);
        //fPARA->SetParameter(-180,1400.0);
        //fPERP->SetParameter(-180,2040.0);
        //dataPara->FillRandom(fPARA,10000);





return;}
