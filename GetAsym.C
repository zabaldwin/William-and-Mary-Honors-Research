void GetAsym(){

        //TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_31057.root");
        TString Path7 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PARA_30274_30788.root");
        TString dataName = "Other Histograms/Proton_Phi11";
        TFile *PARAdata = TFile::Open(Path7);
        TH1F* dataPARA = (TH1F*)PARAdata->Get(dataName);
        TH1D* dataPARA2 = (TH1D*)PARAdata->Get(dataName);
        //dataPARA->Draw();
        TH1D* h_numer = (TH1D*)dataPARA->Clone("A");


        //TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_31057.root");
        TString Path8 = Form("/sciclone/data10/zabaldwin/comptonNew/hist_sum_PERP_30274_30788.root");
        TFile *PERPdata = TFile::Open(Path8);
        TH1F* dataPERP = (TH1F*)PERPdata->Get(dataName);
        TH1D* dataPERP2 = (TH1D*)PERPdata->Get(dataName);
        h_numer->Add(dataPERP,-1);
        //dataPERP->Draw();
        /*TCanvas* cc = new TCanvas("cc", "",800, 600);
        cc->Divide(2,1);
        cc->cd(1);
        dataPARA->Draw();
        cc->cd(2);
        dataPERP->Draw();*/

        //TCanvas* c1 = new TCanvas("c1", "",800, 600);
        //c1->Divide(2,1);
        //c1->cd(1);
        //h_numer->Draw();\
        //dataPERP->Draw();
        //dataPARA->Add(dataPERP,-1);
        TH1D* h_denom = (TH1D*)dataPERP->Clone("B");
        //dataPARA2->Add(dataPERP2);
        h_denom->Add(dataPARA);
        //c1->cd(2);
        //h_sub->Draw();
        //dataPARA->Add(dataPERP);
        //dataPARA->Draw();

        //h_asym->Add(dataPERP, -1);
        //dividing the numerator and the denominator 
        h_numer->Divide(h_denom);
        //h_numer->Draw();

        //dataPERP->Divide(dataPARA2);
        //dataPERP->Draw();


        TH1F *Asym = (TH1F*)dataPERP->GetAsymmetry(dataPARA);
        Asym->Draw();

return;}
