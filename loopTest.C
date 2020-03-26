void loopTest(){

TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30276_30788.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/MonteCarlo_new/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/MonteCarlo_new/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);
/*
TCanvas *c0 = new TCanvas("FCAL Orignial", "cc", 800, 400);
c0->Divide(2,3);
TCanvas *c1 = new TCanvas("FCAL Shower", "cc", 800, 400);
c1->Divide(2,3);
TCanvas *c2 = new TCanvas("FCAL DPhi<1.5", "cc", 800, 400);
c2->Divide(2,3);
TCanvas *c3 = new TCanvas("FCAL DE", "cc", 800, 400);
c3->Divide(2,3);
TCanvas *c4 = new TCanvas("FCAL DTheta", "cc", 800, 400);
c4->Divide(2,3);
TCanvas *c5 = new TCanvas("FCAL SigTrans", "cc", 800, 400);
c5->Divide(2,3);
TCanvas *c6 = new TCanvas("FCAL SigTheta", "cc", 800, 400);
c6->Divide(2,3);
TCanvas *c7 = new TCanvas("FCAL SigLong", "cc", 800, 400);
c7->Divide(2,3);*/

TString FCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)Original"};
/*
TH2F* h0 = (TH2F*)openData->Get(FCALname[0]);
TH2F* h1 = (TH2F*)openData->Get(FCALname[1]);
TH2F* h2 = (TH2F*)openData->Get(FCALname[2]);
TH2F* h3 = (TH2F*)openData->Get(FCALname[3]);
TH2F* h4 = (TH2F*)openData->Get(FCALname[4]);
TH2F* h5 = (TH2F*)openData->Get(FCALname[5]);
TH2F* h6 = (TH2F*)openData->Get(FCALname[6]);
TH2F* h7 = (TH2F*)openData->Get(FCALname[7]);
TH2F* h8 = (TH2F*)openData->Get(FCALname[8]);
*/
int count=0;
TCanvas *cc = new TCanvas("FCAL","cc", 800, 400);
cc->Divide(2,3);
//cc += count;
//^^ was so complicated
int i=0;
//if(i<9){
/*
TH2F* h = (TH2F*)openData->Get(FCALname[i]);
cc->Divide(2,3);
cc->cd(count+1);
h->Draw();
h += count;
count ++;
cc->cd(count+1);
h->Draw();*/
//for(int i=0; i < 2; i++){
/*TH2F* h = (TH2F*)openData->Get(FCALname[i]);
h+=count;
cout<<h;
h+=count+2;
cout<<"aaaaaaaaaaaaaaaaa"<<endl;
cout<<h;*/
//TH2F* h = (TH2F*)openData->Get(FCALname[i]);
//h = &h[count];
//h->Draw()
while(count<2){
        //cc += count;

        TH2F* h = (TH2F*)openData->Get(FCALname[i]);
        //if(i<9){  

                //TH2F* h = (TH2F*)openData->Get(FCALname[i]);
//      h += count;

        //TH2F* h[count] = (TH2F*)openData->Get(FCALname[count]);
        cc->cd(1);
        //h += count;
        h->Draw();
        //count++;
        cc->cd(2);
        TH2F* z = (TH2F*)openData->Get(FCALname[i+1]);
        z = &z[count];
        i++;
        z->Draw();
        (*h)++;
        count++;
        //i++;
}


return;}
