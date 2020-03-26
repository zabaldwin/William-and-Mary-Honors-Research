#include "DSelector_compton.h"
#include <DKinematicData.h>

void DSelector_compton::Init(TTree *locTree)
{
        // The Init() function is called when the selector needs to initialize a new tree or chain.
        // Typically here the branch addresses and branch pointers of the tree will be set.
        // Init() will be called many times when running on PROOF (once per file to be processed).

        //SET OUTPUT FILE NAME //can be overriden by user in PROOF
        dOutputFileName = "compton.root"; //"" for none
        dOutputTreeFileName = ""; //"" for none

        //DO THIS NEXT
        //Because this function gets called for each TTree in the TChain, we must be careful:
                //We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
        bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
        DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
        //gDirectory now points to the output file with name dOutputFileName (if any)
        if(locInitializedPriorFlag)
                return; //have already created histograms, etc. below: exit

        //THEN THIS
        Get_ComboWrappers();
        dPreviousRunNumber = 0;
          
        /*********************************** EXAMPLE USER INITIALIZATION: ANALYSIS ACTIONS **********************************/
        
        //ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
        //false/true below: use measured/kinfit data
      
        //PID
        dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));
        dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.4, Proton, SYS_TOF));
        dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 1.0, Proton, SYS_BCAL));
        dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 2.0, Gamma, SYS_FCAL));
        dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 2.5, Gamma, SYS_BCAL));
        //dAnalysisActions.push_back(new DCutAction_NoPIDHit(dComboWrapper, Gamma, SYS_BCAL));
    
        //MASSES
        dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1));
        //KINFIT RESULTS
        //dAnalysisActions.push_back(new DHistogramAction_KinFitResults(dComboWrapper));
        //dAnalysisActions.push_back(new DCutAction_KinFitFOM(dComboWrapper, 1.0e-10));

        //CUT MISSING MASS
        //dAnalysisActions.push_back(new DCutAction_MissingMassSquared(dComboWrapper, false, -0.1, 0.1));

        //BEAM ENERGY
        dAnalysisActions.push_back(new DHistogramAction_BeamEnergy(dComboWrapper, false));

        //KINEMATICS
        //dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, false));

        //INITIALIZE ACTIONS
        //If you create any actions that you want to run manually (i.e. don't add to dAnalysisActions), be sure to initialize them here as well
        Initialize_Actions();

        /******************************** USER INITIALIZATION: STAND-ALONE HISTOGRAMS *******************************/
        TDirectory *savdir = gDirectory;
        TDirectory *adir = savdir->mkdir("Histograms");
        TDirectory *thedir = savdir->mkdir("BeamAsymmetry");
        TDirectory *purDir = savdir->mkdir("ComptonPurity");
        TDirectory *cvDir = savdir->mkdir("SigTrans-vs-Variables");
        TDirectory *cv2Dir = savdir->mkdir("SigTheta-vs-Variables");
        TDirectory *cv3Dir = savdir->mkdir("SigLong-vs-Variables");
        TDirectory *cv4Dir = savdir->mkdir("FinalAnalysisCuts");
        adir->cd();

        double locPhotonThetaMin = 0.; double locPhotonThetaMax = 60.;
        double locPhotonPMin = 0.; double locPhotonPMax = 12.;
        double locProtonThetaMin = 0.; double locProtonThetaMax = 180.;
        double locProtonPMin = 0.; double locProtonPMax = 6.;



//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//Makes the arrays that will be called 
        TString locRFBinLabel[2] = {"", "Acci_"};
        TString locCutCounterLabel[5] = {"Fiducial", "UE", "DeltaTheta", "DeltaPhiSignal", "DeltaPhiSideband"};
        TString locCutCounter2Label[6] = {"Original", "DetlaPhi Cut", "DeltaPhi<1.5", "DeltaEnergy Cut", "DeltaTheta Cut", "Shower Cut"};
        TString locBeamEBinLabel[5] = {"Egamma5_6", "Egamma6_7", "Egamma7_8.4", "Egamma8.4_9", "Egamma9_12"};
        //int locDeltaPhiOffset = 3;
        TString locCutViewLabel[2]={"PreCut", "AfterCut"};


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//These loops set up the directories to make things cleaner in the TBrowser
        Int_t i,j;
        TDirectory *directories[2][5];
        for (i=0;i<2;i++){
                for(j=0;j<5;j++){


                        TString dirname = locRFBinLabel[i];
                        dirname += locBeamEBinLabel[j];
                        directories[i][j]= adir->mkdir(dirname.Data());}}
        Int_t k,l;
        TDirectory *directories2[2][5];
        for (k=0;k<2;k++){
                for(l=0;l<5;l++){


                        TString dirname2 = locRFBinLabel[k];
                        dirname2 += locCutCounterLabel[l];
                        directories2[k][l]= adir->mkdir(dirname2.Data());}}
        Int_t m,n;
        TDirectory *directories_three[2][6];
        for (m=0;m<2;m++){
                for(n=0;n<6;n++){


                        TString dirname3 = locRFBinLabel[m];
                        dirname3 += locCutCounter2Label[n];
                        directories_three[m][n]= thedir->mkdir(dirname3.Data());}}
                        
                        Int_t x,y;
        TDirectory *directories_four[2][2];
        for(x=0; x<2; x++){
                for(y=0; y<2;y++){
                        TString dircname = locRFBinLabel[x];
                        dircname += locCutViewLabel[y];
                        directories_four[x][y] = thedir->mkdir(dircname.Data());}}

        Int_t a;
        TDirectory *directories_five[2];
        for(a=0; a<2; a++){

                        TString dirname5 = locRFBinLabel[a];
                        directories_five[a] = cvDir->mkdir(dirname5.Data());}

        Int_t b;
        TDirectory *directories_six[2];
        for(b=0; b<2; b++){

                        TString dirname6 = locRFBinLabel[b];
                        directories_six[b] = cv2Dir->mkdir(dirname6.Data());}

        Int_t c;
        TDirectory *directories_seven[2];
        for(c=0; c<2; c++){

                        TString dirname7 = locRFBinLabel[c];
                        directories_seven[c] = cv3Dir->mkdir(dirname7.Data());}

        Int_t d;
        TDirectory *directories_eight[2];
        for(d=0; d<2; d++){

                        TString dirname8 = locRFBinLabel[d];
                        directories_eight[d] = cv4Dir->mkdir(dirname8.Data());}

//wrong variable
        /*Int_t a, b;
        TDirectory *directory_RFBin[2][5];
        for(a=0; a<2; a++){
                
                TString dirRF_name = locRFBinLabel[a];
                dirRF_name += locBeamEBinLabel[b];
                directory_RFBin[a][b] = purDir->mkdir(dirRF_name.Data());}
*/

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//This sets up the variables for just observing normal histograms               
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                dHist_BeamEnergy_Init[locRFBin] = new TH1I(locRFBinLabel[locRFBin]+"BeamEnergy_Init", ";Beam Energy (GeV)", 600, 0.0, 12.0);
                dHist_BeamEnergy_Final[locRFBin] = new TH1I(locRFBinLabel[locRFBin]+"BeamEnergy_Final_", ";Beam Energy (GeV)", 600, 0.0, 12.0);
                dHist_Deltat_Init2[locRFBin] = new TH1I(locRFBinLabel[locRFBin]+"Deltat_Init2", "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                //dHist_Deltat_Final[locRFBin] = new TH1I(locRFBinLabel[locRFBin]+"Deltat_Final_", "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                for(int locBeamEBin=0; locBeamEBin<5; locBeamEBin++) {
                        directories[locRFBin][locBeamEBin]->cd();

                        dHist_Chisq_tracking[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"Chi Squared Tracking"+locBeamEBinLabel[locBeamEBin],"",360,0,300);
                        dHist_Chisq_timing[locRFBin][locBeamEBin]= new TH1I(locRFBinLabel[locRFBin]+"Chi Squared Timing"+locBeamEBinLabel[locBeamEBin],"",360,0,300);
                        dHist_PhotonP_Theta_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonP_Theta_Init"+locBeamEBinLabel[locBeamEBin], "; #theta_{#gamma} (degrees); p_{#gamma} (GeV/c)", 360., locPhotonThetaMin, locPhotonThetaMax, 400, locPhotonPMin, locPhotonPMax);
                        dHist_PhotonTheta_ThetaDet_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonTheta_ThetaDet_Init"+locBeamEBinLabel[locBeamEBin], "; Detector #theta_{#gamma} (degrees); Measured #theta_{#gamma} (degrees)", 360., locPhotonThetaMin, locPhotonThetaMax, 360., locPhotonThetaMin, locPhotonThetaMax);

                        dHist_ProtonP_Theta_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Init"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360., locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);
                        dHist_VertexZ_Init[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"VertexZ_Init"+locBeamEBinLabel[locBeamEBin], "; z_{vertex} (cm)", 300., 0., 300.);
                        dHist_VertexR_Init[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"VertexR_Init"+locBeamEBinLabel[locBeamEBin], "; r_{vertex} (cm)", 200., -5., 2.);

                        dHist_MissingMassSquared_Init[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingMassSquared_Init"+locBeamEBinLabel[locBeamEBin], ";Missing Mass Squared (GeV/c^{2})^{2}", 500, -0.1, 0.1);
                        dHist_MissingEnergy_Init[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingEnergy_Init"+locBeamEBinLabel[locBeamEBin], ";Missing Energy (GeV)", 400, -2.0, 2.0);
                        
                        dHist_UnusedEnergyBCAL_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyBCAL_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); BCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_UnusedEnergyFCAL_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyFCAL_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); FCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_UnusedEnergyTotal_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyTotal_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); BCAL+FCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_PhotonThetaMeasure_PhotonThetaMissing_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonThetaMeasure_PhotonThetaMissing_Init"+locBeamEBinLabel[locBeamEBin], "; #theta #gamma_{Missing} (degrees); #theta #gamma_{Measured} (degrees)", 240, 0., 120., 240, 0., 120.);
                        dHist_DeltaE_DeltaTheta_BCAL_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE_DeltaTheta_BCAL_Init"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta E (GeV)", 200, -20., 20., 500, -9.0, 1.0);
                        dHist_DeltaPhi_DeltaTheta_BCAL_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaTheta_BCAL_Init"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_DeltaTheta_FCAL_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaTheta_FCAL_Init"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{FCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);

                        dHist_DeltaPhi_t_Init[locRFBin][locBeamEBin] = new TH2F(locRFBinLabel[locRFBin]+"DeltaPhi_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); #Delta#phi (degrees)", 250, 0., 5., 200, 170., 190.);
                         dHist_ThetaCM_PhotonTheta_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_PhotonTheta_Init"+locBeamEBinLabel[locBeamEBin], "; #theta_{#gamma} (degrees); #theta_{CM} (degrees)", 360, locPhotonThetaMin, locPhotonThetaMax, 360, 0., 180.);
                        dHist_ThetaCM_ProtonTheta_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_ProtonTheta_Init"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); #theta_{CM} (degrees)", 360, locProtonThetaMin, locProtonThetaMax, 360, 0., 180.);
                        dHist_ThetaCM_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); #theta_{CM} (degrees)", 250, 0., 5.0, 360, 0., 180.);
                        dHist_u_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"u_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); -u (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                        dHist_s_t_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"s_t_Init"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); -s (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                        dHist_u_s_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"u_s_Init"+locBeamEBinLabel[locBeamEBin], "; -s (GeV^{2}); -u (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                        dHist_BCALSigTrans_SigLong_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigLong_Init"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);
                        dHist_BCALSigTrans_SigTheta_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Init"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);
                //      dHist_TrackBCAL_DeltaPhi[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"TrackBCAL_DeltaPhi"+locBeamEBinLabel[locBeamEBin], "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                  //      dHist_TrackBCAL_DeltaZ[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"TrackBCAL_DeltaZ"+locBeamEBinLabel[locBeamEBin], "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                     //   dHist_TrackFCAL_DOCA[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"TrackFCAL_DOCA"+locBeamEBinLabel[locBeamEBin], "; T{Beam}-T{RF}; Counts", 360,-20.,20);

 dHist_MissingMassSquaredPreCut[locRFBin][locBeamEBin]=new TH1I(locRFBinLabel[locRFBin]+"MissingMassSquared_PreCut" +locBeamEBinLabel[locBeamEBin], "; Missing Mass Squared", 200 ,-2.,5);
                        dHist_MissingEnergyPreCut[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingEnergy_PreCut" + locBeamEBinLabel[locBeamEBin], ";Missing Energy",500, -4, 10);
                        dHist_DeltaPhiPreCut[locRFBin][locBeamEBin] =new TH1I(locRFBinLabel[locRFBin]+"DeltaPhi_PreCut" + locBeamEBinLabel[locBeamEBin], ";Deltat",400, 130, 250);

                        dHist_MissingMassSquared1stCut[locRFBin][locBeamEBin]=new TH1I(locRFBinLabel[locRFBin]+"MissingMassSquared_1stCut" +locBeamEBinLabel[locBeamEBin], "; Missing Mass Squared", 200 ,-2.,5);
                        dHist_MissingEnergy1stCut[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingEnergy_1stCut" + locBeamEBinLabel[locBeamEBin], ";Missing Energy",500, -4, 10);
                        dHist_DeltaPhi1stCut[locRFBin][locBeamEBin] =new TH1I(locRFBinLabel[locRFBin]+"DeltaPhi_1stCut" + locBeamEBinLabel[locBeamEBin], ";Deltat",400, 130, 250); 
                        //dHist_MissingMassSquared2ndCut[locRFBin][locBeamEBin]=new TH1I(locRFBinLabel[locRFBin]+"MissingMassSquared_2ndCut" +locBeamEBinLabel[locBeamEBin], "; Missing Mass Squared", 200 ,-2.,5);
                        //dHist_MissingEnergy2ndCut[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingEnergy_2ndCut" + locBeamEBinLabel[locBeamEBin], ";Missing Energy",500, -4, 10);
                        //dHist_DeltaPhi2ndCut[locRFBin][locBeamEBin] =new TH1I(locRFBinLabel[locRFBin]+"DeltaPhi_2ndCut" + locBeamEBinLabel[locBeamEBin], ";Deltat",400, 150, 400);




// This is the set up of "final histograms" when cuts have been made
                        dHist_PhotonP_Theta_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonP_Theta_Final_"+locBeamEBinLabel[locBeamEBin], "; #theta_{#gamma} (degrees); p_{#gamma} (GeV/c)", 360, locPhotonThetaMin, locPhotonThetaMax, 400, locPhotonPMin, locPhotonPMax);
                        dHist_PhotonTheta_ThetaDet_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonTheta_ThetaDet_Final_"+locBeamEBinLabel[locBeamEBin], "; Detector #theta_{#gamma} (degrees); Measured #theta_{#gamma} (degrees)", 360., locPhotonThetaMin, locPhotonThetaMax, 360., locPhotonThetaMin, locPhotonThetaMax);
                        dHist_ProtonP_Theta_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);

                        dHist_ThetaCM_PhotonTheta_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_PhotonTheta_Final_"+locBeamEBinLabel[locBeamEBin], "; #theta_{#gamma} (degrees); #theta_{CM} (degrees)", 360, locPhotonThetaMin, locPhotonThetaMax, 360, 0., 180.);
                        dHist_ThetaCM_ProtonTheta_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_ProtonTheta_Final_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); #theta_{CM} (degrees)", 360, locProtonThetaMin, locProtonThetaMax, 360, 0., 180.);
                        dHist_ThetaCM_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ThetaCM_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); #theta_{CM} (degrees)", 250, 0., 5.0, 360, 0., 180.);
                        dHist_u_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"u_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); -u (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                         dHist_s_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"s_t_Final"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^{2}); -s (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                         dHist_u_s_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"u_s_Final"+locBeamEBinLabel[locBeamEBin], "; -s (GeV^{2}); -u (GeV^{2})", 250, 0., 5.0, 250, 0., 25.0);
                        dHist_EnergyLossPho_P[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"EnergyLossPho_P"+locBeamEBinLabel[locBeamEBin],"",250,0.,10.,450,0.,3.);
                        dHist_EnergyLoss_P[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"EnergyLoss_P"+locBeamEBinLabel[locBeamEBin],"",250,0.,10.,450,0.,3.);
                        dHist_BCALSigTheta_SigLong_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTheta_SigLong_Final_"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.005);
                        dHist_BCALSigTrans_SigTheta_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Final_"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);
                        dHist_ProtonP_Theta_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final2_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);

                        dHist_ProtonP_Theta_Final3[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final3_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);

                        dHist_ProtonP_Theta_Final4[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final4_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);
                        dHist_ProtonP_Theta_Final5[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final5_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);
                        dHist_ProtonP_Theta_Final6[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final6_"+locBeamEBinLabel[locBeamEBin], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);
                        dHist_VertexZ_Final[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"VertexZ_Final_"+locBeamEBinLabel[locBeamEBin], "; z_{vertex} (cm)", 300., 0., 300.);
                        dHist_VertexR_Final[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"VertexR_Final_"+locBeamEBinLabel[locBeamEBin], "; r_{vertex} (cm)", 200., -5., 2.);
                        dHist_MissingMassSquared_Final[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingMassSquared_Final_"+locBeamEBinLabel[locBeamEBin], ";Missing Mass Squared (GeV/c^{2})^{2}", 500, -0.1, 0.1);
                        dHist_MissingEnergy_Final[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"MissingEnergy_Final_"+locBeamEBinLabel[locBeamEBin], ";Missing Energy (GeV)", 400, -2.0, 2.0);
                        dHist_UnusedEnergyBCAL_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyBCAL_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); BCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_UnusedEnergyFCAL_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyFCAL_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); FCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_UnusedEnergyTotal_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"UnusedEnergyTotal_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); BCAL+FCAL Unused Energy (GeV)", 250, 0., 5., 200, 0.0, 2.0);
                        dHist_PhotonThetaMeasure_PhotonThetaMissing_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"PhotonThetaMeasure_PhotonThetaMissing_Final_"+locBeamEBinLabel[locBeamEBin], "; #theta #gamma_{Missing} (degrees); #theta #gamma_{Measured} (degrees)", 240, -50., 120., 240, -50., 120.);
                        dHist_DeltaE_DeltaTheta_BCAL_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE_DeltaTheta_BCAL_Final_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta E (GeV)", 200, -20., 20., 500, -9.0, 1.0);
                        dHist_DeltaPhi_DeltaTheta_BCAL_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaTheta_BCAL_Final_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaE_DeltaTheta_BCAL_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE_DeltaTheta_BCAL_Final2_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta E (GeV)", 200, -20., 20., 500, -9.0, 1.0);
                        dHist_DeltaPhi_DeltaTheta_BCAL_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaTheta_BCAL_Final2_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_DeltaEnergy_BCAL_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaE_BCAL_Final_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta E (GeV)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_DeltaEnergy_BCAL_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaE_BCAL_Final2_"+locBeamEBinLabel[locBeamEBin], "; #Delta E (GeV) #gamma_{BCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_DeltaEnergy_BCAL_Final3[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaE_BCAL_Final3_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{BCAL} (degrees); #Delta E (GeV)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_DeltaTheta_FCAL_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_DeltaTheta_FCAL_Final_"+locBeamEBinLabel[locBeamEBin], "; #Delta#theta #gamma_{FCAL} (degrees); #Delta#phi (degrees)", 200, -10., 10., 200, 170., 190.);
                        dHist_DeltaPhi_t_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"DeltaPhi_t_Final_"+locBeamEBinLabel[locBeamEBin], "; -t (GeV^2); #Delta#phi (degrees)", 250, 0., 5., 200, 170., 190.);
                        //dHist_Deltat_Init2[locRFBin] = new TH1I(locRFBinLabel[locRFBin]+"Deltat_Init2", "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                        
                        dHist_Deltat_Final[locRFBin][locBeamEBin] = new TH1I(locRFBinLabel[locRFBin]+"Deltat_Final_"+locBeamEBinLabel[locBeamEBin], "; T{Beam}-T{RF}; Counts", 360,-20.,20);
                        dHist_dEdx_p_CDC_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"dEdx_p_CDC_Init"+locBeamEBinLabel[locBeamEBin],"", 200,0, 3.5,200,0,17);
                        dHist_dEdx_p_CDC_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"dEdx_p_CDC_Final_"+locBeamEBinLabel[locBeamEBin],"", 200,0, 3.5,200,0,17);
                        dHist_dEdx_p_FDC_Init[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"dEdx_p_FDC_Init_"+locBeamEBinLabel[locBeamEBin],"", 200,0, 3.5,200,0,17);
                        dHist_dEdx_p_FDC_Final[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"dEdx_p_FDC_Final_"+locBeamEBinLabel[locBeamEBin],"", 200,0, 3.5,200,0,17);
                        dHist_BCALSigTrans_SigLong_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigLong_Final2_"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);
                        dHist_BCALSigTrans_SigTheta_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Final2_"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                        //dHist_BCALSigLong_SigTheta_Final2[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Final2_"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#rho}", 200, 0., 0.05, 200, 0., 0.02);
                        dHist_SigTheta_SigLong_Compton[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTheta SigLong Compton"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#theta}", 300, 0, 10, 200, 0., 0.005);
                        dHist_SigTheta_SigTrans_Compton[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans SigTheta Compton"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                        dHist_SigLong_SigTrans_Compton[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans SigLong Compton"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);

                        dHist_SigTheta_SigLong_Pizero[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTheta SigLong Pi-zero"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#theta}", 300, 0, 10, 200, 0., 0.005);
                        dHist_SigTheta_SigTrans_Pizero[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans SigTheta Pi-zero"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.005, 200, 0., 0.02);
                        dHist_SigLong_SigTrans_Pizero[locRFBin][locBeamEBin] = new TH2I(locRFBinLabel[locRFBin]+"SigTrans SigLong Pi-zero"+locBeamEBinLabel[locBeamEBin], "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);
                        dHist_SigLongYield[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Yield" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                        dHist_SigTransYield[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Yield" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                        dHist_SigThetaYield[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Yield" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );
                        dHist_SigLongYield2[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 10);
                        dHist_SigTransYield2[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 10);
                        dHist_SigThetaYield2[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 10);
                        dHist_EPre___EShower[locRFBin] = new TH2F("SigTrans___EPreEShower", ";Energy Shower ;Energy PreShower",  300, 0, 9, 200, 0., 5);
                }
                
                //------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//This sets up the variables to observe plots based off of different cuts applied
                for(int locCutCounter=0; locCutCounter<5; locCutCounter++) {
                        directories2[locRFBin][locCutCounter]->cd();
                        dHist_ProtonPhi_t_Init0[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Init0"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Init0[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Init0"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        //dHist_ProtonP_Theta_Final2[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonP_Theta_Final2_"+locCutCounterLabel[locCutCounter], "; #theta_{p} (degrees); p_{p} (GeV/c)", 360, locProtonThetaMin, locProtonThetaMax, 400, locProtonPMin, locProtonPMax);
                        dHist_ProtonPhi_t_Init1[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Init1"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Init1[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Init1"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);

                        dHist_ProtonPhi_t_Init2[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Init2"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Init2[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Init2"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        dHist_ProtonPhi_t_Init3[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Init3"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Init3[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Init3"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        dHist_ProtonPhi_t_Final0[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Final0_"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Final0[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Final0_"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        dHist_ProtonPhi_t_Final1[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Final1_"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Final1[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Final1_"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        
                        dHist_ProtonPhi_t_Final2[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Final2_"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Final2[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Final2_"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);
                        dHist_ProtonPhi_t_Final3[locRFBin][locCutCounter] = new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_t_Final3_"+locCutCounterLabel[locCutCounter], "; -t (GeV^2); #phi_{p} (degrees)", 250, 0., 5., 360, -180., 180.);
                        dHist_ProtonPhi_ThetaCM_Final3[locRFBin][locCutCounter]= new TH2I(locRFBinLabel[locRFBin]+"ProtonPhi_ThetaCM_Final3_"+locCutCounterLabel[locCutCounter], "; #theta_{CM} (degrees); #phi_{p} (degrees)", 360, 0., 180., 360, -180., 180.);}}

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//This sets up the variables to look at simple 1-D histograms of most variables
        TDirectory *addir = savdir->mkdir("Other Histograms");
        addir->cd();
        dHist_BeamP4xx = new TH1I("Beam Momentum_x", "", 300, 10, 200);
        dHist_BeamP4tt = new TH1I("Beam Momentum_t", "", 300, 10, 200);
        dHist_BeamP4px = new TH1I("Beam Momentum_px", "", 300, 10, 200);
        dHist_BeamP4ee = new TH1I("Beam Momentum_ee", "", 300, 10, 200);
        //dHist_PhotonP4 = new TH1I("Photon Momentum", "", 300, 10, 200);
        //dHist_ProtonP4 = new TH1I("Proton Momentum", "", 300, 10, 200);
        dHist_BeamP4_Measured = new TH1I("Beam Momentum Measured", "", 300, 10, 200);
        //dHist_PhotonP4_Measured = new TH1I("Photon Momentum Measured", "", 300, 10, 200);
        //dHist_ProtonP4_Measured = new TH1I("Proton Momentum Measured", "", 300, 10, 200);
        //dHist_BeamX4_Measured = new TH1I("BeamX4 Momentum Measured", "", 300, 10, 200);
        //dHist_PhotonX4_Measured = new TH1I("PhotonX4 Momentum Measured", "", 300, 10, 200);
        //dHist_ProtonX4_Measured = new TH1I("ProtonX4 Momentum Measured", "", 300, 10, 200);
        
        dHist_PBCALPreShowerE = new TH1I("Photon BCAL PreShower", "", 300, -10, 200);
        dHist_PBCALShowerE = new TH1I("Photon BCAL Shower Energy", "", 300, -10, 200);
        dHist_PhotonBCALShowerZ = new TH1I("Photon BCAL Shower Energy.Z", "", 300, -10, 200);
        dHist_PFCALShowerE = new TH1I("Photon FCAL Shower Energy", "", 300, -10, 200);
        dHist_PSLBCALShower = new TH1I("Photon SigLong BCAL Shower", "", 300, 10, 200);
        dHist_PSTBCALShower = new TH1I("Photon SigTheta BCAL Shower", "", 300, 10, 200);
        dHist_PSTrBCALShower = new TH1I("Photon SigTrans BCAL Shower", "", 300, 10, 200);
        dHist_RFT = new TH1I("Radio Frequency Time", "", 300, 10, 200);
        dHist_BDT = new TH1I("Beam Delta T", "", 300, 10, 200);
        dHist_TCM = new TH1I("Theta Center of Mass", "", 300, 10, 200);
        dHist_loct = new TH1I("loct", "", 300, 10, 200);
        dHist_locu = new TH1I("locu", "", 300, 10, 200);
        dHist_locs = new TH1I("locs", "", 300, 10, 200);
        dHist_Photonp = new TH1I("Photon Momentum", "", 300, 10, 200);
        dHist_Photont = new TH1I("Photon Theta", "", 300, 10, 200);
        dHist_Photontdelta = new TH1I("Photon Theta Delta", "", 300, 10, 200);
        //dHist_Protonp = new TH1I("Proton Momentum", "", 300, 10, 200);
        dHist_Deltat_Init = new TH1I("Deltat_Init", "; T{Beam}-T{RF}; Counts", 360,-20.,20);
        dHist_unusedTotal = new TH1I("UnusedTotal", "", 360,20,20);
        dHist_Protont = new TH1I("Proton Theta", "", 300, 10, 200);
        dHist_ProtonPhi = new TH1F("Proton_Phi1", "", 300, -180, 180);
        dHist_ProtonPhi1 = new TH1F("Proton_Phi1", "", 300, -180, 180);
        dHist_ProtonPhi2 = new TH1F("Proton_Phi2", "", 300, -180, 180);
        dHist_ProtonPhi11 = new TH1F("Proton_Phi11", "", 300, -180, 180);
        dHist_ProtonPhi22 = new TH1F("Proton_Phi22", "", 300, -180, 180);
        dHist_VertZ = new TH1I("VertexZ", "", 300, 10, 200);
        dHist_VertR = new TH1I("VertexR", "", 300, 10, 200);
        dHist_MMS = new TH1I("Missing Mass Squared", "", 300, -2., 2.);
        dHist_ME = new TH1I("Missing Energy", "", 300, -2., 2.);
        dHist_unusedEnergyB = new TH1I("Unused Energy BCAL", "", 300, 10, 200);
        dHist_unusedEnergyF = new TH1I("Unused Energy FCAL", "", 300, 10, 200);
        dHist_DT = new TH1I("Delta Theta", "", 300, 10, 200);
        dHist_DE = new TH1I("Delta Energy", "", 300, 10, 200);
        dHist_DP = new TH1I("Delta Phi", "", 300, 80, 300);
        dHist_TrackBCAL_DeltaPhi = new TH1I("TrackBCAL_DeltaPhi", "", 360,-20.,20);
        dHist_TrackBCAL_DeltaZ= new TH1I("TrackBCAL_DeltaZ", "", 360,-20.,20);
        dHist_TrackFCAL_DOCA = new TH1I("TrackFCAL_DOCA", "", 360,-20.,20);
        dHist_EPre_EShower = new TH1F("EPreShower/EShower", "", 300, -10, 200);
        dHist_PhotonBCALShowerZ_less = new TH1F("Photon BCAL Shower Energy.Z_less", "", 300, -10, 200);
        dHist_PhotonBCALShowerZ_greater = new TH1F("Photon BCAL Shower Energy.Z_greater", "", 300, -10, 200);
        
        dHist_PBCALPreShowerE_less = new TH1F("Photon BCAL PreShower_less", "", 300, -10, 200);
        dHist_PBCALPreShowerE_greater = new TH1F("Photon BCAL PreShower_greater", "", 300, -10, 200);

        dHist_PBCALShowerE_less = new TH1F("Photon BCAL Shower Energy_less", "", 300, -10, 200);
        dHist_PBCALShowerE_greater = new TH1F("Photon BCAL Shower Energy_greater", "", 300, -10, 200);
        //dHist_EPre_EShower = new TH1F("EPre_EShower", ";Energy PreShower/Energy Shower", 300, 0, 50); 
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//Sets up the variables that looks at the differences in the DeltaPhi cuts
        thedir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                for(int locCutCounter2=0; locCutCounter2<6; locCutCounter2++) {
                        directories_three[locRFBin][locCutCounter2]->cd();
                        dHist_ProtonPhi_O_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Original(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL Original); Counts", 300, -180, 180);
                        dHist_ProtonPhi_O_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Original(BCAL)"+locCutCounter2Label[locCutCounter2], "; Proton#phi (BCAL Original); Counts", 300, -180, 180);
                        dHist_ProtonPhi_O_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Original(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 Original); Counts", 300, -180, 180);
                        dHist_ProtonPhi_O_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Original(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 Original); Counts", 300, -180, 180);
                        dHist_ProtonPhi_dPhi5_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi<1.5_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL DPhi<1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_5dPhi_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi>1.5_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL DPhi>1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dE_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaE_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL DE); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dTheta_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaTheta_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL D#theta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_Shower_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Shower_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL Shower); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dPhi5_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi<1.5_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL DPhi<1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_5dPhi_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi>1.5_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL DPhi>1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dE_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaE_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL DE); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dTheta_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaTheta_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL D#theta); Counts",  300, -180, 180);
                        
                        dHist_ProtonPhi_Shower_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Shower_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL Shower); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dE_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaE_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 DE); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dPhi5_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi<1.5_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 DPhi<1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_5dPhi_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi>1.5_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2>1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dTheta_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaTheta_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 D#theta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_Shower_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Shower_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 Shower); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dPhi5_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi<1.5_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 DPhi<1.5); Counts",  300, -180, 180);
                        dHist_ProtonPhi_5dPhi_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaPhi>1.5_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2], "; Proton#phi (BCAL2>1.5); Counts", 300, -180, 180);
                        dHist_ProtonPhi_dE_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaE_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 DE); Counts",  300, -180, 180);
                        dHist_ProtonPhi_dTheta_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_DeltaTheta_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 D#theta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_Shower_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_Shower_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 Shower); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTrans_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTrans_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL SigTrans); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTrans_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTrans_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 SigTrans); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTrans_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTrans_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL SigTrans); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTrans_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTrans_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 SigTrans); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTheta_F[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTheta_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL SigTheta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTheta_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTheta_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 SigTheta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTheta_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTheta_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL SigTheta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigTheta_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigTheta_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 SigTheta); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigLong_F[locRFBin][locCutCounter2]= new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigLong_Cut(FCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL SigLong); Counts",  300, -180, 180);
                        
                        dHist_ProtonPhi_SigLong_F2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigLong_Cut(FCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (FCAL2 SigLong); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigLong_B[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigLong_Cut(BCAL)"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL SigLong); Counts",  300, -180, 180);
                        dHist_ProtonPhi_SigLong_B2[locRFBin][locCutCounter2] = new TH1F(locRFBinLabel[locRFBin]+"ProtonPhi_SigLong_Cut(BCAL)2"+locCutCounter2Label[locCutCounter2],"; Proton#phi (BCAL2 SigLong); Counts",  300, -180, 180);
}

//Sets up variables looking at the pre Cuts and the post Cuts
                for(int locCutView=0; locCutView<2; locCutView++){
                        directories_four[locRFBin][locCutView]->cd();
                        dHist_DeltaPhiFCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhiFCALpre"+locCutViewLabel[locCutView],"; #delta#phi (FCAL); Counts",  300, -130, 230);
                        dHist_DeltaPhiBCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhiBCALpre"+locCutViewLabel[locCutView],"; #delta#phi (BCAL); Counts",  300, -130, 230);
                        dHist_Shower_FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"ShowerFCALpre"+locCutViewLabel[locCutView],"; Shower (FCAL); Counts",  300, -180, 180);
                        dHist_Shower_BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"ShowerBCALpre"+locCutViewLabel[locCutView],"; Shower (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_L5FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Lessthan_1.5_FCALpre"+locCutViewLabel[locCutView],"; #delta#phi<1.5 (FCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_G5FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Greaterthan_1.5_FCALpre"+locCutViewLabel[locCutView],"; #delta#phi>1.5 (FCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_L5BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Lessthan_1.5_BCALpre"+locCutViewLabel[locCutView],"; #delta#phi<1.5 (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_G5BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Greaterthan_1.5_BCALpre"+locCutViewLabel[locCutView],"; #delta#phi>1.5 (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaE_Theta_FCALpre[locRFBin][locCutView] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE-Theta_FCALpre"+locCutViewLabel[locCutView],"; #deltaE (FCAL); #delta#theta (FCAL)", 360, 0., 180., 360, -180., 180.);
                        dHist_DeltaE_Theta_BCALpre[locRFBin][locCutView] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE-Theta_BCALpre"+locCutViewLabel[locCutView],"; #deltaE (BCAL); #delta#theta (BCAL)",  360, 0., 180., 360, -180., 180.);
                        dHist_SigTrans_FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTrans_FCALpre"+locCutViewLabel[locCutView],"; SigTrans (FCAL); Counts",  300, -180, 180);
                        dHist_SigTheta_FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTrans_BCALpre"+locCutViewLabel[locCutView],"; SigTrans (BCAL); Counts",  300, -180, 180);
                        dHist_SigLong_FCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigLong_FCALpre"+locCutViewLabel[locCutView],"; SigLong (FCAL); Counts",  300, -180, 180);
                        dHist_SigTrans_BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigLong_FCALpre"+locCutViewLabel[locCutView],"; SigLong (BCAL); Counts",  300, -180, 180);
                        
                        dHist_SigTheta_BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTheta_FCALpre"+locCutViewLabel[locCutView],"; SigTheta (FCAL); Counts",  300, -180, 180);
                        dHist_SigLong_BCALpre[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTheta_BCALpre"+locCutViewLabel[locCutView],"; SigTheta (BCAL); Counts",  300, -180, 180);

                        dHist_DeltaPhiFCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhiFCALpost"+locCutViewLabel[locCutView],"; #delta#phi (FCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhiBCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhiBCALpost"+locCutViewLabel[locCutView],"; #delta#phi (BCAL); Counts",  300, -180, 180);
                        dHist_Shower_FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"ShowerFCALpost"+locCutViewLabel[locCutView],"; Shower (FCAL); Counts",  300, -180, 180);
                        dHist_Shower_BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"ShowerBCALpost"+locCutViewLabel[locCutView],"; Shower (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_L5FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Lessthan_1.5_FCALpost"+locCutViewLabel[locCutView],"; #delta#phi<1.5 (FCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_G5FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Greaterthan_1.5_FCALpost"+locCutViewLabel[locCutView],"; #delta#phi>1.5 (FCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_L5BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Lessthan_1.5_BCALpost"+locCutViewLabel[locCutView],"; #delta#phi<1.5 (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaPhi_G5BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"DeltaPhi_Greaterthan_1.5_BCALpost"+locCutViewLabel[locCutView],"; #delta#phi>1.5 (BCAL); Counts",  300, -180, 180);
                        dHist_DeltaE_Theta_FCALpost[locRFBin][locCutView] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE-Theta_FCALpost"+locCutViewLabel[locCutView],"; #deltaE (FCAL); #delta#theta (FCAL)", 360, 0., 180., 360, -180., 180.);

                        dHist_DeltaE_Theta_BCALpost[locRFBin][locCutView] = new TH2I(locRFBinLabel[locRFBin]+"DeltaE-Theta_BCALpost"+locCutViewLabel[locCutView],"; #deltaE (BCAL); #delta#theta (BCAL)", 360, 0., 180., 360, -180., 180.);

                        dHist_SigTrans_FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTrans_FCALpost"+locCutViewLabel[locCutView],"; SigTrans (FCAL); Counts",  300, -180, 180);
                        dHist_SigTheta_FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTrans_BCALpost"+locCutViewLabel[locCutView],"; SigTrans (BCAL); Counts",  300, -180, 180);
                        dHist_SigLong_FCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigLong_FCALpost"+locCutViewLabel[locCutView],"; SigLong (FCAL); Counts",  300, -180, 180);
                        dHist_SigTrans_BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigLong_FCALpost"+locCutViewLabel[locCutView],"; SigLong (BCAL); Counts",  300, -180, 180);
                        dHist_SigTheta_BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTheta_FCALpost"+locCutViewLabel[locCutView],"; SigTheta (FCAL); Counts",  300, -180, 180);
                        dHist_SigLong_BCALpost[locRFBin][locCutView] = new TH1F(locRFBinLabel[locRFBin]+"SigTheta_BCALpost"+locCutViewLabel[locCutView],"; SigTheta (BCAL); Counts",  300, -180, 180);}

        }
purDir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                //directory_RFBin[locRFBin][locBeamEBin]->cd();

                dHist_SigLongPure_DPlessThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPlessThan BCAL" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTransPure_DPlessThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPlessThan BCAL", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPlessThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPlessThan BCAL", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );

/*                dHist_SigLongPure_DPgraThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPgraThan BCAL" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30); 
                dHist_SigTransPure_DPgraThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPgraThan BCAL", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPgraThan_B[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPgraThan BCAL", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );
*/
                dHist_SigLongPure_DPlessThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPlessThan BCAL SignalCutComp" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTransPure_DPlessThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPlessThan BCAL SignalCutComp", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPlessThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPlessThan BCAL SignalCutComp", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );

/*                dHist_SigLongPure_DPgraThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPgraThan BCAL SignalCutComp" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTransPure_DPgraThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPgraThan BCAL SignalCutComp", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPgraThan_B_SignalCutComp[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPgraThan BCAL SignalCutComp", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );
*/

                dHist_SigLongPure_DPlessThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPlessThan BCAL SignalCutPi0" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTransPure_DPlessThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPlessThan BCAL SignalCutPi0", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPlessThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPlessThan BCAL SignalCutPi0", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );
                
                /*
                dHist_SigLongPure_DPgraThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Pure DPgraThan BCAL SignalCutPi0" , ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTransPure_DPgraThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Pure DPgraThan BCAL SignalCutPi0", ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigThetaPure_DPgraThan_B_SignalCutPi0[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Pure DPgraThan BCAL SignalCutPi0", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004 );
*/

                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "SigTrans_SigTheta_DPlessThan_B_SignalCutComp", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);

                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "SigLong_SigTheta_DPlessThan_B_SignalCutComp", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#theta}", 300, 0, 10, 200, 0., 0.005);
                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "SigLong_SigTrans_DPlessThan_B_SignalCutComp", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);

                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_DPlessThan_B_SignalCutPi0", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);
                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_SigTheta_DPlessThan_B_SignalCutPi0", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#theta}", 300, 0, 10, 200, 0., 0.005);
                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_SigTrans_DPlessThan_B_SignalCutPi0", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);

                 dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,0.001,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(0.015,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,1000,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,0.015,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(0.025,1000,1);

                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,0.002,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(3,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,0.002,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,1000,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(5,1000,1);
                
                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,0.002,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(3,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,1000,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,0.002,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(5,1000,1);

                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,1000,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,0.001,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(0.015,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,1000,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,0.015,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(0.025,1000,1);

                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,1000,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,0.002,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(3,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,0.002,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,1000,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(5,1000,1);

                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,1000,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(-1,0.002,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(3,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,1000,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(1000,0.002,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(5,1000,1);
                }

                cvDir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                dHist_SigTrans_PhotonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PhotonP", ";PhotonP; BCAL Shower #sigma_{#phi}; PhotonP", 300, 0, 8, 200, 0., 0.02);
                dHist_SigTrans_PhotonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PhotonTheta", ";Photon#theta; BCAL Shower #sigma_{#phi}", 300, 10, 35, 200, 0., 0.02);
                dHist_SigTrans_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PhotonThetaDet", ";Photon#thetaDet BCAL; Shower #sigma_{#phi}",  300, 10, 35, 200, 0., 0.02);
                dHist_SigTrans_PhotonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PhotonPhi", ";Photon#phi ;BCAL Shower #sigma_{#phi}",  300, 0, 200, 200, 0., 0.02);
                dHist_SigTrans_ProtonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ProtonP", "; ProtonP; BCAL Shower #sigma_{#phi}", 300, 0, 6, 200, 0., 0.02);
                dHist_SigTrans_ProtonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ProtonTheta", "; Proton#theta; BCAL Shower #sigma_{#phi}", 300, 20, 70, 200, 0., 0.02);
                dHist_SigTrans_ProtonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ProtonPhi", ";Proton#phi ;BCAL Shower #sigma_{#phi}",  300, 0, 200, 200, 0., 0.02);
                dHist_SigTrans_ProtonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ProtonThetaDet", ";Proton#thetaDet BCAL; Shower #sigma_{#phi}",  300, 0, 50, 200, 0., 0.02);

dHist_SigTrans_PhotonBCALShowerZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PhotonBCALShowerZ", ";PhotonBCALShowerZ ;BCAL Shower #sigma_{#phi}",  300, 150, 450, 200, 0., 0.02);
                dHist_SigTrans_ThetaCM[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ThetaCM", ";ThetaCM ;BCAL Shower #sigma_{#phi}",  300, 25, 100, 200, 0., 0.02);

                dHist_SigTrans_DeltaTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_DetlaTheta", ";#Delta#theta ;BCAL Shower #sigma_{#phi}",  300, -10, 10, 200, 0., 0.02);
                dHist_SigTrans_DeltaE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_DeltaE", ";#DeltaE ;BCAL Shower #sigma_{#phi}",  300, -3, 3, 200, 0., 0.02);
                dHist_SigTrans_DeltaPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_DeltaPhi", ";#Delta#phi ;BCAL Shower #sigma_{#phi}",  300, 150, 200, 200, 0., 0.02);

                dHist_SigTrans_PBCALPreShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PBCALPreShower", ";Photon BCAL Pre Shower ;BCAL Shower #sigma_{#phi}",  300, 0, 4, 200, 0., 0.02);
                dHist_SigTrans_PBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PBCALSE", ";Photon BCAL Shower E ;BCAL Shower #sigma_{#phi}",  300, 2, 7, 200, 0., 0.02);
                dHist_SigTrans_PrBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PrBCALSE", ";Proton BCAL Shower E ;BCAL Shower #sigma_{#phi}",  300, 0, 2, 200, 0., 0.02);
                dHist_SigTrans_PFCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_PFCALSE", ";Photon FCAL Shower E ;BCAL Shower #sigma_{#phi}",  300, -1, 1, 200, 0., 0.02);

                dHist_SigTrans_t[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_t", ";t ;BCAL Shower #sigma_{#phi}",  300, 0, 6, 200, 0., 0.02);
                dHist_SigTrans_s[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_s", ";s ;BCAL Shower #sigma_{#phi}",  300, 4, 17, 200, 0., 0.02);
                dHist_SigTrans_u[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_u", ";u ;BCAL Shower #sigma_{#phi}",  300, 2, 15, 200, 0., 0.02);

                dHist_SigTrans_MMS[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_MMS", ";MMS ;BCAL Shower #sigma_{#phi}",  300, -0.5, 0.5, 200, 0., 0.02);
                dHist_SigTrans_ME[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_ME", ";ME ;BCAL Shower #sigma_{#phi}",  300, -1, 3, 200, 0., 0.02);

                dHist_SigTrans_VertexZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_VertexZ", ";VertexZ ;BCAL Shower #sigma_{#phi}",  300, 45, 80, 200, 0., 0.02);
                dHist_SigTrans_VertexR[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_VertexR", ";VertexR ;BCAL Shower #sigma_{#phi}",  300, -1, 1, 200, 0., 0.02);

                dHist_SigTrans_dEdxCDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_dEdxCDC", ";dEdXCDC ;BCAL Shower #sigma_{#phi}",  300, 0, 6, 200, 0., 0.02);
                dHist_SigTrans_dEdxFDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_dEdxFDC", ";dEdxFDC ;BCAL Shower #sigma_{#phi}",  300, -1, 1, 200, 0., 0.02);

                dHist_SigTrans_EPreEShower[locRFBin] = new TH2F("SigTrans_EPreEShower", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#phi}",  300, 0, 1, 200, 0., 0.02);
                dHist_SigTrans_EPreEShower_varyMore[locRFBin] = new TH2F("SigTrans_EPreEShower_varyMore", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#phi}",  300, 0, 1, 200, 0., 0.02);


dHist_EPre_EShower_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"EPreEShower_PhotonThetaDet", ";Energy PreShower/Energy Shower ;PhotonThetaDet",  300, 0, 4, 200, 10, 35);
                dHist_EPreShower_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"EPreShower_PhotonThetaDet", ";Energy PreShower ;PhotonThetaDet",  300, 0, 4, 200, 10, 35);

                dHist_EPre_EShower_PhotonThetaDet_varyMore[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"EPreEShower_PhotonThetaDet_varyMore", ";Energy PreShower/Energy Shower ;PhotonThetaDet",  300, 0, 4, 200, 10, 35);
                dHist_EPreShower_PhotonThetaDet_varyMore[locRFBin]  = new TH2F(locRFBinLabel[locRFBin]+"EPreShower_PhotonThetaDet_varyMore", ";Energy PreShower ;PhotonThetaDet",  300, 0, 4, 200, 10, 35);




                dHist_SigTrans_SigTheta_varyLess_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyLess PhotonThetaDet", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                dHist_SigTrans_SigTheta_varyMore_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyMore PhotonThetaDet", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                dHist_SigTrans_SigTheta_varyLess_ME[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyLess ME", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                dHist_SigTrans_SigTheta_varyMore_ME[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyMore ME", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);
                dHist_SigTrans_SigTheta_varyLess_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyLess PBCALPreShower", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);
                dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigTheta varyMore PBCALPreShower", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.05, 200, 0., 0.02);
                dHist_SigLong_SigTheta_varyLess_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong SigTheta varyLess PBCALPreShower", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#rho}", 200, 0., 0.005, 300, 0., 10.);
                dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong SigTheta varyMore PBCALPreShower", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#rho}", 200, 0., 0.005, 300, 0., 10.);
                dHist_SigTrans_SigLong_varyLess_PBCALPreShowerE[locRFBin]= new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigLong varyLess PBCALPreShower", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0., 10, 200, 0., 0.02);
                dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans SigLong varyMore PBCALPreShower", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0., 10, 200, 0., 0.02);
                
                dHist_SigTrans_PhotonThetaDet_varyLess_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans PhotonThetaDet varyLess", "; PhotonThetaDet; BCAL Shower #sigma_{#phi}", 200, 10., 35, 200, 0., 0.02);
                dHist_SigTrans_PhotonThetaDet_varyMore_PBCALPreShowerE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans PhotonThetaDet varyMore", "; PhotonThetaDet; BCAL Shower #sigma_{#phi}", 200, 10., 35., 200, 0., 0.02);



                dHist_BCALSigTrans_SigLong_Normal[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigLong_Normal", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);
                dHist_BCALSigTrans_SigTheta_Normal[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Normal", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);

                dHist_BCALSigLong_SigTheta_Normal[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_SigTheta_Normal", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#rho}", 200, 0., 0.02, 200, 0., 10.);

                dHist_BCALSigTrans_SigLong_Normal_cutsApplied[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigLong_Normal_cutsApplied", "; BCAL Shower #sigma_{#rho}; BCAL Shower #sigma_{#phi}", 300, 0, 10, 200, 0., 0.02);
                dHist_BCALSigTrans_SigTheta_Normal_cutsApplied[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Normal_cutsApplied", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);

                dHist_BCALSigLong_SigTheta_Normal_cutsApplied[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_SigTheta_Normal_cutsApplied", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#rho}", 200, 0., 0.02, 200, 0., 10.);


                dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong_varyMore_PBCALPreShowerE", ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_105_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.05_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_105_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.05_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_11_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.1_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_11_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.1_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                
                dHist_SigTrans_varyMore_115_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.15_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_115_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.15_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_12_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.2_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_12_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.2_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_125_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.25_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_125_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.25_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                dHist_SigTrans_varyMore_13_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_1.3_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_13_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_1.3_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);



                dHist_SigTrans_varyMore_80_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.80_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_80_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.80_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_825_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.825_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_825_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.825_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_85_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.85_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_85_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.85_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_875_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.875_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_875_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.875_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                
                dHist_SigTheta_varyMore_90_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.90_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_925_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.925_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_925_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.925_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_95_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.95_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_95_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.95_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTrans_varyMore_975_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyMore_.975_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigTheta_varyMore_975_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore_.975_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);



                dHist_SigTheta_varyMore_piCut_0013_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.0013_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_00125_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.00125_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                dHist_SigTheta_varyMore_piCut_0012_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.0012_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_00115_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.00115_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_0011_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.0011_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                dHist_SigTheta_varyMore_piCut_00105_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.00105_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);
                
                dHist_SigTheta_varyMore_piCut_001_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.001_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_00095_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.00095_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_0009_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.0009_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_SigTheta_varyMore_piCut_00075_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyMore__piCut_.00075_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);


                dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE_Scale[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTrans_SigTheta_Scale", "; BCAL Shower #sigma_{#theta}; BCAL Shower #sigma_{#phi}", 200, 0., 0.02, 200, 0., 0.02);



                dHist_SigTrans_varyLess_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans_varyLess_PBCALPreShowerE" , ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 0.03);
                dHist_SigLong_varyLess_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong_varyLess_PBCALPreShowerE", ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 30);
                dHist_SigTheta_varyLess_PBCALPreShowerE[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta_varyLess_PBCALPreShowerE", ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 0.004);

                dHist_EPreEShower_EPreShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EPreEShower EPreShower", ";EPre/EShower; EPreShower", 300, 0, 1, 200, 0, 4);
                dHist_EPreEShower_EShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EPreEShower EShower", ";EPre/EShower; EShower", 300, 0, 1, 200, 0, 7);

                dHist_EPreEShower_EPreShower_varyMore[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EPreEShower EPreShower_varyMore", ";EPre/EShower; EPreShower", 300, 0, 1, 200, 0, 4);
                dHist_EPreEShower_EShower_varyMore[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EPreEShower EShower_varyMore", ";EPre/EShower; EShower", 300, 0, 1, 200, 0, 7);

                dHist_EShower_EPreShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EShower EPreShower", ";EShower; EPreShower", 300, 0, 6, 200, 0, 4);
                dHist_EShower_EPreShower_varyMore[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+ "EShower EPreShower_varyMore", ";EShower; EPreShower", 300, 0, 6, 200, 0, 4);

                dHist_Delta_Phi[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+"Delta_Phi_1D", "; #Delta#phi; Counts", 300, 80, 300);
                dHist_Delta_Phi[locRFBin]->Fill(-1000,1); dHist_Delta_Phi[locRFBin]->Fill(1000,1);

                dHist_Delta_Energy_O[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+"Delta_Energy_1D_O", "; #Delta E; Counts", 300, 2, -7);
                dHist_Delta_Energy_O[locRFBin]->Fill(-1000,1); dHist_Delta_Energy_O[locRFBin]->Fill(1000,1);
                
                dHist_Delta_Energy_Up[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+"Delta_Energy_1D_Up", "; #Delta E: Counts", 300, 2, -7);
                dHist_Delta_Energy_Up[locRFBin]->Fill(-1000,1); dHist_Delta_Energy_Up[locRFBin]->Fill(1000,1);

                dHist_Delta_Theta_Up[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+"Delta_Theta_1D_Up", "; #Delta#theta; Counts", 300, -30, 30);
                dHist_Delta_Theta_Up[locRFBin]->Fill(-1000,1); dHist_Delta_Theta_Up[locRFBin]->Fill(1000,1);


                dHist_DeltaPhi_t[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"DeltaPhi_t", "; -t (GeV^2); #Delta#phi (degrees)", 250, 0., 5., 200, 170., 190.);

                dHist_DeltaPhi_t[locRFBin]->Fill(-1,-1,1); dHist_DeltaPhi_t[locRFBin]->Fill(1000,-1,1); dHist_DeltaPhi_t[locRFBin]->Fill(-1,1000,1); dHist_DeltaPhi_t[locRFBin]->Fill(-1,180.0,1); dHist_DeltaPhi_t[locRFBin]->Fill(2.5,-1,1); dHist_DeltaPhi_t[locRFBin]->Fill(1000,1000,1); dHist_DeltaPhi_t[locRFBin]->Fill(1000,180.0,1); dHist_DeltaPhi_t[locRFBin]->Fill(2.5,1000,1);


                //TO FIX THE OVERFLOW
                //
//              dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.015,-1,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);

//              dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.015,-1,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);

//              dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.015,-1,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);
                dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1000,1); dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1);
                dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1000,1); dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1);
                dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1000,1); dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1);
                
                dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.0015,-1,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);

                dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.015,-1,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);

                dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,1000,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(-1,0.001,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.015,-1,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,1000,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(1000,0.015,1); dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(0.025,1000,1);
                }

                cv2Dir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                dHist_SigTheta_PhotonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PhotonP", ";PhotonP; BCAL Shower #sigma_{#theta}; PhotonP", 300, 0, 8, 200, 0., 0.006);
                dHist_SigTheta_PhotonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PhotonTheta", ";Photon#theta; BCAL Shower #sigma_{#theta}", 300, 10, 35, 200, 0., 0.006);
                dHist_SigTheta_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PhotonThetaDet", ";Photon#thetaDet BCAL; Shower #sigma_{#theta}",  300, 10, 35, 200, 0., 0.006);
                dHist_SigTheta_PhotonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PhotonPhi", ";Photon#phi ;BCAL Shower #sigma_{#theta}",  300, 0, 200, 200, 0., 0.006);
                dHist_SigTheta_ProtonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ProtonP", "; ProtonP; BCAL Shower #sigma_{#theta}", 300, 0, 6, 200, 0., 0.006);
                dHist_SigTheta_ProtonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ProtonTheta", "; Proton#theta; BCAL Shower #sigma_{#theta}", 300, 20, 70, 200, 0., 0.006);
                dHist_SigTheta_ProtonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ProtonPhi", ";Proton#phi ;BCAL Shower #sigma_{#theta}",  300, 0, 200, 200, 0., 0.006);
                dHist_SigTheta_ProtonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ProtonThetaDet", ";Proton#thetaDet BCAL; Shower #sigma_{#theta}",  300, 0, 50, 200, 0., 0.006);
                
                dHist_SigTheta_PhotonBCALShowerZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PhotonBCALShowerZ", ";PhotonBCALShowerZ ;BCAL Shower #sigma_{#theta}",  300, 150, 450, 200, 0., 0.006);
                dHist_SigTheta_ThetaCM[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ThetaCM", ";ThetaCM ;BCAL Shower #sigma_{#v}",  300, 25, 100, 200, 0., 0.006);

                dHist_SigTheta_DeltaTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_DetlaTheta", ";#Delta#theta ;BCAL Shower #sigma_{#theta}",  300, -10, 10, 200, 0., 0.006);
                dHist_SigTheta_DeltaE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_DeltaE", ";#DeltaE ;BCAL Shower #sigma_{#theta}",  300, -3, 3, 200, 0., 0.006);
                dHist_SigTheta_DeltaPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_DeltaPhi", ";#Delta#phi ;BCAL Shower #sigma_{#theta}",  300, 150, 200, 200, 0., 0.006);

                dHist_SigTheta_PBCALPreShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PBCALPreShower", ";Photon BCAL Pre Shower ;BCAL Shower #sigma_{#theta}",  300, 0, 4, 200, 0., 0.006);
                dHist_SigTheta_PBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PBCALSE", ";Photon BCAL Shower E ;BCAL Shower #sigma_{#theta}",  300, 2, 7, 200, 0., 0.006);
                dHist_SigTheta_PrBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PrBCALSE", ";Proton BCAL Shower E ;BCAL Shower #sigma_{#theta}",  300, 0, 2, 200, 0., 0.006);
                dHist_SigTheta_PFCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_PFCALSE", ";Photon FCAL Shower E ;BCAL Shower #sigma_{#theta}",  300, -1, 1, 200, 0., 0.006);

                dHist_SigTheta_t[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_t", ";t ;BCAL Shower #sigma_{#theta}",  300, 0, 6, 200, 0., 0.006);
                dHist_SigTheta_s[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_s", ";s ;BCAL Shower #sigma_{#theta}",  300, 4, 17, 200, 0., 0.006);
                dHist_SigTheta_u[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_u", ";u ;BCAL Shower #sigma_{#theta}",  300, 2, 15, 200, 0., 0.006);
                
                dHist_SigTheta_MMS[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_MMS", ";MMS ;BCAL Shower #sigma_{#theta}",  300, -0.5, 0.5, 200, 0., 0.006);
                dHist_SigTheta_ME[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_ME", ";ME ;BCAL Shower #sigma_{#theta}",  300, -1, 3, 200, 0., 0.006);

                dHist_SigTheta_VertexZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_VertexZ", ";VertexZ ;BCAL Shower #sigma_{#theta}",  300, 45, 80, 200, 0., 0.006);
                dHist_SigTheta_VertexR[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_VertexR", ";VertexR ;BCAL Shower #sigma_{#theta}",  300, -1, 1, 200, 0., 0.006);

                dHist_SigTheta_dEdxCDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_dEdxCDC", ";dEdXCDC ;BCAL Shower #sigma_{#theta}",  300, 0, 6, 200, 0., 0.006);
                dHist_SigTheta_dEdxFDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigTheta_dEdxFDC", ";dEdxFDC ;BCAL Shower #sigma_{#theta}",  300, -1, 1, 200, 0., 0.006);

                dHist_SigTheta_EPreEShower[locRFBin] = new TH2F("SigTheta_EPreEShower", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#theta}",  300, 0, 1, 200, 0., 0.006);
                dHist_SigTheta_EPreEShower_varyMore[locRFBin] = new TH2F("SigTheta_EPreEShower_varyMore", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#theta}",  300, 0, 1, 200, 0., 0.006);

                }

                cv3Dir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++) {
                dHist_SigLong_PhotonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PhotonP", ";PhotonP; BCAL Shower #sigma_{#rho}; PhotonP", 300, 0, 8, 200, 0., 10.);
                dHist_SigLong_PhotonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PhotonTheta", ";Photon#theta; BCAL Shower #sigma_{#rho}", 300, 10, 35, 200, 0., 10.);
                dHist_SigLong_PhotonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PhotonThetaDet", ";Photon#thetaDet BCAL; Shower #sigma_{#rho}",  300, 10, 35, 200, 0., 10.);
                dHist_SigLong_PhotonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PhotonPhi", ";Photon#phi ;BCAL Shower #sigma_{#rho}",  300, 0, 200, 200, 0., 10.);
                dHist_SigLong_ProtonP[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ProtonP", "; ProtonP; BCAL Shower #sigma_{#rho}", 300, 0, 6, 200, 0., 10.);
                dHist_SigLong_ProtonTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ProtonTheta", "; Proton#theta; BCAL Shower #sigma_{#rho}", 300, 20, 70, 200, 0., 10.);
                dHist_SigLong_ProtonPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ProtonPhi", ";Proton#phi ;BCAL Shower #sigma_{#rho}",  300, 0, 200, 200, 0., 10.);
                dHist_SigLong_ProtonThetaDet[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ProtonThetaDet", ";Proton#thetaDet BCAL; Shower #sigma_{#rho}",  300, 0, 50, 200, 0., 10.);

                dHist_SigLong_PhotonBCALShowerZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PhotonBCALShowerZ", ";PhotonBCALShowerZ ;BCAL Shower #sigma_{#rho}",  300, 150, 450, 200, 0., 10.);
                dHist_SigLong_ThetaCM[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ThetaCM", ";ThetaCM ;BCAL Shower #sigma_{#rho}",  300, 25, 100, 200, 0., 10.);

                dHist_SigLong_DeltaTheta[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_DetlaTheta", ";#Delta#theta ;BCAL Shower #sigma_{#rho}",  300, -10, 10, 200, 0., 10.);


dHist_SigLong_DeltaE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_DeltaE", ";#DeltaE ;BCAL Shower #sigma_{#rho}",  300, -3, 3, 200, 0., 10.);
                dHist_SigLong_DeltaPhi[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_DeltaPhi", ";#Delta#phi ;BCAL Shower #sigma_{#rho}",  300, 150, 200, 200, 0., 10.);

                dHist_SigLong_PBCALPreShower[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PBCALPreShower", ";Photon BCAL Pre Shower ;BCAL Shower #sigma_{#rho}",  300, 0, 4, 200, 0., 10.);
                dHist_SigLong_PBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PBCALSE", ";Photon BCAL Shower E ;BCAL Shower #sigma_{#rho}",  300, 2, 7, 200, 0., 10.);
                dHist_SigLong_PrBCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PrBCALSE", ";Proton BCAL Shower E ;BCAL Shower #sigma_{#rho}",  300, 0, 2, 200, 0., 10.);
                dHist_SigLong_PFCALSE[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_PFCALSE", ";Photon FCAL Shower E ;BCAL Shower #sigma_{#rho}",  300, -1, 1, 200, 0., 10.);

                dHist_SigLong_t[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_t", ";t ;BCAL Shower #sigma_{#rho}",  300, 0, 6, 200, 0., 10.);
                dHist_SigLong_s[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_s", ";s ;BCAL Shower #sigma_{#rho}",  300, 4, 17, 200, 0., 10.);
                dHist_SigLong_u[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_u", ";u ;BCAL Shower #sigma_{#rho}",  300, 2, 15, 200, 0., 10.);

                dHist_SigLong_MMS[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_MMS", ";MMS ;BCAL Shower #sigma_{#rho}",  300, -0.5, 0.5, 200, 0., 10.);
                dHist_SigLong_ME[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_ME", ";ME ;BCAL Shower #sigma_{#rho}",  300, -1, 3, 200, 0., 10.);

                dHist_SigLong_VertexZ[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_VertexZ", ";VertexZ ;BCAL Shower #sigma_{#rho}",  300, 45, 80, 200, 0., 10.);
                dHist_SigLong_VertexR[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_VertexR", ";VertexR ;BCAL Shower #sigma_{#rho}",  300, -1, 1, 200, 0., 10.);

                dHist_SigLong_dEdxCDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_dEdxCDC", ";dEdXCDC ;BCAL Shower #sigma_{#rho}",  300, 0, 6, 200, 0., 10.);
                dHist_SigLong_dEdxFDC[locRFBin] = new TH2F(locRFBinLabel[locRFBin]+"SigLong_dEdxFDC", ";dEdxFDC ;BCAL Shower #sigma_{#rho}",  300, -1, 1, 200, 0., 10.);

                dHist_SigLong_EPreEShower[locRFBin] = new TH2F("SigLong_EPreEShower", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#rho}",  300, 0, 1, 200, 0., 10.);
                dHist_SigLong_EPreEShower_varyMore[locRFBin] = new TH2F("SigLong_EPreEShower_varyMore", ";Energy PreShower/Energy Shower ;BCAL Shower #sigma_{#rho}",  300, 0, 1, 200, 0., 10.);

}
                cv4Dir->cd();
        for(int locRFBin=0; locRFBin<2; locRFBin++){
                dHist_dPhi_Final[locRFBin] = new TH1F(locRFBinLabel[locRFBin]+"Delta_Phi_Final", "; #Delta#phi; Counts", 300, 80, 300);
        }




//-------------------------------------------------------------------TO COMMENT OUT ALL OF THE FILLING FOR BUG FIXES------------------------------------------------------


}
                //dHist_SigLong[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigLong Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#rho}; Counts", 300, 0, 10);
                //dHist_SigTrans[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTrans Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#phi}; Counts", 300, 0, 10);
                //dHist_SigTheta[locRFBin][locBeamEBin] = new TH1F(locRFBinLabel[locRFBin]+ "SigTheta Yield2" + locBeamEBinLabel[locBeamEBin], ";BCAL Shower #sigma_{#theta}; Counts", 300, 0, 10);             
Bool_t DSelector_compton::Process(Long64_t locEntry)
{


// The Process() function is called for each entry in the tree. The entry argument
        // specifies which entry in the currently loaded tree is to be processed.
        //
        // This function should contain the "body" of the analysis. It can contain
        // simple or elaborate selection criteria, run algorithms on the data
        // of the event and typically fill histograms.
        //
        // The processing can be stopped by calling Abort().
        // Use fStatus to set the return value of TTree::Process().
        // The return value is currently not used.

        //CALL THIS FIRST
        DSelector::Process(locEntry); //Gets the data from the tree for the entry

        /******************************************** GET POLARIZATION ORIENTATION ******************************************/
        //Only if the run number changes
        //RCDB environment must be setup in order for this to work! (Will return false otherwise)
        UInt_t locRunNumber = Get_RunNumber();
        if(locRunNumber != dPreviousRunNumber)
        {
                dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
                dPreviousRunNumber = locRunNumber;
        }

        /********************************************* SETUP UNIQUENESS TRACKING ********************************************/

        //ANALYSIS ACTIONS: Reset uniqueness tracking for each action
        //For any actions that you are executing manually, be sure to call Reset_NewEvent() on them here
        Reset_Actions_NewEvent();

        //PREVENT-DOUBLE COUNTING WHEN HISTOGRAMMING
                //Sometimes, some content is the exact same between one combo and the next
                        //e.g. maybe two combos have different beam particles, but the same data for the final-state
                //When histogramming, you don't want to double-count when this happens: artificially inflates your signal (or background)
                //So, for each quantity you histogram, keep track of what particles you used (for a given combo)
                //Then for each combo, just compare to what you used before, and make sure it's unique

        //EXAMPLE 1: Particle-specific info:
        set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search
        //EXAMPLE 2: Combo-specific info:
                //In general: Could have multiple particles with the same PID: Use a set of Int_t's
                //In general: Multiple PIDs, so multiple sets: Contain within a map
                //Multiple combos: Contain maps within a set (easier, faster to search)
        set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;
        set<Int_t> locUsedSoFar_Proton;
        //INSERT USER ANALYSIS UNIQUENESS TRACKING HERE

        /************************************************* LOOP OVER COMBOS *************************************************/

        //Loop over combos
        for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
        {
                //Set branch array indices for combo and all combo particles
                dComboWrapper->Set_ComboIndex(loc_i);

                // Is used to indicate when combos have been cut
                if(dComboWrapper->Get_IsComboCut()) // Is false when tree originally created
                        continue; // Combo has been cut previously

                /********************************************** GET PARTICLE INDICES *********************************************/

                //Used for tracking uniqueness when filling histograms, and for determining unused particles

                //Step 0
                Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
                Int_t locPhotonNeutralID = dPhotonWrapper->Get_NeutralID();
                Int_t locProtonTrackID = dProtonWrapper->Get_TrackID();
                //dHistogramAction = dHistogramAction_ParticleTD.Fill_Hists(const DKinematicData* locKinematicData, size_t locStepIndex);
                //-------------------------------------------------------------------TO COMMENT OUT ALL OF THE FILLING FOR BUG FIXES------------------------------------------------------      


/*              const DKinematicData* locKinematicData  
                Particle_t locPID = locKinematicData->Get_PID();
                if(ParticleCharge(locPID) !=0){
                const DChargedTrackHypothesis* locChargedTrackHypothesis = dynamic_cast<const DChargedTrackHypothesis*>(locKinematicData);
                if(locChargedTrackHypothesis->GetdEdx_CDC()>0.)
                        dHist_dEdx_p_CDC[RFBin][locBeamEBin]->Fill(locP,locChargedTrackHypothesis->Get_dEdx_CDC()*1e6);
*/              /*********************************************** GET FOUR-MOMENTUM **********************************************/


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// Get P4's: //is kinfit if kinfit performed, else is measured
                //dTargetP4 is target p4
                //Step 0
                TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
                TLorentzVector locPhotonP4 = dPhotonWrapper->Get_P4();
                TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();

                Double_t xx = locBeamP4.X();
                Double_t tt = locBeamP4.T();
                Double_t px = locBeamP4.Px();
                Double_t ee = locBeamP4.E();


                dHist_BeamP4xx->Fill(xx);
                dHist_BeamP4tt->Fill(tt);
                dHist_BeamP4px->Fill(px);
                dHist_BeamP4ee->Fill(ee);
                //dHist_PhotonP4->Fill(locPhotonP4);
                //dHist_ProtonP4->Fill(locProtonP4);
                //------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------              
// Get Measured P4's:
                //Step 0
                TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
                TLorentzVector locPhotonP4_Measured = dPhotonWrapper->Get_P4_Measured();
                TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();
                Double_t P4 = locProtonP4_Measured.X();
                dHist_BeamP4_Measured->Fill(P4);
                //dHist_PhotonP4_Measured->Fill(locPhotonP4_Measured);
                //dHist_ProtonP4_Measured->Fill(locProtonP4_Measured);

                TLorentzVector locBeamX4_Measured = dComboBeamWrapper->Get_X4_Measured();
                TLorentzVector locPhotonX4_Measured = dPhotonWrapper->Get_X4_Shower();
                TLorentzVector locProtonX4_Measured = dProtonWrapper->Get_X4_Measured();
                Float_t locTrackBCAL_DeltaPhi = dPhotonWrapper->Get_TrackBCAL_DeltaPhi();
                Float_t locTrackBCAL_DeltaZ = dPhotonWrapper->Get_TrackBCAL_DeltaZ();
                Float_t locTrackFCAL_DOCA = dPhotonWrapper->Get_TrackFCAL_DOCA();

                Float_t locChiSq_timing = dProtonWrapper->Get_ChiSq_Timing();
                Float_t locChiSq_tracking = dProtonWrapper->Get_ChiSq_Tracking();

                Double_t X4 = locProtonX4_Measured.X();

                //dHist_BeamX4_Measured->Fill(locBeamX4_Measured);
                //dHist_PhotonX4_Measured->Fill(locPhotonX4_Measured);
                //dHist_ProtonX4_Measured->Fill(locProtonX4_Measured);

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------              
// Get Shower Energy:

double locPhotonBCALPreShowerE = dPhotonWrapper->Get_Energy_BCALPreshower();
                double locPhotonBCALShowerE = dPhotonWrapper->Get_Energy_BCAL();
                double locProtonBCALShowerE = dProtonWrapper->Get_Energy_BCAL();
                double locPhotonFCALShowerE = dPhotonWrapper->Get_Energy_FCAL();
                double locPhotonSigLongBCALShower = dPhotonWrapper->Get_SigLong_BCAL();
                double locPhotonSigThetaBCALShower = dPhotonWrapper->Get_SigTheta_BCAL();
                double locPhotonSigTransBCALShower = dPhotonWrapper->Get_SigTrans_BCAL();

                double locPhotonBCALShowerZ = locPhotonX4_Measured.Z();
                dHist_PhotonBCALShowerZ->Fill(locPhotonBCALShowerZ);

                dHist_PBCALPreShowerE->Fill(locPhotonBCALPreShowerE);
                dHist_PBCALShowerE->Fill(locPhotonBCALShowerE);
                dHist_PFCALShowerE->Fill(locPhotonFCALShowerE);
                dHist_PSLBCALShower->Fill(locPhotonSigLongBCALShower);
                dHist_PSTBCALShower->Fill(locPhotonSigThetaBCALShower);
                dHist_PSTrBCALShower->Fill(locPhotonSigTransBCALShower);

                double locEPre_EShower = locPhotonBCALPreShowerE/locPhotonBCALShowerE ;
                dHist_EPre_EShower->Fill(locEPre_EShower);
                //                double locEPre_EShower = locPhotonBCALPreShowerE*TMath::Power(locPhotonBCALShowerE, -1.);
//              dHist_SigTrans_EPreEShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonBCALShowerE);
                /******************************************** EXECUTE ANALYSIS ACTIONS *******************************************/

                // Loop through the analysis actions, executing them in order for the active particle combo
                if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
                        continue;

                //if you manually execute any actions, and it fails a cut, be sure to call:
                        //dComboWrapper->Set_IsComboCut(true);

                /********************************************* ACCIDENTALS & RF TIMING ********************************************/

                double locRFTime = dComboWrapper->Get_RFTime_Measured();
                double locBeamDeltaT = locBeamX4_Measured.T() - (locRFTime + (locProtonX4_Measured.Z() - dTargetCenter.Z())/29.9792458);
                double locDeltaT =  locBeamX4_Measured.T() - locRFTime;
                dHist_RFT->Fill(locRFTime);
                dHist_BDT->Fill(locBeamDeltaT);
                
                dHist_Deltat_Init->Fill(locBeamDeltaT);
                //dHist_Deltat_Init2->Fill(locBeamDeltaT);      

                int locRFBin = -1;
                if(fabs(locBeamDeltaT) < 0.5*4.008) locRFBin = 0;
                else if (fabs(locBeamDeltaT) > 4.008*0.5 || fabs(locBeamDeltaT) < 4.008*2.5) locRFBin = 1;
                else continue;
                dHist_Deltat_Init2[locRFBin]->Fill(locBeamDeltaT);

                //dHist_SigTrans_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigTransBCALShower);             
                //dHist_SigTheta_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigThetaBCALShower);
                //dHist_SigLong_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigLongBCALShower);               


                dHist_EPre___EShower[locRFBin]->Fill(locPhotonBCALShowerE,locPhotonBCALPreShowerE);
        /*
                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1);
                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1);

                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(1000,-1,1); dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(-1,1000,1);
*/
//              dHist_Deltat_Init[locRFBin][locBeamEBin]->Fill(locBeamDeltaT);
                //dHist_Deltat_Final[locRFBin]->Fill(locBeamDeltaT);

                /********************************************* KINEMATIC VARIABLES **********************************************/

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// Get COM P4's for scattering angle

TLorentzVector locInitialStateP4 = locBeamP4_Measured + dTargetP4;
                TVector3 locBoostVectorCM = -1.0*(locInitialStateP4.BoostVector());
                TLorentzVector locProtonP4_MeasuredCM = locProtonP4_Measured; locProtonP4_MeasuredCM.Boost(locBoostVectorCM);
                TLorentzVector locPhotonP4_MeasuredCM = locPhotonP4_Measured; locPhotonP4_MeasuredCM.Boost(locBoostVectorCM);


//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------              
// should directly be photon CM angle, but can't use that since BCAL saturates
                double locThetaCM = -1.*(locProtonP4_MeasuredCM.Theta()*180./TMath::Pi() - 180.);
                double loct = -1.*(dTargetP4 - locProtonP4_Measured).M2();
                double locu = -1.*(locBeamP4_Measured - locProtonP4_Measured).M2();
                double locs = (locPhotonP4_Measured + locProtonP4_Measured).M2();
                dHist_TCM->Fill(locThetaCM);
                dHist_loct->Fill(loct);
                dHist_locu->Fill(locu);
                dHist_locs->Fill(locs);
                /**************************************** HISTOGRAM BEAM ENERGY *****************************************/

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//Histogram beam energy (if haven't already)
        //      dHist_BeamEnergy_Init[locRFBin]->Fill(locBeamP4.E());
                if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
                {
                        dHist_BeamEnergy_Final[locRFBin]->Fill(locBeamP4.E());
                        locUsedSoFar_BeamEnergy.insert(locBeamID);
                }

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
// cut low energy beam photons and make bins for Egamma (in arrays below)

 if(locBeamP4.E() < 5.0)
                        continue;
                dHist_BeamEnergy_Init[locRFBin]->Fill(locBeamP4.E());

                int locBeamEBin = 0;
                if(locBeamP4.E() > 6. && locBeamP4.E() < 7.)  locBeamEBin = 1;
                if(locBeamP4.E() > 7. && locBeamP4.E() < 8.4)  locBeamEBin = 2;
                if(locBeamP4.E() > 8.4 && locBeamP4.E() < 9) locBeamEBin = 3;
                if(locBeamP4.E() > 9.)  locBeamEBin = 4;


                dHist_Deltat_Final[locRFBin][locBeamEBin]->Fill(locBeamDeltaT);
                //      dHist_Deltat_Final->Fill(locBeamDeltaT); 
                /********************************************* FIXING 2017 BACKGROUND DATA PRECUT  ********************************************/

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
                TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
                locMissingP4_Measured -= locPhotonP4_Measured + locProtonP4_Measured;
                double locMissingMassSquared = locMissingP4_Measured.M2();
                double locMissingEnergy = locMissingP4_Measured.E();

                map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
                locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
                locUsedThisCombo_MissingMass[Gamma].insert(locPhotonNeutralID);
                locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);

                // if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
                //{
                        //unique missing mass combo: histogram it, and register this combo of particles
                        locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
                        dHist_MissingEnergyPreCut[locRFBin][locBeamEBin]->Fill(locMissingEnergy);
                        dHist_MissingMassSquaredPreCut[locRFBin][locBeamEBin]->Fill(locMissingMassSquared);
                //}


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------        
//Combine four vector here to use the new if statement tree
                TLorentzVector locPhotonP4_Missing_Measured = locBeamP4_Measured + dTargetP4;
                locPhotonP4_Missing_Measured -= locProtonP4_Measured;
                TLorentzVector locProtonP4_Missing_Measured = locBeamP4_Measured + dTargetP4;
                locProtonP4_Missing_Measured -=locPhotonP4_Measured;
                double locDeltaPhi = (locPhotonP4_Measured.Phi() - locProtonP4_Measured.Phi())*180./TMath::Pi();
                dHist_DeltaPhiPreCut[locRFBin][locBeamEBin]->Fill(locDeltaPhi);
                double locDeltaTheta = (locPhotonP4_Measured.Theta() - locPhotonP4_Missing_Measured.Theta())*180./TMath::Pi();
                double locDeltaE = locPhotonBCALShowerE - locPhotonP4_Missing_Measured.E();

                /********************************************* FIDUCIAL AND VERTEX CUTS ********************************************/

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
                double locPhotonP = locPhotonP4_Measured.P();
                double locPhotonTheta = locPhotonP4_Measured.Theta()*180./TMath::Pi();
                double locPhotonThetaDet = (locPhotonX4_Measured.Vect()-dTargetCenter).Theta()*180./TMath::Pi();
                double locPhotonPhi = locPhotonP4_Measured.Phi()*180./TMath::Pi();
                dHist_Photonp->Fill(locPhotonP);
                dHist_Photont->Fill(locPhotonTheta);
                dHist_Photontdelta->Fill(locPhotonThetaDet);

                dHist_TrackBCAL_DeltaPhi->Fill(locTrackBCAL_DeltaPhi);
                dHist_TrackBCAL_DeltaZ->Fill(locTrackBCAL_DeltaZ);
                dHist_TrackFCAL_DOCA->Fill(locTrackFCAL_DOCA);

                double locVertexZ = locProtonX4_Measured.Z();
                dHist_VertZ->Fill(locVertexZ);

                dHist_VertexZ_Init[locRFBin][locBeamEBin]->Fill(locVertexZ);
                if(locVertexZ < 51. || locVertexZ > 76.) continue;
                dHist_VertexZ_Final[locRFBin][locBeamEBin]->Fill(locVertexZ);
                
                double locVertexR = locProtonX4_Measured.Perp();
                dHist_VertR->Fill(locVertexR);

                dHist_VertexR_Init[locRFBin][locBeamEBin]->Fill(locVertexR);
                //if(locVertexR > 1.45) continue;
                if(locVertexR > 0.8) continue;
                dHist_VertexR_Final[locRFBin][locBeamEBin]->Fill(locVertexR);

                dHist_PhotonP_Theta_Init[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonP);
                if(locPhotonThetaDet < 2.5 || (locPhotonThetaDet > 10.3 && locPhotonThetaDet < 11.5)) continue;
                //dHist_PhotonP_Theta_Final[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonP);
                //dHist_PhotonTheta_ThetaDet_Init[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonTheta);
                if(locPhotonBCALShowerE > 0.) {
                        dHist_PhotonTheta_ThetaDet_Init[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonTheta);
                        if(locPhotonTheta < 10.5)
                                continue; // remove BCAL showers with wrong measured theta 
                }


                double locProtonP = locProtonP4_Measured.P();
                double locProtonTheta = locProtonP4_Measured.Theta()*180./TMath::Pi();
                double locProtonPhi = locProtonP4_Measured.Phi()*180./TMath::Pi();
                double locProtonPhi11 = locProtonP4_Measured.Phi()*180./TMath::Pi();
                double locProtonPhi2 = locProtonP4_Measured.Phi()*180./TMath::Pi();
                double locProtonPhi22 = locProtonP4_Measured.Phi()*180./TMath::Pi();
                double locProtonThetaDet = (locProtonX4_Measured.Vect()-dTargetCenter).Theta()*180./TMath::Pi();
                
                /*dHistoAction = dHistogramActions.Fill_Hists(locKinematicData,locStepIndex){
                //const DKinematicData* locKinematicData
                Particle_t locPID = locKinematicData->Get_PID();
                if(ParticleCharge(locPID) !=0){
                const DChargedTrackHypothesis* locChargedTrackHypothesis = dynamic_cast<const DChargedTrackHypothesis*>(locKinematicData);
                if(locChargedTrackHypothesis->Get_dEdx_CDC()>0.)
                        dHist_dEdx_p_CDC[locRFBin][locBeamEBin]->Fill(locProtonP,locChargedTrackHypothesis->Get_dEdx_CDC()*1e6);
                }}*/
                Float_t locdEdxCDC= dProtonWrapper->Get_dEdx_CDC();
                Float_t locdEdxFDC= dProtonWrapper->Get_dEdx_FDC();

                dHist_dEdx_p_CDC_Init[locRFBin][locBeamEBin]->Fill(locProtonP, locdEdxCDC*1e6);
                dHist_dEdx_p_FDC_Init[locRFBin][locBeamEBin]->Fill(locProtonP, locdEdxFDC*1e6);


                //dHist_Protonp->Fill(locProtonP);
                dHist_Protont->Fill(locPhotonTheta);
                //dHist_ProtonPhi->Fill(locProtonPhi);
                /*************************************************************************************************/
                dHist_Chisq_timing[locRFBin][locBeamEBin]->Fill(locChiSq_timing);
                dHist_Chisq_tracking[locRFBin][locBeamEBin]->Fill(locChiSq_tracking);

//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
// Draws histograms based off of cuts to Delta-Phi (whether <1.5 or >1.5)

dHist_BCALSigTrans_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigTrans_SigLong_Normal[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigLong_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);

                int locCutCounter2 = 0;
                int locCutView;
//#if 0
                if(locCutCounter2 == 0){
                        if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
                                if(locDeltaPhi > 360.) locDeltaPhi -= 360.;
                                if(locDeltaPhi < 0.) locDeltaPhi += 360.;
                                dHist_Shower_FCALpre[locRFBin][locCutView]->Fill(locPhotonFCALShowerE);
                                dHist_Shower_BCALpre[locRFBin][locCutView]->Fill(locPhotonBCALShowerE);
                                dHist_ProtonPhi_O_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                dHist_ProtonPhi_O_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                dHist_ProtonPhi_O_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                dHist_ProtonPhi_O_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                if(locPhotonFCALShowerE >0.){
                                        dHist_Shower_FCALpost[locRFBin][locCutView]->Fill(locPhotonFCALShowerE);
                                        dHist_ProtonPhi_Shower_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                        dHist_ProtonPhi_Shower_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                        dHist_DeltaPhiFCALpre[locRFBin][locCutView]->Fill(locDeltaPhi);
                                        if(locDeltaPhi-180){
                                                dHist_DeltaPhiFCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                dHist_DeltaPhi_L5FCALpre[locRFBin][locCutView]->Fill(locDeltaPhi);
                                        dHist_DeltaPhi_G5FCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                if(fabs(locDeltaPhi-180)<1.5){
                                                        dHist_DeltaPhi_L5FCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                        dHist_ProtonPhi_dPhi5_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                        dHist_DeltaE_Theta_FCALpre[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                        if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2.) {
                                                                dHist_ProtonPhi_dTheta_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                dHist_DeltaE_Theta_FCALpost[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                                dHist_SigTrans_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        //dHist_ProtonPhi_dTheta_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                if(locPhotonSigTransBCALShower < 0.0035){
                                                                        dHist_SigTrans_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        dHist_ProtonPhi_SigTrans_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                        dHist_SigTheta_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                //dHist_ProtonPhi_SigTrans_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                                if(locPhotonSigThetaBCALShower > 0.04){
                                                                                dHist_ProtonPhi_SigTheta_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                                dHist_SigLong_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                dHist_SigTheta_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                        //dHist_ProtonPhi_SigTheta_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                                if(locPhotonSigLongBCALShower < 1.){
                                                                                        dHist_SigLong_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                        dHist_ProtonPhi_SigLong_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                                        }}}}}

                                                if(fabs(locDeltaPhi-180)>1.5){
                                                        dHist_DeltaPhi_G5FCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                        dHist_ProtonPhi_5dPhi_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                        dHist_ProtonPhi_5dPhi_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                        dHist_ProtonPhi_5dPhi_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                        dHist_ProtonPhi_5dPhi_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                        dHist_DeltaE_Theta_FCALpre[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                                if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2){
                                                                        //dHist_ProtonPhi_dTheta_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                        dHist_DeltaE_Theta_FCALpost[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                                        dHist_SigTrans_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        dHist_ProtonPhi_dTheta_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                        if(locPhotonSigTransBCALShower < 0.0035){
                                                                                //dHist_ProtonPhi_SigTrans_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                                dHist_SigTrans_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                                dHist_SigTheta_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                dHist_ProtonPhi_SigTrans_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                                if(locPhotonSigThetaBCALShower > 0.04){
                                                                                        //dHist_ProtonPhi_SigTheta_F[locRFBin][locCutCounter2]->Fill(locProtonPhi);
                                                                                        dHist_SigLong_FCALpre[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                        dHist_ProtonPhi_SigTheta_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                                        dHist_SigTheta_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                        if(locPhotonSigLongBCALShower < 1.){
                                                                                                dHist_SigLong_FCALpost[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);    
                                                                                                dHist_ProtonPhi_SigLong_F2[locRFBin][locCutCounter2]->Fill(locProtonPhi11);
                                                                                        }}}}}}}

if(locPhotonBCALShowerE > 0.){
                                        dHist_Shower_BCALpost[locRFBin][locCutView]->Fill(locPhotonBCALShowerE);
                                        dHist_ProtonPhi_Shower_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                        dHist_ProtonPhi_Shower_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                        dHist_DeltaPhiBCALpre[locRFBin][locCutView]->Fill(locDeltaPhi);
                                        if(locDeltaPhi-180){
                                                dHist_DeltaPhiBCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                dHist_DeltaPhi_L5BCALpre[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                dHist_DeltaPhi_G5BCALpre[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                if(fabs(locDeltaPhi-180)<1.5){
                                                        dHist_ProtonPhi_dPhi5_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                        dHist_DeltaE_Theta_BCALpre[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                        dHist_DeltaPhi_L5BCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                        if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2){
                                                                dHist_DeltaE_Theta_BCALpost[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                                dHist_ProtonPhi_dTheta_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                dHist_SigTrans_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        //dHist_SigTransYield[locRFBin][locBeamEBin]->Fill(locPhotonSigTransBCALShower);
                                                                        //dHist_SigThetaYield[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower);
                                                                        //dHist_SigLongYield[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower);
                                                                if(locPhotonSigTransBCALShower < 0.0035){
                                                                        dHist_ProtonPhi_SigTrans_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                        dHist_SigTrans_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        dHist_SigTheta_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                //dHist_ProtonPhi_SigTrans_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                        if(locPhotonSigThetaBCALShower > 0.04){
                                                                                dHist_ProtonPhi_SigTheta_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                                        //dHist_ProtonPhi_SigTheta_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                                dHist_SigTheta_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                dHist_SigLong_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                if(locPhotonSigLongBCALShower < 1.){
                                                                                dHist_SigLong_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);                                                                                                                                         //dHist_ProtonPhi_SigLong_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                                        }}}}}
                                                                                        if(fabs(locDeltaPhi-180)>1.5){
                                                        dHist_DeltaPhi_G5FCALpost[locRFBin][locCutView]->Fill(locDeltaPhi);
                                                        dHist_ProtonPhi_5dPhi_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                        dHist_DeltaE_Theta_BCALpre[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                        if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2){
                                                        //dHist_ProtonPhi_dTheta_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                dHist_DeltaE_Theta_BCALpost[locRFBin][locCutView]->Fill(locDeltaE,locDeltaTheta);
                                                                dHist_ProtonPhi_dTheta_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                dHist_SigTrans_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);

                                                                //dHist_SigTransYield2[locRFBin][locBeamEBin]->Fill(locPhotonSigTransBCALShower);
                                                                // dHist_SigThetaYield2[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower);
                                                                 //dHist_SigLongYield2[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower);
                                                                if(locPhotonSigTransBCALShower < 0.0035){
                                                                                //dHist_ProtonPhi_SigTrans_B[locRFBin][locCutCounter2]->Fill(locProtonPhi2);
                                                                        dHist_SigTrans_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigTransBCALShower);
                                                                        dHist_SigTheta_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                //dHist_ProtonPhi_SigTrans_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                        if(locPhotonSigThetaBCALShower > 0.04){
                                                                                dHist_SigTheta_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigThetaBCALShower);
                                                                                dHist_SigLong_BCALpre[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                        //dHist_ProtonPhi_SigTheta_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                                if(locPhotonSigLongBCALShower < 1.){
                                                                                        dHist_SigLong_BCALpost[locRFBin][locCutView]->Fill(locPhotonSigLongBCALShower);
                                                                                                        //dHist_ProtonPhi_SigLong_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                                                                                        }}}}}}}
                                }}
 dHist_BCALSigTrans_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
 dHist_BCALSigTrans_SigLong_Normal[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
 dHist_BCALSigLong_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);
 
 //dHist_DeltaPhi_t[locRFBin]->Fill(loct, locDeltaPhi);
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
// Loop to find the purity of all three sig variables
// z-> switches between FCAL and BCAL
        if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
// Cuts out the large range of the Delta Phi since it is 2pi            
                if(locDeltaPhi > 360.) locDeltaPhi -= 360.;
                if(locDeltaPhi < 0.) locDeltaPhi += 360.;
//Looks at the BCAL being greater than zero (only need BCAL for purity
                if(locPhotonBCALShowerE >0.){
                        for(int f=0; f<2; f++){
                                if(f==0){
//dPhi<1.5                                                      
//                              if(locDeltaPhi-180){


                                        dHist_DeltaPhi_t[locRFBin]->Fill(loct, locDeltaPhi);
                                        dHist_Delta_Phi[locRFBin]->Fill(locDeltaPhi);
                                        dHist_Delta_Energy_O[locRFBin]->Fill(locDeltaE);
                                        dHist_Delta_Theta_O[locRFBin]->Fill(locDeltaTheta);
                                        if(fabs(locDeltaPhi-180)<1.5){
//                                              dHist_DeltaPhi_t[locRFBin]->Fill(loct, locDeltaPhi);
//                                              dHist_Delta_Energy_Up[locRFBin]->Fill(locDeltaE);
 //                                             dHist_Delta_Theta_Up[locRFBin]->Fill(locDeltaTheta);
                                                if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2){
//Loose cuts
                                                        dHist_DeltaPhi_t[locRFBin]->Fill(loct, locDeltaPhi);
                                                        dHist_SigLongPure_DPlessThan_B[locRFBin]->Fill(locPhotonSigLongBCALShower);
                                                        dHist_SigThetaPure_DPlessThan_B[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                                                        dHist_SigTransPure_DPlessThan_B[locRFBin]->Fill(locPhotonSigTransBCALShower);
                                                        
                                                        #if 0                                                   
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
                dHist_SigTrans_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);

                dHist_SigTrans_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigTransBCALShower);

                dHist_SigTrans_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigTransBCALShower);

                dHist_SigTrans_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigTransBCALShower);
                dHist_SigTrans_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigTransBCALShower);

                dHist_SigTrans_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigTransBCALShower);

                dHist_SigTrans_t[locRFBin]->Fill(loct, locPhotonSigTransBCALShower);
                dHist_SigTrans_s[locRFBin]->Fill(locs, locPhotonSigTransBCALShower);
                dHist_SigTrans_u[locRFBin]->Fill(locu, locPhotonSigTransBCALShower);

                dHist_SigTrans_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigTransBCALShower);
                dHist_SigTrans_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigTransBCALShower);

                dHist_SigTrans_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigTransBCALShower);
                dHist_SigTrans_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigTransBCALShower);

                dHist_SigTrans_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigTransBCALShower);
                dHist_SigTrans_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigTransBCALShower);

                dHist_SigTrans_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigTransBCALShower);
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

dHist_SigTheta_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigThetaBCALShower);

                dHist_SigTheta_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigThetaBCALShower);

                dHist_SigTheta_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigThetaBCALShower);

                dHist_SigTheta_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigThetaBCALShower);

                dHist_SigTheta_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigThetaBCALShower);

                dHist_SigTheta_t[locRFBin]->Fill(loct, locPhotonSigThetaBCALShower);
                dHist_SigTheta_s[locRFBin]->Fill(locs, locPhotonSigThetaBCALShower);
                dHist_SigTheta_u[locRFBin]->Fill(locu, locPhotonSigThetaBCALShower);

                dHist_SigTheta_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigThetaBCALShower);

                dHist_SigTheta_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigThetaBCALShower);
                dHist_SigTheta_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigThetaBCALShower);

                dHist_SigTheta_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigThetaBCALShower);
                dHist_SigTheta_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigThetaBCALShower);

                dHist_SigTheta_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigThetaBCALShower);
/*----------------------------------------------------------------------------------------------------------------------------------------------*/

 dHist_SigLong_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigLongBCALShower);

                dHist_SigLong_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigLongBCALShower);

                dHist_SigLong_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigLongBCALShower);

                dHist_SigLong_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigLongBCALShower);
                dHist_SigLong_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigLongBCALShower);

                dHist_SigLong_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigLongBCALShower);

                dHist_SigLong_t[locRFBin]->Fill(loct, locPhotonSigLongBCALShower);
                dHist_SigLong_s[locRFBin]->Fill(locs, locPhotonSigLongBCALShower);
                dHist_SigLong_u[locRFBin]->Fill(locu, locPhotonSigLongBCALShower);

                dHist_SigLong_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigLongBCALShower);
                dHist_SigLong_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigLongBCALShower);

                dHist_SigLong_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigLongBCALShower);
                dHist_SigLong_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigLongBCALShower);

                dHist_SigLong_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigLongBCALShower);
                dHist_SigLong_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigLongBCALShower);

                dHist_SigLong_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigLongBCALShower);
/*----------------------------------------------------------------------------------------------------------------------------------------------*/
#endif

if(locPhotonTheta > 11){
                                                                dHist_BCALSigTrans_SigTheta_Normal_cutsApplied[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                                                                dHist_BCALSigTrans_SigLong_Normal_cutsApplied[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                                                                dHist_BCALSigLong_SigTheta_Normal_cutsApplied[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);

                                                                dHist_EPre_EShower_PhotonThetaDet[locRFBin]->Fill(locEPre_EShower, locPhotonThetaDet);
                                                                dHist_EPreShower_PhotonThetaDet[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonThetaDet);

                                                                dHist_SigTrans_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigTransBCALShower);
                                                                dHist_SigTheta_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigThetaBCALShower);
                                                                dHist_SigLong_EPreEShower[locRFBin]->Fill(locEPre_EShower, locPhotonSigLongBCALShower);

                                                                dHist_EPreEShower_EPreShower[locRFBin]->Fill(locEPre_EShower, locPhotonBCALPreShowerE);
                                                                dHist_EPreEShower_EShower[locRFBin]->Fill(locEPre_EShower, locPhotonBCALShowerE);
                                                                dHist_EShower_EPreShower[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonBCALPreShowerE);

                //if(locPhotonThetaDet < 13){
                  //      dHist_SigTrans_SigTheta_varyLess_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                //if(locPhotonThetaDet > 13){
                  //      dHist_SigTrans_SigTheta_varyMore_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                //if(locMissingEnergy < 0.5){
                  //      dHist_SigTrans_SigTheta_varyLess_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                //if(locMissingEnergy > 0.5){
                  //      dHist_SigTrans_SigTheta_varyMore_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                  
                  //dHist_Photon_PreShowerE->Fill(locPhotonBCALPreShowerE);
                                                        //dHist_EnergyPre_EnergyShower_O->Fill(locEPre_EShower);
                                                        if(locPhotonBCALPreShowerE > 1){
                                                                //dHist_EnergyPre_EnergyShower_Up->Fill(locEPre_EShower);
                                                                if(locEPre_EShower > 0.4){

                                                                        if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE_Scale[locRFBin]->Fill(locPhotonSigThetaBCALShower*0.925, locPhotonSigTransBCALShower*0.95);}

                                                                        if(locPhotonSigThetaBCALShower < 0.001){//0.0015){
                                                                                if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower);
                                                                                        dHist_SigTrans_varyMore_105_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.05);
                                                                                        dHist_SigTrans_varyMore_11_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.1);                                                                                                                dHist_SigTrans_varyMore_115_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.15);
                                                                                        dHist_SigTrans_varyMore_12_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.2);
                                                                                        dHist_SigTrans_varyMore_125_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.25);
                                                                                        dHist_SigTrans_varyMore_13_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*1.3);

                                                                                        dHist_SigTrans_varyMore_80_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.8);
                                                                                        dHist_SigTrans_varyMore_825_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.825);                                                                                                              dHist_SigTrans_varyMore_85_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.85);
                                                                                        dHist_SigTrans_varyMore_875_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.875);


                                                                                        dHist_SigTrans_varyMore_90_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.9);
                                                                                        dHist_SigTrans_varyMore_925_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.925);                                                                                                              dHist_SigTrans_varyMore_95_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.95);
                                                                                        dHist_SigTrans_varyMore_975_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower*.975);


 }}
                                                                                if(locPhotonSigTransBCALShower < 0.0062){
                                                                                      if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                                                                                        dHist_SigTheta_varyMore_105_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.05);
                                                                                        dHist_SigTheta_varyMore_11_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.1);                                                                                                                dHist_SigTheta_varyMore_115_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.15);
                                                                                        dHist_SigTheta_varyMore_12_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.2);
                                                                                        dHist_SigTheta_varyMore_125_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.25);
                                                                                        dHist_SigTheta_varyMore_13_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*1.3);


                                                                                        dHist_SigTheta_varyMore_80_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.8);
                                                                                        dHist_SigTheta_varyMore_825_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.825);
                                                                                        dHist_SigTheta_varyMore_85_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.85);
                                                                                        dHist_SigTheta_varyMore_875_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.875);

                                                                                        dHist_SigTheta_varyMore_90_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.9);
                                                                                        dHist_SigTheta_varyMore_925_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.925);
                                                                                        dHist_SigTheta_varyMore_95_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);
                                                                                        dHist_SigTheta_varyMore_975_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.975);


if(locPhotonSigThetaBCALShower < 0.0013){
                                                                                                dHist_SigTheta_varyMore_piCut_0013_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.00125){
                                                                                                dHist_SigTheta_varyMore_piCut_00125_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.0012){
                                                                                                dHist_SigTheta_varyMore_piCut_0012_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.00115){
                                                                                                dHist_SigTheta_varyMore_piCut_00115_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.0011){
                                                                                                dHist_SigTheta_varyMore_piCut_0011_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.00105){
                                                                                                dHist_SigTheta_varyMore_piCut_00105_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.001){
                                                                                                dHist_SigTheta_varyMore_piCut_001_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.00095){
                                                                                                dHist_SigTheta_varyMore_piCut_00095_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}
                                                                                        if(locPhotonSigThetaBCALShower < 0.0009){
                                                                                                dHist_SigTheta_varyMore_piCut_0009_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}


if(locPhotonSigThetaBCALShower < 0.00075){
                                                                                                dHist_SigTheta_varyMore_piCut_00075_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower*.95);}



                                                                                                }}
                                                                                if(locPhotonSigTransBCALShower < 0.0062){
                                                                                        if(locPhotonSigThetaBCALShower < 0.001){//0.0015){ //for a tighter cut
                                                                                                dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower);}}

                                                                        if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigThetaBCALShower < 0.001){
                                                                                dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigTransBCALShower < 0.0062){
                                                                                dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);}

                                                                        dHist_SigTrans_PhotonThetaDet_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);

                                                                        dHist_EPre_EShower_PhotonThetaDet_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonThetaDet);
                                                                        dHist_EPreShower_PhotonThetaDet_varyMore[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonThetaDet);

                                                                        dHist_SigTrans_EPreEShower_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonSigTransBCALShower);
                                                                        dHist_SigTheta_EPreEShower_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonSigThetaBCALShower);
                                                                        dHist_SigLong_EPreEShower_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonSigLongBCALShower);

                                                                        dHist_EPreEShower_EPreShower_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonBCALPreShowerE);
                                                                        dHist_EPreEShower_EShower_varyMore[locRFBin]->Fill(locEPre_EShower, locPhotonBCALShowerE);
                                                                        dHist_EShower_EPreShower_varyMore[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonBCALPreShowerE);

                                                                        }}
if(locPhotonBCALPreShowerE < 1){
                                                                        if(locPhotonSigThetaBCALShower < 0.001){//0.0015){
                                                                                if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigTrans_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower);}}
                                                                                if(locPhotonSigTransBCALShower < 0.0062){
                                                                                      if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower);}}
                                                                                if(locPhotonSigTransBCALShower < 0.0062){
                                                                                        if(locPhotonSigThetaBCALShower < 0.001){//0.0015){ //for a tighter cut
                                                                                                dHist_SigLong_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower);}}

                                                                        if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                dHist_SigTrans_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigThetaBCALShower < 0.001){
                                                                                dHist_SigTrans_SigLong_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigTransBCALShower < 0.0062){
                                                                                dHist_SigLong_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);}
                                                                        dHist_SigTrans_PhotonThetaDet_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);
        }
//      if(locPhotonBCALPreShowerE > 0.5){
                                                        //              dHist_SigTrans_PhotonThetaDet_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);
                                                        //              dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                                                        //              dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                                                        //              dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);}
                                                        //              dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower);
                                                        //              dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                                                        //              dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower);
                }
                                                                        if(locPhotonSigTransBCALShower < 0.0062){
                                                                                if(locPhotonSigThetaBCALShower < 0.001){//0.0015){ //for a tighter cut
                                                                                        dHist_SigLongPure_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigLongBCALShower);}}
                                                                        if(locPhotonSigTransBCALShower > 0.0062){
                                                                                if(locPhotonSigThetaBCALShower > 0.001){//0.0015){
                                                                                        dHist_SigLongPure_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigLongBCALShower);}}

                                                                        if(locPhotonSigTransBCALShower < 0.0062){
                                                                              if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigThetaPure_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigThetaBCALShower);}}
                                                                        if(locPhotonSigTransBCALShower > 0.0062){
                                                                              if(locPhotonSigLongBCALShower > 6.){
                                                                                        dHist_SigThetaPure_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigThetaBCALShower);}}
                                                                        if(locPhotonSigThetaBCALShower < 0.001){//0.0015){
                                                                                if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                        dHist_SigTransPure_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigTransBCALShower);}}
                                                                        if(locPhotonSigThetaBCALShower > 0.001){//0.0015){ 
                                                                                if(locPhotonSigLongBCALShower > 6.){
                                                                                        dHist_SigTransPure_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigTransBCALShower);}}

                                                                        if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                                                                                
                                                                                if(locPhotonSigLongBCALShower > 6.){
                                                                                dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigTransBCALShower < 0.0062){
                                                                                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigThetaBCALShower);}
                                                                        if(locPhotonSigTransBCALShower > 0.0062){
                                                                                dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigThetaBCALShower);}

                                                                        if(locPhotonSigThetaBCALShower < 0.001){
                                                                                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}
                                                                        if(locPhotonSigThetaBCALShower > 0.001){
                                                                                dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}


}}}
//-----------------------------------------------------------------__FINAL CUTS__--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

// Keeps the energy in range
if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
  // Cuts out the large range of the Delta Phi since it is 2pi            
        if(locDeltaPhi > 360.) locDeltaPhi -= 360.;
        if(locDeltaPhi < 0.) locDeltaPhi += 360.;
        if(locPhotonBCALShowerE >0.){
                // dHist_dPhi_Final[locRFBin]->Fill(locDeltaPhi);
                if(locDeltaPhi > 179 && locDeltaPhi < 181.2) {
                        dHist_dPhi_Final[locRFBin]->Fill(locDeltaPhi);
                        dHist_Delta_Energy_Up[locRFBin]->Fill(locDeltaE);
                        dHist_Delta_Theta_Up[locRFBin]->Fill(locDeltaTheta);
}}}







/*
if(locPhotonTheta > 11){
                dHist_BCALSigTrans_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigTrans_SigLong_Normal[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigLong_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);
                if(locPhotonThetaDet < 13){
                        dHist_SigTrans_SigTheta_varyLess_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locPhotonThetaDet > 13){
                        dHist_SigTrans_SigTheta_varyMore_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locMissingEnergy < 0.5){
                        dHist_SigTrans_SigTheta_varyLess_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locMissingEnergy > 0.5){
                        dHist_SigTrans_SigTheta_varyMore_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locPhotonBCALPreShowerE < 0.5){
                        dHist_SigTrans_PhotonThetaDet_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);
                        dHist_SigTrans_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                        dHist_SigTrans_SigLong_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                        dHist_SigLong_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);
                        dHist_SigTrans_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower);
                        dHist_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                        dHist_SigLong_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower);
                        }
                         if(locPhotonBCALPreShowerE > 0.5){
                        dHist_SigTrans_PhotonThetaDet_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);
                        dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                        dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                        dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigLongBCALShower);}
                        dHist_SigTrans_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigTransBCALShower);
                        dHist_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                        dHist_SigLong_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigLongBCALShower);
                }               
*/

//Dont need currently. Will need later for checking
                                /*if(f==1){
//dPhi>1.5                      
                                        if(fabs(locDeltaPhi-180)>1.5){
                                                if(fabs(locDeltaTheta) < 4. || fabs(locDeltaE) > -2){
                                                        
                                                        dHist_SigLongPure_DPgraThan_B[locRFBin]->Fill(locPhotonSigLongBCALShower);
                                                        dHist_SigThetaPure_DPgraThan_B[locRFBin]->Fill(locPhotonSigThetaBCALShower);
                                                        dHist_SigTransPure_DPgraThan_B[locRFBin]->Fill(locPhotonSigTransBCALShower);
                        
                                                        if(locPhotonSigTransBCALShower < 0.007){
                                                                if(locPhotonSigThetaBCALShower < 0.0015){
                                                                      dHist_SigLongPure_DPgraThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigLongBCALShower);}}
                                                        if(locPhotonSigTransBCALShower > 0.007){
                                                                if(locPhotonSigThetaBCALShower > 0.0015){
                                                                      dHist_SigLongPure_DPgraThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigLongBCALShower);}}

                                                        if(locPhotonSigTransBCALShower < 0.007){
                                                                if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                      dHist_SigThetaPure_DPgraThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigThetaBCALShower);}}
                                                        if(locPhotonSigTransBCALShower > 0.007){
                                                                if(locPhotonSigLongBCALShower > 6.){
                                                                      dHist_SigThetaPure_DPgraThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigThetaBCALShower);}}                         
if(locPhotonSigThetaBCALShower < 0.0015){
                                                                if(locPhotonSigLongBCALShower > 1. && locPhotonSigLongBCALShower < 6.){
                                                                      dHist_SigTransPure_DPgraThan_B_SignalCutComp[locRFBin]->Fill(locPhotonSigTransBCALShower);}}
                                                        if(locPhotonSigThetaBCALShower > 0.0015){
                                                                if(locPhotonSigLongBCALShower > 6.){
                                                                      dHist_SigTransPure_DPgraThan_B_SignalCutPi0[locRFBin]->Fill(locPhotonSigTransBCALShower);}}}}} 
*/


}}} //ends loop


//------------------------------------------------------------------------------------------------------------------------------
                dHist_ProtonP_Theta_Init[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                if(locProtonP < 0.25) continue;
                //if(locProtonP >2.1) continue;
                if(locProtonTheta < 20.) continue;
                // remove high -t region populated by accidentals
                //dHist_ProtonP_Theta_Init[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                dHist_ProtonP_Theta_Final2[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);

//------------------------------------------------------------------------------------------------------------------------------
                int locCutCounter = 0;
                dHist_ProtonPhi_t_Init0[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                dHist_ProtonPhi_ThetaCM_Init0[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
//This is how the CutCounter is used
                if(locBeamEBin == 3) {
                        dHist_ProtonPhi_t_Final0[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                        dHist_ProtonPhi_ThetaCM_Final0[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                }
//This is how to account for double counting 
                /*
                if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
                {
                        //unique missing mass combo: histogram it, and register this combo of particles
                    locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
                    dHist_MissingEnergy1stCut[locRFBin][locBeamEBin]->Fill(locMissingEnergy);
                    dHist_MissingMassSquared1stCut[locRFBin][locBeamEBin]->Fill(locMissingMassSquared);
                                                                                                                }
                  */
                    dHist_DeltaPhi1stCut[locRFBin][locBeamEBin]->Fill(locDeltaPhi);

                /********************************************* COMBINE FOUR-MOMENTUM ********************************************/

// (Called Up top) Combine 4-vectors
                //TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
                //locMissingP4_Measured -= locPhotonP4_Measured + locProtonP4_Measured;
                //TLorentzVector locPhotonP4_Missing_Measured = locBeamP4_Measured + dTargetP4;
                //locPhotonP4_Missing_Measured -= locProtonP4_Measured;
                //TLorentzVector locProtonP4_Missing_Measured = locBeamP4_Measured + dTargetP4;
                //locProtonP4_Missing_Measured -=locPhotonP4_Measured;

//Missing Mass Squared/Missing Energy (Called Up top)
                //double locMissingMassSquared = locMissingP4_Measured.M2();
                //double locMissingEnergy = locMissingP4_Measured.E();

                dHist_MMS->Fill(locMissingMassSquared);
                dHist_ME->Fill(locMissingEnergy);
                 //dHist_PhotonTheta_ThetaDet_Final[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonTheta);
                //Uniqueness tracking: Build the map of particles used for the missing mass
                        //For beam: Don't want to group with final-state photons. Instead use "Unknown" PID (not ideal, but it's easy).
                //map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
                //locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
                //locUsedThisCombo_MissingMass[Gamma].insert(locPhotonNeutralID);
                //locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);

//Compare to what's been used so far
                //if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
                //{
                        //unique missing mass combo: histogram it, and register this combo of particles
                        dHist_MissingMassSquared_Init[locRFBin][locBeamEBin]->Fill(locMissingMassSquared);
                        dHist_MissingEnergy_Final[locRFBin][locBeamEBin]->Fill(locMissingEnergy);
                        locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
                //}
                //
// Accidental Cuts
                if(locBeamDeltaT > 2.004) continue;
                if(locBeamDeltaT < -2.004) continue;

// cut missing mass squared
                //if(fabs(locMissingMassSquared) < 0.05){
                //      dHist_MissingMassSquared_Final[locRFBin][locBeamEBin]->Fill(locMissingMassSquared);
                //      continue;}
// unused shower energy sum
                double unusedEnergyBCAL = 0.;
                double unusedEnergyFCAL = 0.;

                dHist_unusedEnergyB->Fill(unusedEnergyBCAL);
                dHist_unusedEnergyF->Fill(unusedEnergyFCAL);
                dHist_unusedTotal->Fill(unusedEnergyBCAL+unusedEnergyFCAL);
                 //What exactly does this do? (Gets the NeurtalHyops from combo wrapper so that I can call them
                for(UInt_t loc_j = 0; loc_j < Get_NumNeutralHypos(); ++loc_j) {

                        //Set branch array indices corresponding to this particle
                        dNeutralHypoWrapper->Set_ArrayIndex(loc_j);
                        UInt_t locPhotonNeutralPID = dNeutralHypoWrapper->Get_PID();
                        if(locPhotonNeutralPID != Gamma || dNeutralHypoWrapper->Get_NeutralID() == locPhotonNeutralID)
                                continue;

                        unusedEnergyBCAL += dNeutralHypoWrapper->Get_Energy_BCAL();
                        unusedEnergyFCAL += dNeutralHypoWrapper->Get_Energy_FCAL();
                }
                dHist_UnusedEnergyBCAL_t_Final[locRFBin][locBeamEBin]->Fill(loct, unusedEnergyBCAL);
                dHist_UnusedEnergyFCAL_t_Final[locRFBin][locBeamEBin]->Fill(loct, unusedEnergyFCAL);
                dHist_UnusedEnergyTotal_t_Init[locRFBin][locBeamEBin]->Fill(loct, unusedEnergyBCAL+unusedEnergyFCAL);


// cut unused energy
                if(unusedEnergyBCAL+unusedEnergyFCAL > 0.1)
                        continue;
// cut BCAL shower shape
                dHist_BCALSigTrans_SigLong_Init[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigTrans_SigTheta_Init[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                if(locPhotonBCALShowerE > 0.) {
                        //dHist_BCALSigTrans_SigLong_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                //      dHist_BCALSigTrans_SigTheta_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                        //if(locPhotonSigTransBCALShower > 0.0035)
                        //      continue; 
                        //if(locPhotonSigThetaBCALShower > 0.0035)
                        //      continue;
                                //dHist_BCALSigTrans_SigLong_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                                //dHist_BCALSigTrans_SigTheta_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                        //dHist_BCALSigTrans_SigLong_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);

                }
                //              
//#if 1 
                dHist_ProtonP_Theta_Final5[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                locCutCounter++; // = 1
                dHist_ProtonPhi_t_Init1[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                dHist_ProtonPhi_ThetaCM_Init1[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                if(locBeamEBin == 3) {
                        dHist_ProtonPhi_t_Final1[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                        dHist_ProtonPhi_ThetaCM_Final1[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                        //dHist_ProtonP_Theta_Final3[locRFBin][locCutCounter]->Fill(locProtonTheta, locProtonP);
                }


                if(locProtonTheta > 11){
                if(locUsedSoFar_Proton.find(locProtonTrackID) == locUsedSoFar_Proton.end())
                {
                dHist_dEdx_p_CDC_Final[locRFBin][locBeamEBin]->Fill(locProtonP, locdEdxCDC*1e6);
                locUsedSoFar_Proton.insert(locProtonTrackID);
                }}
                dHist_dEdx_p_FDC_Final[locRFBin][locBeamEBin]->Fill(locProtonP, locdEdxFDC*1e6);

                dHist_DT->Fill(locDeltaTheta);
                dHist_DE->Fill(locDeltaE);


                if(locPhotonFCALShowerE > 0.)
                        locDeltaE = locPhotonFCALShowerE - locPhotonP4_Missing_Measured.E();
//------------------------------------------------------------------------------------------------------------------------------
// DeltaPhi (called at top)
                //double locDeltaPhi = (locPhotonP4_Measured.Phi() - locProtonP4_Measured.Phi())*180./TMath::Pi();
                dHist_DP->Fill(locDeltaPhi);
                if(locDeltaPhi > 360.) locDeltaPhi -= 360.;
                if(locDeltaPhi < 0.) locDeltaPhi += 360.;
                dHist_DP->Fill(locDeltaPhi);
                dHist_PhotonThetaMeasure_PhotonThetaMissing_Init[locRFBin][locBeamEBin]->Fill(locPhotonP4_Missing_Measured.Theta()*180./TMath::Pi(), locPhotonP4_Measured.Theta()*180./TMath::Pi());
                //dHist_DeltaE_DeltaTheta_BCAL_Init[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaE);
                dHist_DeltaPhi_DeltaTheta_BCAL_Init[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaPhi);
                dHist_DeltaPhi_DeltaTheta_FCAL_Init[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaPhi);
                if(locPhotonBCALShowerE > 0.) {
                        dHist_PhotonThetaMeasure_PhotonThetaMissing_Final[locRFBin][locBeamEBin]->Fill(locPhotonP4_Missing_Measured.Theta()*180./TMath::Pi(), locPhotonP4_Measured.Theta()*180./TMath::Pi());
                        dHist_DeltaE_DeltaTheta_BCAL_Init[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaE);
                        if(locDeltaPhi-180){
                                dHist_DeltaPhi_DeltaEnergy_BCAL_Final3[locRFBin][locBeamEBin]->Fill(locDeltaE, locDeltaPhi);}
                        if(fabs(locDeltaPhi - 180) <1.5){
                                dHist_DeltaE_DeltaTheta_BCAL_Final[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaE);
                                dHist_DeltaPhi_DeltaEnergy_BCAL_Final[locRFBin][locBeamEBin]->Fill(locDeltaE, locDeltaPhi);
                                dHist_DeltaPhi_DeltaTheta_BCAL_Final[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaPhi);}
                        if(fabs(locDeltaPhi - 180) >1.5){
                                //dHist_DeltaE_DeltaTheta_BCAL_Final2[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaE);
                                dHist_DeltaPhi_DeltaTheta_BCAL_Final2[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaPhi);
                                dHist_DeltaPhi_DeltaEnergy_BCAL_Final2[locRFBin][locBeamEBin]->Fill(locDeltaE, locDeltaPhi);}}
                else
                        dHist_DeltaPhi_DeltaTheta_FCAL_Final[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaPhi);
                /***********************************************************************************************************/


//Attempt at changing to a new locCutCounter
                locCutCounter2++; //=2*/
                locCutCounter++; // = 2
                dHist_ProtonPhi_t_Init2[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                dHist_ProtonPhi_ThetaCM_Init2[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                if(locBeamEBin == 3) {
                        dHist_ProtonPhi_t_Final2[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                        dHist_ProtonPhi_ThetaCM_Final2[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                }
//------------------------------------------------------------------------------------------------------------------------              
//------------------------------------------------------------------------------------------------------------------------
//Delta Phi cuts 
                dHist_DeltaPhi_t_Init[locRFBin][locBeamEBin]->Fill(loct, locDeltaPhi);
                if(fabs(locDeltaTheta) > 4. || locDeltaE < -2.) {
                        dHist_DeltaE_DeltaTheta_BCAL_Final2[locRFBin][locBeamEBin]->Fill(locDeltaTheta, locDeltaE);
                        continue;
                }
                dHist_DeltaPhi_t_Final[locRFBin][locBeamEBin]->Fill(loct, locDeltaPhi);

// assign delta phi bins to to match locCutCounter
                if(fabs(locDeltaPhi - 180.) < 0.5) locCutCounter += 1; // = 3
                else if(fabs(locDeltaPhi - 180.) > 10. && fabs(locDeltaPhi - 180.) < 20) locCutCounter += 2; // = 4
                else continue;
                //dHist_ProtonP_Theta_Final[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                /********************************************* FINAL ASYMMETRIES ********************************************/

//------------------------------------------------------------------------------------------------------------------------
//For locCutCounter
                dHist_ProtonPhi_t_Init3[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                dHist_ProtonPhi_ThetaCM_Init3[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);
                if(locBeamEBin == 3) {
                        dHist_ProtonPhi_t_Final3[locRFBin][locCutCounter]->Fill(loct, locProtonPhi);
                        dHist_ProtonPhi_ThetaCM_Final3[locRFBin][locCutCounter]->Fill(locThetaCM, locProtonPhi);

                }

/********************************************* FINAL KINEMATICS ********************************************/


//------------------------------------------------------------------------------------------------------------------------
                //dHist_ProtonP_Theta_Final2[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                dHist_ThetaCM_ProtonTheta_Init[locRFBin][locBeamEBin]->Fill(locProtonTheta, locThetaCM);
                dHist_ThetaCM_PhotonTheta_Init[locRFBin][locBeamEBin]->Fill(locPhotonTheta, locThetaCM);
                dHist_ThetaCM_t_Init[locRFBin][locBeamEBin]->Fill(loct, locThetaCM);
                dHist_u_t_Init[locRFBin][locBeamEBin]->Fill(loct, locu);
                dHist_u_s_Init[locRFBin][locBeamEBin]->Fill(locs, locu);
                dHist_s_t_Init[locRFBin][locBeamEBin]->Fill(loct, locs);

//Final locCutCounter with Width variables
                if(locCutCounter == 3) {
                        dHist_ProtonP_Theta_Final[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                        //dHist_ProtonP_Theta_Final3[locRFBin][locBeamEBin]->Fill(locProtonTheta, locProtonP);
                        dHist_PhotonP_Theta_Final[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonP);
                        if(locPhotonBCALShowerE > 0.) {
                                dHist_PhotonTheta_ThetaDet_Final[locRFBin][locBeamEBin]->Fill(locPhotonThetaDet, locPhotonTheta);
                                dHist_BCALSigTrans_SigTheta_Final2[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                                if(locPhotonSigTransBCALShower < 0.0035)
                                        continue;
                                dHist_BCALSigTrans_SigTheta_Final2[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                                if(locPhotonSigThetaBCALShower > 0.004)
                                        continue;
                                dHist_BCALSigTheta_SigLong_Final[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigThetaBCALShower);
                                dHist_BCALSigTrans_SigLong_Final2[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);

                        }
                        dHist_ThetaCM_ProtonTheta_Final[locRFBin][locBeamEBin]->Fill(locProtonTheta, locThetaCM);
                        dHist_ThetaCM_PhotonTheta_Final[locRFBin][locBeamEBin]->Fill(locPhotonTheta, locThetaCM);
                        dHist_ThetaCM_t_Final[locRFBin][locBeamEBin]->Fill(loct, locThetaCM);
                        dHist_u_t_Final[locRFBin][locBeamEBin]->Fill(loct, locu);
                        dHist_u_s_Final[locRFBin][locBeamEBin]->Fill(locs, locu);
                        dHist_s_t_Final[locRFBin][locBeamEBin]->Fill(loct, locs);

//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//looking at the beam asymmetry (sanity check should all be the same)
                        if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
                                dHist_ProtonPhi->Fill(locProtonPhi);}
                        if(locPhotonFCALShowerE > 0.){
                                if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
                                        dHist_ProtonPhi11->Fill(locProtonPhi11);}}
                        if(locPhotonBCALShowerE > 0.){
                                if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8){
                                        dHist_ProtonPhi22->Fill(locProtonPhi22);}}}
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//Makes sure that there are no empty bins (can optimize this with SetBinContent)
                        if(locPhotonSigTransBCALShower > 0.0041 && locPhotonSigTransBCALShower < 0.017){
                                dHist_SigTransYield[locRFBin][locBeamEBin]->Fill(locPhotonSigTransBCALShower);}

                        if(locPhotonSigThetaBCALShower > 0.00066 && locPhotonSigThetaBCALShower < 0.0039){
                                dHist_SigThetaYield[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower);}

                        if(locPhotonSigLongBCALShower > 0.88 && locPhotonSigLongBCALShower < 20){
                                 dHist_SigLongYield[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower);}
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
//Seperate from above looks at width cuts closely (not needed atm)      
                        if(locPhotonSigThetaBCALShower<0.015){
                                if(locPhotonSigTransBCALShower>0.0035 && locPhotonSigTransBCALShower<0.007){
                                        dHist_SigTheta_SigTrans_Compton[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);//}}
                                        dHist_ProtonPhi_SigLong_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);}}

                        if(locPhotonSigThetaBCALShower>0.015 || locPhotonSigTransBCALShower<0.0035 || locPhotonSigTransBCALShower>0.007){
                                dHist_ProtonPhi_SigLong_B[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                dHist_SigTheta_SigTrans_Pizero[locRFBin][locBeamEBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}

                        if(locPhotonSigTransBCALShower>0.0035 && locPhotonSigTransBCALShower<0.007){
                                if(locPhotonSigLongBCALShower>2 && locPhotonSigLongBCALShower<6){
                                        dHist_ProtonPhi_SigTheta_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                        dHist_SigLong_SigTrans_Compton[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}}

if(locPhotonSigTransBCALShower<0.0035 || locPhotonSigTransBCALShower>0.007 || locPhotonSigLongBCALShower<2 || locPhotonSigLongBCALShower>6){
                                dHist_ProtonPhi_SigTheta_B[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                dHist_SigLong_SigTrans_Pizero[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);}

                        if(locPhotonSigThetaBCALShower<0.002){
                                if(locPhotonSigLongBCALShower>2 && locPhotonSigLongBCALShower<6){
                                        dHist_ProtonPhi_SigTrans_B2[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                        dHist_SigTheta_SigLong_Compton[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigThetaBCALShower);}}

                        if(locPhotonSigThetaBCALShower>0.002 || locPhotonSigLongBCALShower<2 || locPhotonSigLongBCALShower>6){
                                        dHist_ProtonPhi_SigTrans_B[locRFBin][locCutCounter2]->Fill(locProtonPhi22);
                                        dHist_SigTheta_SigLong_Pizero[locRFBin][locBeamEBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigThetaBCALShower);}

                         dHist_SigTrans_EPreEShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonBCALShowerE);

        if(locPhotonTheta > 11){
                dHist_SigTrans_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigTransBCALShower);
                dHist_SigTrans_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigTransBCALShower);

                dHist_SigTrans_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigTransBCALShower);
                dHist_SigTrans_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigTransBCALShower);

                dHist_SigTrans_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigTransBCALShower);

                dHist_SigTrans_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigTransBCALShower);
                dHist_SigTrans_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigTransBCALShower);
                dHist_SigTrans_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigTransBCALShower);

                dHist_SigTrans_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigTransBCALShower);
                dHist_SigTrans_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigTransBCALShower);

                dHist_SigTrans_t[locRFBin]->Fill(loct, locPhotonSigTransBCALShower);
                dHist_SigTrans_s[locRFBin]->Fill(locs, locPhotonSigTransBCALShower);
                dHist_SigTrans_u[locRFBin]->Fill(locu, locPhotonSigTransBCALShower);
                
                dHist_SigTrans_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigTransBCALShower);
                dHist_SigTrans_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigTransBCALShower);

                dHist_SigTrans_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigTransBCALShower);
                dHist_SigTrans_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigTransBCALShower);

                dHist_SigTrans_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigTransBCALShower);
                dHist_SigTrans_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigTransBCALShower);

                dHist_SigTrans_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigTransBCALShower);

                dHist_EPre_EShower->Divide(dHist_PBCALShowerE);
//
                dHist_SigTheta_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigThetaBCALShower);

                dHist_SigTheta_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigThetaBCALShower);

                dHist_SigTheta_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigThetaBCALShower);

                dHist_SigTheta_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigThetaBCALShower);
                dHist_SigTheta_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigThetaBCALShower);

                dHist_SigTheta_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigThetaBCALShower);
                dHist_SigTheta_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigThetaBCALShower);

                dHist_SigTheta_t[locRFBin]->Fill(loct, locPhotonSigThetaBCALShower);
                dHist_SigTheta_s[locRFBin]->Fill(locs, locPhotonSigThetaBCALShower);
                dHist_SigTheta_u[locRFBin]->Fill(locu, locPhotonSigThetaBCALShower);

                dHist_SigTheta_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigThetaBCALShower);
                dHist_SigTheta_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigThetaBCALShower);
dHist_SigTheta_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigThetaBCALShower);
                dHist_SigTheta_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigThetaBCALShower);

                dHist_SigTheta_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigThetaBCALShower);
                dHist_SigTheta_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigThetaBCALShower);

                dHist_SigTheta_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigThetaBCALShower);
//
                dHist_SigLong_PhotonP[locRFBin]->Fill(locPhotonP, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonTheta[locRFBin]->Fill(locPhotonTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonPhi[locRFBin]->Fill(locPhotonPhi, locPhotonSigLongBCALShower);
                dHist_SigLong_PhotonThetaDet[locRFBin]->Fill(locPhotonThetaDet, locPhotonSigLongBCALShower);

                dHist_SigLong_ProtonP[locRFBin]->Fill(locProtonP, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonTheta[locRFBin]->Fill(locProtonTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonPhi[locRFBin]->Fill(locProtonPhi, locPhotonSigLongBCALShower);
                dHist_SigLong_ProtonThetaDet[locRFBin]->Fill(locProtonThetaDet, locPhotonSigLongBCALShower);

                dHist_SigLong_ThetaCM[locRFBin]->Fill(locThetaCM, locPhotonSigLongBCALShower);

                dHist_SigLong_DeltaTheta[locRFBin]->Fill(locDeltaTheta, locPhotonSigLongBCALShower);
                dHist_SigLong_DeltaE[locRFBin]->Fill(locDeltaE, locPhotonSigLongBCALShower);
                dHist_SigLong_DeltaPhi[locRFBin]->Fill(locDeltaPhi, locPhotonSigLongBCALShower);

                dHist_SigLong_PBCALPreShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PrBCALSE[locRFBin]->Fill(locProtonBCALShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PBCALSE[locRFBin]->Fill(locPhotonBCALShowerE, locPhotonSigLongBCALShower);
                dHist_SigLong_PFCALSE[locRFBin]->Fill(locPhotonFCALShowerE, locPhotonSigLongBCALShower);

                dHist_SigLong_t[locRFBin]->Fill(loct, locPhotonSigLongBCALShower);
                dHist_SigLong_s[locRFBin]->Fill(locs, locPhotonSigLongBCALShower);
                dHist_SigLong_u[locRFBin]->Fill(locu, locPhotonSigLongBCALShower);

                dHist_SigLong_MMS[locRFBin]->Fill(locMissingMassSquared, locPhotonSigLongBCALShower);
                dHist_SigLong_ME[locRFBin]->Fill(locMissingEnergy, locPhotonSigLongBCALShower);

                dHist_SigLong_VertexZ[locRFBin]->Fill(locVertexZ, locPhotonSigLongBCALShower);
                dHist_SigLong_VertexR[locRFBin]->Fill(locVertexR, locPhotonSigLongBCALShower);
                dHist_SigLong_dEdxCDC[locRFBin]->Fill(locdEdxCDC*1e6, locPhotonSigLongBCALShower);
                dHist_SigLong_dEdxFDC[locRFBin]->Fill(locdEdxFDC*1e6, locPhotonSigLongBCALShower);

                dHist_SigLong_PhotonBCALShowerZ[locRFBin]->Fill(locPhotonBCALShowerZ, locPhotonSigLongBCALShower);



                double locEPre_EShower = locPhotonBCALPreShowerE*TMath::Power(locPhotonBCALShowerE, -1.);


                //dHist_SigTrans_EPreEShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonBCALShowerE);
                //dHist_SigTheta_EPreEShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonBCALShowerE);
                //dHist_SigLong_EPreEShower[locRFBin]->Fill(locPhotonBCALPreShowerE, locPhotonBCALShowerE);
}
/*      if(locPhotonTheta > 11){
                dHist_BCALSigTrans_SigTheta_Normal[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);
                dHist_BCALSigTrans_SigLong_Normal[locRFBin]->Fill(locPhotonSigLongBCALShower, locPhotonSigTransBCALShower);
                if(locPhotonThetaDet < 13){
                        dHist_SigTrans_SigTheta_varyLess_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locPhotonThetaDet > 13){
                        dHist_SigTrans_SigTheta_varyMore_PhotonThetaDet[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locMissingEnergy < 0.5){
                        dHist_SigTrans_SigTheta_varyLess_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locMissingEnergy > 0.5){
                        dHist_SigTrans_SigTheta_varyMore_ME[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locPhotonBCALPreShowerE < 0.5){
                        dHist_SigTrans_SigTheta_varyLess_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}
                if(locPhotonBCALPreShowerE > 0.5){
                        dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[locRFBin]->Fill(locPhotonSigThetaBCALShower, locPhotonSigTransBCALShower);}

               

                }*/
                
                //-------------------------------------------------------------------TO COMMENT OUT ALL OF THE FILLING FOR BUG FIXES------------------------------------------------------
//#endif
        } // end of combo loop

        //FILL HISTOGRAMS: Num combos / events surviving actions
        Fill_NumCombosSurvivedHists();

        return kTRUE;
}

void DSelector_compton::Finalize(void)
{
        //Save anything to output here that you do not want to be in the default DSelector output ROOT file.

        //Otherwise, don't do anything else (especially if you are using PROOF).
                //If you are using PROOF, this function is called on each thread,
                //so anything you do will not have the combined information from the various threads.
                //Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

        //DO YOUR STUFF HERE

        //CALL THIS LAST
        DSelector::Finalize(); //Saves results to the output file
}
