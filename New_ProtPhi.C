void New_ProtPhi (){

string input;
cout << "Medium intensity or high intensity? Para or Perp? (med/para or high/perp etc.):\n";
getline(cin, input);
if(input=="med/para"){
TString pathWay = Form("/sciclone/data10/zabaldwin/tree_g_Merged/hist_sum_PARA_30276_30788.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/MonteCarlo_new/hist_compton_30001.acc.root");
TString pathWay3 = Form("/sciclone/data10/zabaldwin/MonteCarlo_new/hist_compton_30002.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);
TFile *openData3 = TFile::Open(pathWay3);
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
c7->Divide(2,3);

TCanvas *b0 = new TCanvas("FCAL2 DPhi>1.5", "cc", 800, 400);
b0->Divide(2,3);
TCanvas *b1 = new TCanvas("FCAL2 DE", "cc", 800, 400);
b1->Divide(2,3);
TCanvas *b2 = new TCanvas("FCAL2 DTheta", "cc", 800, 400);
b2->Divide(2,3);
TCanvas *b3 = new TCanvas("FCAL2 SigTrans", "cc", 800, 400);
b3->Divide(2,3);
TCanvas *b4 = new TCanvas("FCAL2 SigTheta", "cc", 800, 400);
b4->Divide(2,3);
TCanvas *b5 = new TCanvas("FCAL2 SigLong", "cc", 800, 400);
b5->Divide(2,3);

TCanvas *t0 = new TCanvas("BCAL Orignial", "cc", 800, 400);
t0->Divide(2,3);
TCanvas *t1 = new TCanvas("BCAL Shower", "cc", 800, 400);
t1->Divide(2,3);
TCanvas *t2 = new TCanvas("BCAL DPhi<1.5", "cc", 800, 400);
t2->Divide(2,3);
TCanvas *t3 = new TCanvas("BCAL DE", "cc", 800, 400);
t3->Divide(2,3);
TCanvas *t4 = new TCanvas("BCAL DTheta", "cc", 800, 400);
t4->Divide(2,3);
TCanvas *t5 = new TCanvas("BCAL SigTrans", "cc", 800, 400);
t5->Divide(2,3);
TCanvas *t6 = new TCanvas("BCAL SigTheta", "cc", 800, 400);
t6->Divide(2,3);
TCanvas *t7 = new TCanvas("BCAL SigLong", "cc", 800, 400);
t7->Divide(2,3);

TCanvas *g0 = new TCanvas("BCAL2 DPhi>1.5", "cc", 800, 400);
g0->Divide(2,3);
TCanvas *g1 = new TCanvas("BCAL2 DE", "cc", 800, 400);
g0->Divide(2,3);
TCanvas *g2 = new TCanvas("BCAL2 DTheta", "cc", 800, 400);
g0->Divide(2,3);
TCanvas *g3 = new TCanvas("BCAL2 SigTrans", "cc", 800, 400);
g0->Divide(2,3);
TCanvas *g4 = new TCanvas("BCAL2 SigTheta", "cc", 800, 400);
g0->Divide(2,3);
TCanvas *g5 = new TCanvas("BCAL2 SigLong", "cc", 800, 400);
g0->Divide(2,3);

TString FCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)Original"};

TString FCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)2Original"};

TString BCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)Original"};

TString BCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)2Original"};
TString Prename[18] = {"BeamAsymmetry/PreCut/DeltaPhiFCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhiBCALprePreCut", "BeamAsymmetry/PreCut/ShowerFCALprePreCut", "BeamAsymmetry/PreCut/ShowerBCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1.5_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_BCALprePreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1,5_BCALprePreCut","BeamAsymmetry/PreCut/DeltaE-Theta_FCALprePreCut", "BeamAsymmetry/PreCut/DeltaE-Theta_BCALprePreCut", "BeamAsymmetry/PreCut/SigTrans_FCALprePreCut", "BeamAsymmetry/PreCut/SigTrans_BCALprePreCut","BeamAsymmetry/PreCut/SigLong_FCALprePreCut", "BeamAsymmetry/PreCut/SigLong_BCALprePreCut", "BeamAsymmetry/PreCut/SigTheta_FCALprePreCut", "BeamAsymmetry/PreCut/SigTheta_BCALprePreCut"};
TString Postname[18] = {"BeamAsymmetry/PreCut/DeltaPhiFCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhiBCALpostPreCut", "BeamAsymmetry/PreCut/ShowerFCALpostPreCut", "BeamAsymmetry/PreCut/ShowerBCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1.5_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Lessthan_1.5_BCALpostPreCut", "BeamAsymmetry/PreCut/DeltaPhi_Greaterthan_1,5_BCALpostPreCut","BeamAsymmetry/PreCut/DeltaE-Theta_FCALpostPreCut", "BeamAsymmetry/PreCut/DeltaE-Theta_BCALpostPreCut", "BeamAsymmetry/PreCut/SigTrans_FCALpostPreCut", "BeamAsymmetry/PreCut/SigTrans_BCALpostPreCut","BeamAsymmetry/PreCut/SigLong_FCALpostPreCut", "BeamAsymmetry/PreCut/SigLong_BCALpostPreCut", "BeamAsymmetry/PreCut/SigTheta_FCALpostPreCut", "BeamAsymmetry/PreCut/SigTheta_BCALpostPreCut"};

TH2F* h0 = (TH2F*)openData->Get(FCALname[0]);
TH2F* h1 = (TH2F*)openData->Get(FCALname[1]);
TH2F* h2 = (TH2F*)openData->Get(FCALname[2]);
TH2F* h3 = (TH2F*)openData->Get(FCALname[3]);
TH2F* h4 = (TH2F*)openData->Get(FCALname[4]);
TH2F* h5 = (TH2F*)openData->Get(FCALname[5]);
TH2F* h6 = (TH2F*)openData->Get(FCALname[6]);
TH2F* h7 = (TH2F*)openData->Get(FCALname[7]);
TH2F* h8 = (TH2F*)openData->Get(FCALname[8]);


TH2F* j0 = (TH2F*)openData->Get(FCAL2name[0]);
TH2F* j1 = (TH2F*)openData->Get(FCAL2name[1]);
TH2F* j2 = (TH2F*)openData->Get(FCAL2name[2]);
TH2F* j3 = (TH2F*)openData->Get(FCAL2name[3]);
TH2F* j4 = (TH2F*)openData->Get(FCAL2name[4]);
TH2F* j5 = (TH2F*)openData->Get(FCAL2name[5]);
TH2F* j6 = (TH2F*)openData->Get(FCAL2name[6]);

TH2F* m0 = (TH2F*)openData->Get(BCALname[0]);
TH2F* m1 = (TH2F*)openData->Get(BCALname[1]);
TH2F* m2 = (TH2F*)openData->Get(BCALname[2]);
TH2F* m3 = (TH2F*)openData->Get(BCALname[3]);
TH2F* m4 = (TH2F*)openData->Get(BCALname[4]);
TH2F* m5 = (TH2F*)openData->Get(BCALname[5]);
TH2F* m6 = (TH2F*)openData->Get(BCALname[6]);
TH2F* m7 = (TH2F*)openData->Get(BCALname[7]);
TH2F* m8 = (TH2F*)openData->Get(BCALname[8]);

TH2F* z0 = (TH2F*)openData->Get(BCAL2name[0]);
TH2F* z1 = (TH2F*)openData->Get(BCAL2name[1]);
TH2F* z2 = (TH2F*)openData->Get(BCAL2name[2]);
TH2F* z3 = (TH2F*)openData->Get(BCAL2name[3]);
TH2F* z4 = (TH2F*)openData->Get(BCAL2name[4]);
TH2F* z5 = (TH2F*)openData->Get(BCAL2name[5]);
TH2F* z6 = (TH2F*)openData->Get(BCAL2name[6]);

TH2F* h00 = (TH2F*)openData2->Get(FCALname[0]);
TH2F* h11 = (TH2F*)openData2->Get(FCALname[1]);
TH2F* h22 = (TH2F*)openData2->Get(FCALname[2]);
TH2F* h33 = (TH2F*)openData2->Get(FCALname[3]);
TH2F* h44 = (TH2F*)openData2->Get(FCALname[4]);
TH2F* h55 = (TH2F*)openData2->Get(FCALname[5]);
TH2F* h66 = (TH2F*)openData2->Get(FCALname[6]);
TH2F* h77 = (TH2F*)openData2->Get(FCALname[7]);
TH2F* h88 = (TH2F*)openData2->Get(FCALname[8]);


TH2F* j00 = (TH2F*)openData2->Get(FCAL2name[0]);
TH2F* j11 = (TH2F*)openData2->Get(FCAL2name[1]);
TH2F* j22 = (TH2F*)openData2->Get(FCAL2name[2]);
TH2F* j33 = (TH2F*)openData2->Get(FCAL2name[3]);
TH2F* j44= (TH2F*)openData2->Get(FCAL2name[4]);
TH2F* j55 = (TH2F*)openData2->Get(FCAL2name[5]);
TH2F* j66 = (TH2F*)openData2->Get(FCAL2name[6]);

TH2F* m00 = (TH2F*)openData2->Get(BCALname[0]);
TH2F* m11 = (TH2F*)openData2->Get(BCALname[1]);
TH2F* m22 = (TH2F*)openData2->Get(BCALname[2]);
TH2F* m33 = (TH2F*)openData2->Get(BCALname[3]);
TH2F* m44 = (TH2F*)openData2->Get(BCALname[4]);
TH2F* m55 = (TH2F*)openData2->Get(BCALname[5]);
TH2F* m66 = (TH2F*)openData2->Get(BCALname[6]);
TH2F* m77 = (TH2F*)openData2->Get(BCALname[7]);
TH2F* m88 = (TH2F*)openData2->Get(BCALname[8]);

TH2F* z00 = (TH2F*)openData2->Get(BCAL2name[0]);
TH2F* z11 = (TH2F*)openData2->Get(BCAL2name[1]);
TH2F* z22 = (TH2F*)openData2->Get(BCAL2name[2]);
TH2F* z33 = (TH2F*)openData2->Get(BCAL2name[3]);
TH2F* z44 = (TH2F*)openData2->Get(BCAL2name[4]);
TH2F* z55 = (TH2F*)openData2->Get(BCAL2name[5]);
TH2F* z66 = (TH2F*)openData2->Get(BCAL2name[6]);

TH2F* a0 = (TH2F*)openData->Get(Prename[0]);
TH2F* a1 = (TH2F*)openData->Get(Prename[1]);
TH2F* a2 = (TH2F*)openData->Get(Prename[2]);
TH2F* a3 = (TH2F*)openData->Get(Prename[3]);
TH2F* a4 = (TH2F*)openData->Get(Prename[4]);
TH2F* a5 = (TH2F*)openData->Get(Prename[5]);
TH2F* a6 = (TH2F*)openData->Get(Prename[6]);
TH2F* a7 = (TH2F*)openData->Get(Prename[7]);
TH2F* a8 = (TH2F*)openData->Get(Prename[8]);
TH2F* a9 = (TH2F*)openData->Get(Prename[9]);
TH2F* a10 = (TH2F*)openData->Get(Prename[10]);
TH2F* a11 = (TH2F*)openData->Get(Prename[11]);
TH2F* a12 = (TH2F*)openData->Get(Prename[12]);
TH2F* a13 = (TH2F*)openData->Get(Prename[13]);
TH2F* a14 = (TH2F*)openData->Get(Prename[14]);
TH2F* a15 = (TH2F*)openData->Get(Prename[15]);
TH2F* a16 = (TH2F*)openData->Get(Prename[16]);
TH2F* a17 = (TH2F*)openData->Get(Prename[17]);

TH2F* d0 = (TH2F*)openData->Get(Postname[0]);
TH2F* d1 = (TH2F*)openData->Get(Postname[1]);
TH2F* d2 = (TH2F*)openData->Get(Postname[2]);
TH2F* d3 = (TH2F*)openData->Get(Postname[3]);
TH2F* d4 = (TH2F*)openData->Get(Postname[4]);
TH2F* d5 = (TH2F*)openData->Get(Postname[5]);
TH2F* d6 = (TH2F*)openData->Get(Postname[6]);
TH2F* d7 = (TH2F*)openData->Get(Postname[7]);
TH2F* d8 = (TH2F*)openData->Get(Postname[8]);
TH2F* d9 = (TH2F*)openData->Get(Postname[9]);
TH2F* d10 = (TH2F*)openData->Get(Postname[10]);
TH2F* d11 = (TH2F*)openData->Get(Postname[11]);
TH2F* d12 = (TH2F*)openData->Get(Postname[12]);
TH2F* d13 = (TH2F*)openData->Get(Postname[13]);
TH2F* d14 = (TH2F*)openData->Get(Postname[14]);
TH2F* d15 = (TH2F*)openData->Get(Postname[15]);
TH2F* d16 = (TH2F*)openData->Get(Postname[16]);
TH2F* d17 = (TH2F*)openData->Get(Postname[17]);

c0->cd(1);
gStyle->SetOptStat();
h0->Draw();
c0->cd(2);
gStyle->SetOptStat();
h00->Draw();
c0->cd(3);
gStyle->SetOptStat();
a0->Draw("colz");
c0->cd(4);
gStyle->SetOptStat();
d0->Draw("colz");

c1->cd(1);
gStyle->SetOptStat();
h1->Draw();
c1->cd(2);
gStyle->SetOptStat();
h11->Draw();
c1->cd(3);
gStyle->SetOptStat();
a1->Draw("colz");
c1->cd(4);
gStyle->SetOptStat();
d1->Draw("colz");

c2->cd(1);
gStyle->SetOptStat();
h2->Draw();
c2->cd(2);
gStyle->SetOptStat();
h22->Draw();
c2->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
c2->cd(4);
gStyle->SetOptStat();
d2->Draw("colz");

c3->cd(1);
gStyle->SetOptStat();
h3->Draw();
c3->cd(2);
gStyle->SetOptStat();
h33->Draw();
c3->cd(3);
gStyle->SetOptStat();
a3->Draw("colz");
c3->cd(4);
gStyle->SetOptStat();
d3->Draw("colz");

c4->cd(1);
gStyle->SetOptStat();
h4->Draw();
c4->cd(2);
gStyle->SetOptStat();
h44->Draw();
c4->cd(3);
gStyle->SetOptStat();
a4->Draw("colz");
c4->cd(4);
gStyle->SetOptStat();
d4->Draw("colz");

c5->cd(1);
gStyle->SetOptStat();
h5->Draw();
c5->cd(2);
gStyle->SetOptStat();
h55->Draw();
c5->cd(3);
gStyle->SetOptStat();
a5->Draw("colz");
c5->cd(4);
gStyle->SetOptStat();
d5->Draw("colz");

c6->cd(1);
gStyle->SetOptStat();
h6->Draw();
c6->cd(2);
gStyle->SetOptStat();
h66->Draw();
c6->cd(3);
gStyle->SetOptStat();
a6->Draw("colz");
c6->cd(4);
gStyle->SetOptStat();
d6->Draw("colz");

c7->cd(1);
gStyle->SetOptStat();
h7->Draw();
c7->cd(2);
gStyle->SetOptStat();
h77->Draw();
/*c7->cd(3);
gStyle->SetOptStat();
a7->Draw();
c7->cd(4);
gStyle->SetOptStat();
d7->Draw();*/

b0->cd(1);
gStyle->SetOptStat();
j0->Draw();
b0->cd(2);
gStyle->SetOptStat();
j00->Draw();
b0->cd(3);
gStyle->SetOptStat();
a8->Draw();
b0->cd(4);
gStyle->SetOptStat();
d8->Draw();

b1->cd(1);
gStyle->SetOptStat();
j1->Draw();
b1->cd(2);
gStyle->SetOptStat();
j11->Draw();
b1->cd(3);
gStyle->SetOptStat();
a9->Draw("colz");
b1->cd(4);
gStyle->SetOptStat();
d9->Draw("colz");

b2->cd(1);
gStyle->SetOptStat();
j2->Draw();
b2->cd(2);
gStyle->SetOptStat();
j22->Draw();
b2->cd(3);
gStyle->SetOptStat();
a10->Draw("colz");
b2->cd(4);
gStyle->SetOptStat();
d10->Draw("colz");

b3->cd(1);
gStyle->SetOptStat();
j3->Draw();
b3->cd(2);
gStyle->SetOptStat();
j33->Draw();
b3->cd(3);
gStyle->SetOptStat();
a11->Draw("colz");
b3->cd(4);
gStyle->SetOptStat();
d11->Draw("colz");

b4->cd(1);
gStyle->SetOptStat();
j4->Draw();
b4->cd(2);
gStyle->SetOptStat();
j44->Draw();
b4->cd(3);
gStyle->SetOptStat();
a12->Draw("colz");
b4->cd(4);
gStyle->SetOptStat();
d12->Draw("colz");

b5->cd(1);
gStyle->SetOptStat();
j5->Draw();
b5->cd(2);
gStyle->SetOptStat();
j55->Draw();
b5->cd(3);
gStyle->SetOptStat();
/*a13->Draw("colz");
b5->cd(4);
gStyle->SetOptStat();
d13->Draw("colz");
*/
t0->cd(1);
gStyle->SetOptStat();
m0->Draw();
t0->cd(2);
gStyle->SetOptStat();
m00->Draw();
t0->cd(3);
gStyle->SetOptStat();
a14->Draw("colz");
t0->cd(4);
gStyle->SetOptStat();

d14->Draw("colz");

t1->cd(1);
gStyle->SetOptStat();
m1->Draw();
t1->cd(2);
gStyle->SetOptStat();
m11->Draw();
t1->cd(3);
gStyle->SetOptStat();
a15->Draw("colz");
t1->cd(4);
gStyle->SetOptStat();
d15->Draw("colz");

t2->cd(1);
gStyle->SetOptStat();
m2->Draw();
t2->cd(2);
gStyle->SetOptStat();
m22->Draw();
t2->cd(3);
gStyle->SetOptStat();
/*a16->Draw("colz");
t2->cd(4);
gStyle->SetOptStat();
d16->Draw("colz");
*/
t3->cd(1);
gStyle->SetOptStat();
m3->Draw();
t3->cd(2);
gStyle->SetOptStat();
m33->Draw();
t3->cd(3);
gStyle->SetOptStat();
a17->Draw("colz");
t3->cd(4);
gStyle->SetOptStat();
d17->Draw("colz");

t4->cd(1);
gStyle->SetOptStat();
m4->Draw();
t4->cd(2);
gStyle->SetOptStat();
m44->Draw();
t4->cd(3);
gStyle->SetOptStat();
a1->Draw("colz");
t4->cd(4);
gStyle->SetOptStat();
d1->Draw("colz");

t5->cd(1);
gStyle->SetOptStat();
m5->Draw();
t5->cd(2);
gStyle->SetOptStat();
m55->Draw();
t5->cd(3);
gStyle->SetOptStat();
a1->Draw("colz");
t5->cd(4);
gStyle->SetOptStat();
d1->Draw("colz");

t6->cd(1);
gStyle->SetOptStat();
m6->Draw();
t6->cd(2);
gStyle->SetOptStat();
m66->Draw();
t6->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
t6->cd(4);
gStyle->SetOptStat();
d2->Draw("colz");

t7->cd(1);
gStyle->SetOptStat();
m7->Draw();
t7->cd(2);
gStyle->SetOptStat();
m77->Draw();
t7->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
t7->cd(4);
gStyle->SetOptStat();
d2->Draw("colz");

g0->cd(1);
gStyle->SetOptStat();
z0->Draw();
g0->cd(2);
gStyle->SetOptStat();
z00->Draw();
g0->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
g0->cd(4);
gStyle->SetOptStat();
d2->Draw(" colz");

g1->cd(1);
gStyle->SetOptStat();
z1->Draw();
g1->cd(2);
gStyle->SetOptStat();
z11->Draw();
g1->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
g1->cd(4);
gStyle->SetOptStat();
d2->Draw("colz");

g2->cd(1);
gStyle->SetOptStat();
z2->Draw();
g2->cd(2);
gStyle->SetOptStat();
z22->Draw();
g2->cd(3);
gStyle->SetOptStat();
a4->Draw("colz");
g2->cd(4);
gStyle->SetOptStat();
d4->Draw("colz");

g3->cd(1);
gStyle->SetOptStat();
z3->Draw();
g3->cd(2);
gStyle->SetOptStat();
z33->Draw();
g3->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
g3->cd(4);
gStyle->SetOptStat();
d4->Draw("colz");

g4->cd(1);
gStyle->SetOptStat();
z4->Draw();
g4->cd(2);
gStyle->SetOptStat();
z44->Draw();
g4->cd(3);
gStyle->SetOptStat();
a1->Draw("colz");
g4->cd(4);
gStyle->SetOptStat();
d1->Draw("colz");

g5->cd(1);
gStyle->SetOptStat();
z5->Draw();
g5->cd(2);
gStyle->SetOptStat();
z55->Draw();
g5->cd(3);
gStyle->SetOptStat();
a2->Draw("colz");
g5->cd(4);
gStyle->SetOptStat();
d5->Draw("colz");



}

if(input=="med/perp"){
TString pathWay = Form("/sciclone/data10/zabaldwin/changedCompton/hist_sum_PERP_30274_30788.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/MonteCarlo-2017/simulation/gen_pi0_PARA/hist_compton_30496PERP.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);

TCanvas *c0 = new TCanvas("FCAL Orignial", "cc", 800, 400);
c0->Divide(1,3);
TCanvas *c1 = new TCanvas("FCAL Shower", "cc", 800, 400);
c1->Divide(1,3);
TCanvas *c2 = new TCanvas("FCAL DPhi<1.5", "cc", 800, 400);
c2->Divide(1,3);
TCanvas *c3 = new TCanvas("FCAL DE", "cc", 800, 400);
c3->Divide(1,3);
TCanvas *c4 = new TCanvas("FCAL DTheta", "cc", 800, 400);
c4->Divide(1,3);
TCanvas *c5 = new TCanvas("FCAL SigTrans", "cc", 800, 400);
c5->Divide(1,3);
TCanvas *c6 = new TCanvas("FCAL SigTheta", "cc", 800, 400);
c6->Divide(1,3);
TCanvas *c7 = new TCanvas("FCAL SigLong", "cc", 800, 400);
c7->Divide(1,3);

TCanvas *b0 = new TCanvas("FCAL2 DPhi>1.5", "cc", 800, 400);
b0->Divide(1,3);
TCanvas *b1 = new TCanvas("FCAL2 DE", "cc", 800, 400);
b1->Divide(1,3);
TCanvas *b2 = new TCanvas("FCAL2 DTheta", "cc", 800, 400);
b2->Divide(1,3);
TCanvas *b3 = new TCanvas("FCAL2 SigTrans", "cc", 800, 400);
b3->Divide(1,3);
TCanvas *b4 = new TCanvas("FCAL2 SigTheta", "cc", 800, 400);
b4->Divide(1,3);
TCanvas *b5 = new TCanvas("FCAL2 SigLong", "cc", 800, 400);
b5->Divide(1,3);

TCanvas *t0 = new TCanvas("BCAL Orignial", "cc", 800, 400);
t0->Divide(1,3);
TCanvas *t1 = new TCanvas("BCAL Shower", "cc", 800, 400);
t1->Divide(1,3);
TCanvas *t2 = new TCanvas("BCAL DPhi<1.5", "cc", 800, 400);
t2->Divide(1,3);
TCanvas *t3 = new TCanvas("BCAL DE", "cc", 800, 400);
t3->Divide(1,3);
TCanvas *t4 = new TCanvas("BCAL DTheta", "cc", 800, 400);
t4->Divide(1,3);
TCanvas *t5 = new TCanvas("BCAL SigTrans", "cc", 800, 400);
t5->Divide(1,3);
TCanvas *t6 = new TCanvas("BCAL SigTheta", "cc", 800, 400);
t6->Divide(1,3);
TCanvas *t7 = new TCanvas("BCAL SigLong", "cc", 800, 400);
t7->Divide(1,3);

TCanvas *g0 = new TCanvas("BCAL2 DPhi>1.5", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g1 = new TCanvas("BCAL2 DE", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g2 = new TCanvas("BCAL2 DTheta", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g3 = new TCanvas("BCAL2 SigTrans", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g4 = new TCanvas("BCAL2 SigTheta", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g5 = new TCanvas("BCAL2 SigLong", "cc", 800, 400);
g0->Divide(1,3);

TString FCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)Original"};

TString FCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)2Original"};

TString BCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)Original"};

TString BCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)2Original"};

TH2F* h0 = (TH2F*)openData->Get(FCALname[0]);
TH2F* h1 = (TH2F*)openData->Get(FCALname[1]);
TH2F* h2 = (TH2F*)openData->Get(FCALname[2]);
TH2F* h3 = (TH2F*)openData->Get(FCALname[3]);
TH2F* h4 = (TH2F*)openData->Get(FCALname[4]);
TH2F* h5 = (TH2F*)openData->Get(FCALname[5]);
TH2F* h6 = (TH2F*)openData->Get(FCALname[6]);
TH2F* h7 = (TH2F*)openData->Get(FCALname[7]);
TH2F* h8 = (TH2F*)openData->Get(FCALname[8]);

TH2F* j0 = (TH2F*)openData->Get(FCAL2name[0]);
TH2F* j1 = (TH2F*)openData->Get(FCAL2name[1]);
TH2F* j2 = (TH2F*)openData->Get(FCAL2name[2]);
TH2F* j3 = (TH2F*)openData->Get(FCAL2name[3]);
TH2F* j4 = (TH2F*)openData->Get(FCAL2name[4]);
TH2F* j5 = (TH2F*)openData->Get(FCAL2name[5]);
TH2F* j6 = (TH2F*)openData->Get(FCAL2name[6]);

TH2F* m0 = (TH2F*)openData->Get(BCALname[0]);
TH2F* m1 = (TH2F*)openData->Get(BCALname[1]);
TH2F* m2 = (TH2F*)openData->Get(BCALname[2]);
TH2F* m3 = (TH2F*)openData->Get(BCALname[3]);
TH2F* m4 = (TH2F*)openData->Get(BCALname[4]);
TH2F* m5 = (TH2F*)openData->Get(BCALname[5]);
TH2F* m6 = (TH2F*)openData->Get(BCALname[6]);
TH2F* m7 = (TH2F*)openData->Get(BCALname[7]);
TH2F* m8 = (TH2F*)openData->Get(BCALname[8]);

TH2F* z0 = (TH2F*)openData->Get(BCAL2name[0]);
TH2F* z1 = (TH2F*)openData->Get(BCAL2name[1]);
TH2F* z2 = (TH2F*)openData->Get(BCAL2name[2]);
TH2F* z3 = (TH2F*)openData->Get(BCAL2name[3]);
TH2F* z4 = (TH2F*)openData->Get(BCAL2name[4]);
TH2F* z5 = (TH2F*)openData->Get(BCAL2name[5]);
TH2F* z6 = (TH2F*)openData->Get(BCAL2name[6]);
gStyle->SetOptStat();
h0->Draw();
c1->cd();
gStyle->SetOptStat();
h1->Draw();
c2->cd();
gStyle->SetOptStat();
h2->Draw();
c3->cd();
gStyle->SetOptStat();
h3->Draw();
c4->cd();
gStyle->SetOptStat();
h4->Draw();
c5->cd();
gStyle->SetOptStat();
h5->Draw();
c6->cd();
gStyle->SetOptStat();
h6->Draw();
c7->cd();
gStyle->SetOptStat();
h7->Draw();
b0->cd();
gStyle->SetOptStat();
j0->Draw();
b1->cd();
gStyle->SetOptStat();
j1->Draw();
b2->cd();
gStyle->SetOptStat();
j2->Draw();
b3->cd();
gStyle->SetOptStat();
j3->Draw();
b4->cd();
gStyle->SetOptStat();
j4->Draw();
b5->cd();
gStyle->SetOptStat();
j5->Draw();

t0->cd();
gStyle->SetOptStat();
m0->Draw();
t1->cd();
gStyle->SetOptStat();
m1->Draw();
t2->cd();
gStyle->SetOptStat();
m2->Draw();
t3->cd();
gStyle->SetOptStat();
m3->Draw();
t4->cd();
gStyle->SetOptStat();
m4->Draw();
t5->cd();
gStyle->SetOptStat();
m5->Draw();
t6->cd();
gStyle->SetOptStat();
m6->Draw();
t7->cd();
gStyle->SetOptStat();
m7->Draw();

g0->cd();
gStyle->SetOptStat();
z0->Draw();
g1->cd();
gStyle->SetOptStat();
z1->Draw();
g2->cd();
gStyle->SetOptStat();
z2->Draw();
g3->cd();
gStyle->SetOptStat();
z3->Draw();
g4->cd();
gStyle->SetOptStat();
z4->Draw();
g5->cd();
gStyle->SetOptStat();
z5->Draw();
}
if(input=="high/para"){
TString pathWay = Form("/sciclone/data10/zabaldwin/changedCompton/hist_sum_PARA_30796_31057.root");
TString pathWay2 = Form("/sciclone/data10/zabaldwin/MonteCarlo-2017/simulation/gen_pi0_PARA/hist_compton_30496PARA.acc.root");
TFile *openData = TFile::Open(pathWay);
TFile *openData2 = TFile::Open(pathWay2);

TCanvas *c0 = new TCanvas("FCAL Orignial", "cc", 800, 400);
c0->Divide(1,3);
TCanvas *c1 = new TCanvas("FCAL Shower", "cc", 800, 400);
c1->Divide(1,3);
TCanvas *c2 = new TCanvas("FCAL DPhi<1.5", "cc", 800, 400);
c2->Divide(1,3);
TCanvas *c3 = new TCanvas("FCAL DE", "cc", 800, 400);
c3->Divide(1,3);
TCanvas *c4 = new TCanvas("FCAL DTheta", "cc", 800, 400);
c4->Divide(1,3);
TCanvas *c5 = new TCanvas("FCAL SigTrans", "cc", 800, 400);
c5->Divide(1,3);
TCanvas *c6 = new TCanvas("FCAL SigTheta", "cc", 800, 400);
c6->Divide(1,3);
TCanvas *c7 = new TCanvas("FCAL SigLong", "cc", 800, 400);
c7->Divide(1,3);

TCanvas *b0 = new TCanvas("FCAL2 DPhi>1.5", "cc", 800, 400);
b0->Divide(1,3);
TCanvas *b1 = new TCanvas("FCAL2 DE", "cc", 800, 400);
b1->Divide(1,3);
TCanvas *b2 = new TCanvas("FCAL2 DTheta", "cc", 800, 400);
b2->Divide(1,3);
TCanvas *b3 = new TCanvas("FCAL2 SigTrans", "cc", 800, 400);
b3->Divide(1,3);
TCanvas *b4 = new TCanvas("FCAL2 SigTheta", "cc", 800, 400);
b4->Divide(1,3);
TCanvas *b5 = new TCanvas("FCAL2 SigLong", "cc", 800, 400);
b5->Divide(1,3);

TCanvas *t0 = new TCanvas("BCAL Orignial", "cc", 800, 400);
t0->Divide(1,3);
TCanvas *t1 = new TCanvas("BCAL Shower", "cc", 800, 400);
t1->Divide(1,3);
TCanvas *t2 = new TCanvas("BCAL DPhi<1.5", "cc", 800, 400);
t2->Divide(1,3);
TCanvas *t3 = new TCanvas("BCAL DE", "cc", 800, 400);
t3->Divide(1,3);
TCanvas *t4 = new TCanvas("BCAL DTheta", "cc", 800, 400);
t4->Divide(1,3);
TCanvas *t5 = new TCanvas("BCAL SigTrans", "cc", 800, 400);
t5->Divide(1,3);
TCanvas *t6 = new TCanvas("BCAL SigTheta", "cc", 800, 400);
t6->Divide(1,3);
TCanvas *t7 = new TCanvas("BCAL SigLong", "cc", 800, 400);
t7->Divide(1,3);

TCanvas *g0 = new TCanvas("BCAL2 DPhi>1.5", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g1 = new TCanvas("BCAL2 DE", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g2 = new TCanvas("BCAL2 DTheta", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g3 = new TCanvas("BCAL2 SigTrans", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g4 = new TCanvas("BCAL2 SigTheta", "cc", 800, 400);
g0->Divide(1,3);
TCanvas *g5 = new TCanvas("BCAL2 SigLong", "cc", 800, 400);
g0->Divide(1,3);

TString FCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)Original"};

TString FCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(FCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(FCAL)2Original"};

TString BCALname[9] = {"BeamAsymmetry/Original/ProtonPhi_Original(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_Shower_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaPhi<1.5_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)Original"};

TString BCAL2name[6] = {"BeamAsymmetry/Original/ProtonPhi_DeltaPhi>1.5_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaE_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_DeltaTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTrans_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigTheta_Cut(BCAL)2Original", "BeamAsymmetry/Original/ProtonPhi_SigLong_Cut(BCAL)2Original"};

TH2F* h0 = (TH2F*)openData->Get(FCALname[0]);
TH2F* h1 = (TH2F*)openData->Get(FCALname[1]);
TH2F* h2 = (TH2F*)openData->Get(FCALname[2]);
TH2F* h3 = (TH2F*)openData->Get(FCALname[3]);
TH2F* h4 = (TH2F*)openData->Get(FCALname[4]);
TH2F* h5 = (TH2F*)openData->Get(FCALname[5]);
TH2F* h6 = (TH2F*)openData->Get(FCALname[6]);
TH2F* h7 = (TH2F*)openData->Get(FCALname[7]);
TH2F* h8 = (TH2F*)openData->Get(FCALname[8]);

TH2F* j0 = (TH2F*)openData->Get(FCAL2name[0]);
TH2F* j1 = (TH2F*)openData->Get(FCAL2name[1]);
TH2F* j2 = (TH2F*)openData->Get(FCAL2name[2]);
TH2F* j3 = (TH2F*)openData->Get(FCAL2name[3]);
TH2F* j4 = (TH2F*)openData->Get(FCAL2name[4]);
TH2F* j5 = (TH2F*)openData->Get(FCAL2name[5]);
TH2F* j6 = (TH2F*)openData->Get(FCAL2name[6]);

TH2F* m0 = (TH2F*)openData->Get(BCALname[0]);
TH2F* m1 = (TH2F*)openData->Get(BCALname[1]);
TH2F* m2 = (TH2F*)openData->Get(BCALname[2]);
TH2F* m3 = (TH2F*)openData->Get(BCALname[3]);
TH2F* m4 = (TH2F*)openData->Get(BCALname[4]);
TH2F* m5 = (TH2F*)openData->Get(BCALname[5]);
TH2F* m6 = (TH2F*)openData->Get(BCALname[6]);
TH2F* m7 = (TH2F*)openData->Get(BCALname[7]);
TH2F* m8 = (TH2F*)openData->Get(BCALname[8]);

TH2F* z0 = (TH2F*)openData->Get(BCAL2name[0]);
TH2F* z1 = (TH2F*)openData->Get(BCAL2name[1]);
TH2F* z2 = (TH2F*)openData->Get(BCAL2name[2]);
TH2F* z3 = (TH2F*)openData->Get(BCAL2name[3]);
TH2F* z4 = (TH2F*)openData->Get(BCAL2name[4]);
TH2F* z5 = (TH2F*)openData->Get(BCAL2name[5]);
TH2F* z6 = (TH2F*)openData->Get(BCAL2name[6]);

gStyle->SetOptStat();
h0->Draw();
c1->cd();
gStyle->SetOptStat();
h1->Draw();
c2->cd();
gStyle->SetOptStat();
h2->Draw();
c3->cd();
gStyle->SetOptStat();
h3->Draw();
c4->cd();
gStyle->SetOptStat();
h4->Draw();
c5->cd();
gStyle->SetOptStat();
h5->Draw();
c6->cd();
gStyle->SetOptStat();
h6->Draw();
c7->cd();
gStyle->SetOptStat();
h7->Draw();

b0->cd();
gStyle->SetOptStat();
j0->Draw();
b1->cd();
gStyle->SetOptStat();
j1->Draw();
b2->cd();
gStyle->SetOptStat();
j2->Draw();
b3->cd();
gStyle->SetOptStat();
j3->Draw();
b4->cd();
gStyle->SetOptStat();
j4->Draw();
b5->cd();
gStyle->SetOptStat();
j5->Draw();

t0->cd();
gStyle->SetOptStat();
m0->Draw();
t1->cd();
gStyle->SetOptStat();
m1->Draw();
t2->cd();
gStyle->SetOptStat();
m2->Draw();
t3->cd();
gStyle->SetOptStat();
m3->Draw();
t4->cd();
gStyle->SetOptStat();
m4->Draw();
t5->cd();
gStyle->SetOptStat();
m5->Draw();
t6->cd();
gStyle->SetOptStat();
m6->Draw();
t7->cd();
gStyle->SetOptStat();
m7->Draw();

g0->cd();
gStyle->SetOptStat();
z0->Draw();
g1->cd();
gStyle->SetOptStat();
z1->Draw();
g2->cd();
gStyle->SetOptStat();
z2->Draw();
g3->Draw();
gStyle->SetOptStat();
z3->Draw();
g4->cd();
gStyle->SetOptStat();
z4->Draw();
g5->cd();
gStyle->SetOptStat();
z5->Draw();
}
return;}
