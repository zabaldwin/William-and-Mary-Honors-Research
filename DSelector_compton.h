#ifndef DSelector_compton_h
#define DSelector_compton_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"

class DSelector_compton : public DSelector
{
        public:

                DSelector_compton(TTree* locTree = NULL) : DSelector(locTree){}
                virtual ~DSelector_compton(){}

                void Init(TTree *tree);
                Bool_t Process(Long64_t entry);

        private:

                void Get_ComboWrappers(void);
                void Finalize(void);

                // BEAM POLARIZATION INFORMATION
                UInt_t dPreviousRunNumber;
                bool dIsPolarizedFlag; //else is AMO
                bool dIsPARAFlag; //else is PERP or AMO

                //CREATE REACTION-SPECIFIC PARTICLE ARRAYS

                //Step 0
                DParticleComboStep* dStep0Wrapper;
                DBeamParticle* dComboBeamWrapper;
                DNeutralParticleHypothesis* dPhotonWrapper;
                // DEFINE YOUR HISTOGRAMS HERE

                // index is locRFBin=2 and locBeamEBin = 5

                TH1I* dHist_BeamX4_measured;
                TH1I* dHist_Chisq_tracking[2][5], *dHist_Chisq_timing[2][5];
                TH1I* dHist_BeamEnergy_Init[2], *dHist_BeamEnergy_Final[2];
                TH1I* dHist_Deltat_Init2[2];
                TH2I* dHist_PhotonP_Theta_Init[2][5], *dHist_ProtonP_Theta_Init[2][5], *dHist_PhotonTheta_ThetaDet_Init[2][5];
                TH1I* dHist_VertexZ_Init[2][5], *dHist_VertexR_Init[2][5];
                TH1I* dHist_MissingMassSquared_Init[2][5], *dHist_MissingEnergy_Init[2][5], *dHist_MissingMassSquared_Final[2][5], *dHist_MissingEnergy_Final[2][5];
                TH2I* dHist_UnusedEnergyBCAL_t_Init[2][5], *dHist_UnusedEnergyFCAL_t_Init[2][5], *dHist_UnusedEnergyTotal_t_Init[2][5];
                TH2I* dHist_PhotonThetaMeasure_PhotonThetaMissing_Init[2][5], *dHist_DeltaE_DeltaTheta_BCAL_Init[2][5];
                TH2I* dHist_DeltaPhi_DeltaTheta_BCAL_Init[2][5], *dHist_DeltaPhi_DeltaTheta_FCAL_Init[2][5];
                TH2F* dHist_DeltaPhi_t_Init[2][5];
                TH2I* dHist_UnusedEnergyBCAL_t_Final[2][5], *dHist_UnusedEnergyFCAL_t_Final[2][5], *dHist_UnusedEnergyTotal_t_Final[2][5];
                TH2I* dHist_PhotonThetaMeasure_PhotonThetaMissing_Final[2][5], *dHist_DeltaE_DeltaTheta_BCAL_Final[2][5], *dHist_DeltaE_DeltaTheta_BCAL_Final2[2][5];
                TH2I* dHist_DeltaPhi_DeltaTheta_BCAL_Final[2][5], *dHist_DeltaPhi_DeltaTheta_FCAL_Final[2][5], *dHist_DeltaPhi_DeltaTheta_BCAL_Final2[2][5];
                TH2I* dHist_DeltaPhi_t_Final[2][5];
                TH1I* dHist_VertexZ_Final[2][5], *dHist_VertexR_Final[2][5];
                // indices are locRFBin=2 and locBeamEBin = 5 (old locDeltaPhiBin=2 Signal and Sideband)
                TH2I* dHist_ProtonP_Theta_Final[2][5], *dHist_PhotonP_Theta_Final[2][5], *dHist_ThetaCM_ProtonTheta_Init[2][5], *dHist_ThetaCM_ProtonTheta_Final[2][5];
                TH2I* dHist_PhotonTheta_ThetaDet_Final[2][5];
                TH2I* dHist_DeltaPhi_DeltaEnergy_BCAL_Final[2][5];
                TH2I* dHist_DeltaPhi_DeltaEnergy_BCAL_Final2[2][5];
                TH2I* dHist_DeltaPhi_DeltaEnergy_BCAL_Final3[2][5];
                TH2I* dHist_ThetaCM_PhotonTheta_Init[2][5], *dHist_ThetaCM_t_Init[2][5];
                TH2I* dHist_u_t_Init[2][5], *dHist_u_s_Init[2][5], *dHist_s_t_Init[2][5];
                TH2I* dHist_EnergyLossPho_P[2][5];
                TH2I* dHist_EnergyLoss_P[2][5];
                TH2I* dHist_BCALSigTrans_SigLong_Init[2][5], *dHist_BCALSigTrans_SigTheta_Init[2][5];
                TH2I* dHist_BCALSigTrans_SigLong_Final2[2][5], *dHist_BCALSigTrans_SigTheta_Final2[2][5];
                TH2I* dHist_dEdx_p_CDC_Init[2][5];
                TH2I* dHist_dEdx_p_CDC_Final[2][5];
                TH2I* dHist_dEdx_p_FDC_Init[2][5];
                TH2I* dHist_dEdx_p_FDC_Final[2][5];
                TH1I* dHist_TrackFCAL_DOCA;
                TH1I* dHist_TrackBCAL_DeltaPhi;
                TH1I* dHist_TrackBCAL_DeltaZ;

TH2I* dHist_SigLong_SigTrans_Compton[2][5], *dHist_SigTheta_SigTrans_Compton[2][5];
                TH2I* dHist_SigLong_SigTrans_Pizero[2][5], *dHist_SigTheta_SigTrans_Pizero[2][5];
                TH2I* dHist_SigTheta_SigLong_Compton[2][5], *dHist_SigTheta_SigLong_Pizero[2][5];

                TH1I* dHist_MissingMassSquaredPreCut[2][5], *dHist_MissingEnergyPreCut[2][5], *dHist_DeltaPhiPreCut[2][5];
                TH1I* dHist_MissingMassSquared1stCut[2][5], *dHist_MissingEnergy1stCut[2][5], *dHist_DeltaPhi1stCut[2][5];
                TH2I* dHist_ThetaCM_PhotonTheta_Final[2][5], *dHist_ThetaCM_t_Final[2][5];
                TH2I* dHist_u_t_Final[2][5], *dHist_u_s_Final[2][5], *dHist_s_t_Final[2][5];
                TH2I* dHist_BCALSigTheta_SigLong_Final[2][5], *dHist_BCALSigTrans_SigTheta_Final[2][5];
                // indices are locRFBin=2 and locCutCounter=5
                TH2I* dHist_ProtonPhi_t_Init0[2][5], *dHist_ProtonPhi_ThetaCM_Init0[2][5];
                TH2I* dHist_ProtonPhi_t_Init1[2][5], *dHist_ProtonPhi_ThetaCM_Init1[2][5];
                TH2I* dHist_ProtonPhi_t_Init2[2][5], *dHist_ProtonPhi_ThetaCM_Init2[2][5];
                TH2I* dHist_ProtonPhi_t_Init3[2][5], *dHist_ProtonPhi_ThetaCM_Init3[2][5];
                TH2I* dHist_ProtonPhi_t_Final0[2][5], *dHist_ProtonPhi_ThetaCM_Final0[2][5];
                TH2I* dHist_ProtonPhi_t_Final1[2][5], *dHist_ProtonPhi_ThetaCM_Final1[2][5];
                TH2I* dHist_ProtonPhi_t_Final2[2][5], *dHist_ProtonPhi_ThetaCM_Final2[2][5];
                TH2I* dHist_ProtonPhi_t_Final3[2][5], *dHist_ProtonPhi_ThetaCM_Final3[2][5];
                TH2I* dHist_ProtonP_Theta_Final2[2][5];
                TH2I* dHist_ProtonP_Theta_Final3[2][5];
                TH2I* dHist_ProtonP_Theta_Final4[2][5];
                TH2I* dHist_ProtonP_Theta_Final5[2][5];
                TH2I* dHist_ProtonP_Theta_Final6[2][5];
        //      TH2I* dHist_EnergyLoss_P[2][5];

                TH1I* dHist_unusedTotal;


                TH1I* dHist_Deltat_Init;
                TH1I* dHist_Deltat_Final[2][5];

                TH2I* dHist_ProtonP_Theta_Init2[2][5];
                TH1I* dHist_BeamP4xx;
                TH1I* dHist_BeamP4tt;
                TH1I* dHist_BeamP4px;
                TH1I* dHist_BeamP4ee;
                
                TH1I* dHist_PhotonP4;
                TH1I* dHist_ProtonP4;
                TH1I* dHist_BeamP4_Measured;
                TH1I* dHist_PhotonP4_Measured;
                TH1I* dHist_ProtonP4_Measured;
                TH1I* dHist_BeamX4_Measured;
                TH1I* dHist_PhotonX4_Measured;
                TH1I* dHist_ProtonX4_Measured;
                TH1I* dHist_PBCALPreShowerE;
                TH1I* dHist_PBCALShowerE;
                TH1I* dHist_PFCALShowerE;
                TH1I* dHist_PSLBCALShower;
                TH1I* dHist_PSTBCALShower;
                TH1I* dHist_PSTrBCALShower;
                TH1I* dHist_RFT;
                TH1I* dHist_BDT;
                TH1I* dHist_TCM;
                TH1I* dHist_loct;
                TH1I* dHist_locu;
                TH1I* dHist_locs;
                TH1I* dHist_Photonp;
                TH1I* dHist_Photont;
                TH1I* dHist_Photontdelta;
                //TH1F* dHist_Protonp;
                TH1I* dHist_Protont;
                TH1F* dHist_ProtonPhi;
                TH1F* dHist_ProtonPhi1;
                TH1F* dHist_ProtonPhi2;
                TH1F* dHist_ProtonPhi11;
                TH1F* dHist_ProtonPhi22;
                TH1I* dHist_VertZ;
                TH1I* dHist_VertR;
                TH1I* dHist_MMS;
                TH1I* dHist_ME;
                TH1I* dHist_unusedEnergyB;
                TH1I* dHist_unusedEnergyF;
                TH1I* dHist_DT;
                TH1I* dHist_DE;
                TH1I* dHist_DP;
                TH1F* dHist_ProtonPhi_O_F[2][6], *dHist_ProtonPhi_O_B[2][6], *dHist_ProtonPhi_O_F2[2][6], *dHist_ProtonPhi_O_B2[2][6];
                TH1F* dHist_ProtonPhi_dPhi_F[2][6];
                
                TH1F* dHist_ProtonPhi_dPhi5_F[2][6];
                TH1F* dHist_ProtonPhi_5dPhi_F[2][6];
                TH1F* dHist_ProtonPhi_dE_F[2][6], *dHist_ProtonPhi_dTheta_F[2][6];
                TH1F* dHist_ProtonPhi_Shower_F[2][6], *dHist_ProtonPhi_dPhi_B[2][6], *dHist_ProtonPhi_dPhi5_B[2][6], *dHist_ProtonPhi_5dPhi_B[2][6];
                TH1F* dHist_ProtonPhi_dE_B[2][6];
                TH1F* dHist_ProtonPhi_dTheta_B[2][6], *dHist_ProtonPhi_Shower_B[2][6], *dHist_ProtonPhi_dPhi_F2[2][6];
                TH1F* dHist_ProtonPhi_dE_F2[2][6], *dHist_ProtonPhi_dPhi5_F2[2][6], *dHist_ProtonPhi_5dPhi_F2[2][6], *dHist_ProtonPhi_dTheta_F2[2][6];
                TH1F* dHist_ProtonPhi_Shower_F2[2][6], *dHist_ProtonPhi_dPhi_B2[2][6], *dHist_ProtonPhi_dPhi5_B2[2][6], *dHist_ProtonPhi_5dPhi_B2[2][6];
                TH1F* dHist_ProtonPhi_dE_B2[2][6], *dHist_ProtonPhi_dTheta_B2[2][6], *dHist_ProtonPhi_Shower_B2[2][6];
                TH1F* dHist_ProtonPhi_SigTrans_F[2][6], *dHist_ProtonPhi_SigTrans_F2[2][6], *dHist_ProtonPhi_SigTrans_B[2][6], *dHist_ProtonPhi_SigTrans_B2[2][6];
                TH1F* dHist_ProtonPhi_SigTheta_F[2][6], *dHist_ProtonPhi_SigTheta_F2[2][6], *dHist_ProtonPhi_SigTheta_B[2][6], *dHist_ProtonPhi_SigTheta_B2[2][6];
                TH1F* dHist_ProtonPhi_SigLong_F[2][6], *dHist_ProtonPhi_SigLong_F2[2][6], *dHist_ProtonPhi_SigLong_B[2][6], *dHist_ProtonPhi_SigLong_B2[2][6];

                TH1F*  dHist_DeltaPhiFCALpre[2][2];
                TH1F*  dHist_DeltaPhiBCALpre[2][2];
                TH1F*  dHist_Shower_FCALpre[2][2];
                TH1F*  dHist_Shower_BCALpre[2][2];
                TH1F*  dHist_DeltaPhi_L5FCALpre[2][2], *dHist_DeltaPhi_G5FCALpre[2][2], *dHist_DeltaPhi_L5BCALpre[2][2], *dHist_DeltaPhi_G5BCALpre[2][2];
                TH2I*  dHist_DeltaE_Theta_FCALpre[2][2];
                TH2I*  dHist_DeltaE_Theta_BCALpre[2][2];
                TH1F*  dHist_SigTrans_FCALpre[2][2];
                TH1F*  dHist_SigTheta_FCALpre[2][2];
                TH1F*  dHist_SigLong_FCALpre[2][2], *dHist_SigTrans_BCALpre[2][2], *dHist_SigTheta_BCALpre[2][2], *dHist_SigLong_BCALpre[2][2];

                TH1F*  dHist_DeltaPhiFCALpost[2][2];
                TH1F*  dHist_DeltaPhiBCALpost[2][2];
                TH1F*  dHist_Shower_FCALpost[2][2];
                TH1F*  dHist_Shower_BCALpost[2][2];
                TH1F*  dHist_DeltaPhi_L5FCALpost[2][2], *dHist_DeltaPhi_G5FCALpost[2][2], *dHist_DeltaPhi_L5BCALpost[2][2], *dHist_DeltaPhi_G5BCALpost[2][2];
                TH2I*  dHist_DeltaE_Theta_FCALpost[2][2];
                TH2I*  dHist_DeltaE_Theta_BCALpost[2][2];
                TH1F*  dHist_SigTrans_FCALpost[2][2];
                TH1F*  dHist_SigTheta_FCALpost[2][2];
                TH1F*  dHist_SigLong_FCALpost[2][2], *dHist_SigTrans_BCALpost[2][2], *dHist_SigTheta_BCALpost[2][2], *dHist_SigLong_BCALpost[2][2];

                TH1F* dHist_SigLongYield[2][5], *dHist_SigThetaYield[2][5], *dHist_SigTransYield[2][5];
                TH1F* dHist_SigLongYield2[2][5], *dHist_SigThetaYield2[2][5], *dHist_SigTransYield2[2][5];
                
                TH1F* dHist_SigLongPure_DPlessThan_F[2], *dHist_SigThetaPure_DPlessThan_F[2], *dHist_SigTransPure_DPlessThan_F[2];
                TH1F* dHist_SigLongPure_DPgraThan_F[2], *dHist_SigThetaPure_DPgraThan_F[2], *dHist_SigTransPure_DPgraThan_F[2];

                TH1F* dHist_SigLongPure_DPlessThan_B[2], *dHist_SigThetaPure_DPlessThan_B[2], *dHist_SigTransPure_DPlessThan_B[2];
                TH1F* dHist_SigLongPure_DPgraThan_B[2], *dHist_SigThetaPure_DPgraThan_B[2], *dHist_SigTransPure_DPgraThan_B[2];

                TH1F* dHist_SigLongPure_DPlessThan_F_SignalCutComp[2], *dHist_SigThetaPure_DPlessThan_F_SignalCutComp[2], *dHist_SigTransPure_DPlessThan_F_SignalCutComp[2];
                TH1F* dHist_SigLongPure_DPgraThan_F_SignalCutComp[2], *dHist_SigThetaPure_DPgraThan_F_SignalCutComp[2], *dHist_SigTransPure_DPgraThan_F_SignalCutComp[2];

                TH1F* dHist_SigLongPure_DPlessThan_B_SignalCutComp[2], *dHist_SigThetaPure_DPlessThan_B_SignalCutComp[2], *dHist_SigTransPure_DPlessThan_B_SignalCutComp[2];
                TH1F* dHist_SigLongPure_DPgraThan_B_SignalCutComp[2], *dHist_SigThetaPure_DPgraThan_B_SignalCutComp[2], *dHist_SigTransPure_DPgraThan_B_SignalCutComp[2];

                TH1F* dHist_SigLongPure_DPlessThan_F_SignalCutPi0[2], *dHist_SigThetaPure_DPlessThan_F_SignalCutPi0[2], *dHist_SigTransPure_DPlessThan_F_SignalCutPi0[2];
                TH1F* dHist_SigLongPure_DPgraThan_F_SignalCutPi0[2], *dHist_SigThetaPure_DPgraThan_F_SignalCutPi0[2], *dHist_SigTransPure_DPgraThan_F_SignalCutPi0[2];

                TH1F* dHist_SigLongPure_DPlessThan_B_SignalCutPi0[2], *dHist_SigThetaPure_DPlessThan_B_SignalCutPi0[2], *dHist_SigTransPure_DPlessThan_B_SignalCutPi0[2];
                TH1F* dHist_SigLongPure_DPgraThan_B_SignalCutPi0[2], *dHist_SigThetaPure_DPgraThan_B_SignalCutPi0[2], *dHist_SigTransPure_DPgraThan_B_SignalCutPi0[2];

                TH2F* dHist_SigLong_SigTrans_DPlessThan_B_SignalCutComp[2], *dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutComp[2], *dHist_SigLong_SigTheta_DPlessThan_B_SignalCutComp[2];
                TH2F* dHist_SigLong_SigTrans_DPlessThan_B_SignalCutPi0[2], *dHist_SigTrans_SigTheta_DPlessThan_B_SignalCutPi0[2], *dHist_SigLong_SigTheta_DPlessThan_B_SignalCutPi0[2];

                TH2F* dHist_SigTrans_PhotonP[2], *dHist_SigTrans_PhotonTheta[2], *dHist_SigTrans_PhotonPhi[2], *dHist_SigTrans_PhotonThetaDet[2];

                TH2F* dHist_SigTrans_ProtonP[2], *dHist_SigTrans_ProtonTheta[2], *dHist_SigTrans_ProtonPhi[2], *dHist_SigTrans_ProtonThetaDet[2];
                TH2F* dHist_SigTrans_ThetaCM[2], *dHist_SigTrans_DeltaTheta[2], *dHist_SigTrans_DeltaE[2], *dHist_SigTrans_DeltaPhi[2];

                TH2F* dHist_SigTrans_BeamE[2], *dHist_SigTrans_PBCALPreShower[2], *dHist_SigTrans_PrBCALSE[2],*dHist_SigTrans_PBCALSE[2], *dHist_SigTrans_PFCALSE[2];
                TH2F* dHist_SigTrans_t[2], *dHist_SigTrans_s[2], *dHist_SigTrans_u[2];
                
                TH2F* dHist_SigTrans_MMS[2], *dHist_SigTrans_ME[2];

                TH2F* dHist_SigTrans_VertexZ[2], *dHist_SigTrans_VertexR[2];
                TH2F* dHist_SigTrans_TrackBCALDP[2], *dHist_SigTrans_TrackBCALVZ[2], *dHist_SigTrans_TrackFCALDoca[2];

                TH2F* dHist_SigTrans_dEdxCDC[2], *dHist_SigTrans_dEdxFDC[2];
                TH1I* dHist_PhotonBCALShowerZ;
                TH2F* dHist_SigTrans_PhotonBCALShowerZ[2];
                TH2F* dHist_SigTrans_EPreEShower[2]; TH1F* dHist_EPre_EShower; TH2F* dHist_EPre___EShower[2];
                TH1F*  dHist_PhotonBCALShowerZ_less, *dHist_PhotonBCALShowerZ_greater, *dHist_PBCALPreShowerE_less, *dHist_PBCALPreShowerE_greater, *dHist_PBCALShowerE_less, *dHist_PBCALShowerE_greater;

//
                TH2F* dHist_SigTheta_PhotonP[2], *dHist_SigTheta_PhotonTheta[2], *dHist_SigTheta_PhotonPhi[2], *dHist_SigTheta_PhotonThetaDet[2];

                TH2F* dHist_SigTheta_ProtonP[2], *dHist_SigTheta_ProtonTheta[2], *dHist_SigTheta_ProtonPhi[2], *dHist_SigTheta_ProtonThetaDet[2];
                TH2F* dHist_SigTheta_ThetaCM[2], *dHist_SigTheta_DeltaTheta[2], *dHist_SigTheta_DeltaE[2], *dHist_SigTheta_DeltaPhi[2];

                TH2F *dHist_SigTheta_PBCALPreShower[2], *dHist_SigTheta_PrBCALSE[2],*dHist_SigTheta_PBCALSE[2], *dHist_SigTheta_PFCALSE[2];
                TH2F* dHist_SigTheta_t[2], *dHist_SigTheta_s[2], *dHist_SigTheta_u[2];

                TH2F* dHist_SigTheta_MMS[2], *dHist_SigTheta_ME[2];

                TH2F* dHist_SigTheta_VertexZ[2], *dHist_SigTheta_VertexR[2];

                TH2F* dHist_SigTheta_dEdxCDC[2], *dHist_SigTheta_dEdxFDC[2];
                TH2F* dHist_SigTheta_PhotonBCALShowerZ[2];
                TH2F* dHist_SigTheta_EPreEShower[2];

//


TH2F* dHist_SigLong_PhotonP[2], *dHist_SigLong_PhotonTheta[2], *dHist_SigLong_PhotonPhi[2], *dHist_SigLong_PhotonThetaDet[2];

                TH2F* dHist_SigLong_ProtonP[2], *dHist_SigLong_ProtonTheta[2], *dHist_SigLong_ProtonPhi[2], *dHist_SigLong_ProtonThetaDet[2];
                TH2F* dHist_SigLong_ThetaCM[2], *dHist_SigLong_DeltaTheta[2], *dHist_SigLong_DeltaE[2], *dHist_SigLong_DeltaPhi[2];

                TH2F *dHist_SigLong_PBCALPreShower[2], *dHist_SigLong_PrBCALSE[2],*dHist_SigLong_PBCALSE[2], *dHist_SigLong_PFCALSE[2];
                TH2F* dHist_SigLong_t[2], *dHist_SigLong_s[2], *dHist_SigLong_u[2];

                TH2F* dHist_SigLong_MMS[2], *dHist_SigLong_ME[2];

                TH2F* dHist_SigLong_VertexZ[2], *dHist_SigLong_VertexR[2];

                TH2F* dHist_SigLong_dEdxCDC[2], *dHist_SigLong_dEdxFDC[2];
                TH2F* dHist_SigLong_PhotonBCALShowerZ[2];
                TH2F* dHist_SigLong_EPreEShower[2];

                TH2F* dHist_SigTrans_SigTheta_varyLess_PhotonThetaDet[2], *dHist_SigTrans_SigTheta_varyMore_PhotonThetaDet[2];
                TH2F* dHist_SigTrans_SigTheta_varyLess_ME[2], *dHist_SigTrans_SigTheta_varyMore_ME[2];
                TH2F* dHist_SigTrans_SigTheta_varyLess_PBCALPreShowerE[2], *dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE[2];
                TH2F* dHist_SigLong_SigTheta_varyLess_PBCALPreShowerE[2], *dHist_SigLong_SigTheta_varyMore_PBCALPreShowerE[2];
                TH2F* dHist_SigTrans_SigLong_varyLess_PBCALPreShowerE[2], *dHist_SigTrans_SigLong_varyMore_PBCALPreShowerE[2];
                TH2F* dHist_BCALSigTrans_SigLong_Normal[2], *dHist_BCALSigTrans_SigTheta_Normal[2], *dHist_BCALSigLong_SigTheta_Normal[2];
                TH2F* dHist_SigTrans_PhotonThetaDet_varyLess_PBCALPreShowerE[2], *dHist_SigTrans_PhotonThetaDet_varyMore_PBCALPreShowerE[2];
                TH1F* dHist_SigTrans_varyMore_PBCALPreShowerE[2], *dHist_SigLong_varyMore_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_PBCALPreShowerE[2];

                TH1F* dHist_SigTrans_varyLess_PBCALPreShowerE[2], *dHist_SigLong_varyLess_PBCALPreShowerE[2], *dHist_SigTheta_varyLess_PBCALPreShowerE[2];

                TH2F* dHist_EPre_EShower_PhotonThetaDet[2];

                TH2F *dHist_EPreShower_PhotonThetaDet[2], *dHist_EPre_EShower_PhotonThetaDet_varyMore[2], *dHist_EPreShower_PhotonThetaDet_varyMore[2];

                TH2F *dHist_EPreEShower_EPreShower[2],*dHist_EPreEShower_EShower[2], *dHist_EPreEShower_EPreShower_varyMore[2],*dHist_EPreEShower_EShower_varyMore[2];

                TH2F *dHist_EShower_EPreShower[2],*dHist_EShower_EPreShower_varyMore[2];

                TH2F *dHist_SigTheta_EPreEShower_varyMore[2], *dHist_SigLong_EPreEShower_varyMore[2], *dHist_SigTrans_EPreEShower_varyMore[2];
                
                TH1F* dHist_SigTrans_varyLess_PBCALPreShowerE[2], *dHist_SigLong_varyLess_PBCALPreShowerE[2], *dHist_SigTheta_varyLess_PBCALPreShowerE[2];

                TH2F* dHist_EPre_EShower_PhotonThetaDet[2];

                TH2F *dHist_EPreShower_PhotonThetaDet[2], *dHist_EPre_EShower_PhotonThetaDet_varyMore[2], *dHist_EPreShower_PhotonThetaDet_varyMore[2];

                TH2F *dHist_EPreEShower_EPreShower[2],*dHist_EPreEShower_EShower[2], *dHist_EPreEShower_EPreShower_varyMore[2],*dHist_EPreEShower_EShower_varyMore[2];

                TH2F *dHist_EShower_EPreShower[2],*dHist_EShower_EPreShower_varyMore[2];

                TH2F *dHist_SigTheta_EPreEShower_varyMore[2], *dHist_SigLong_EPreEShower_varyMore[2], *dHist_SigTrans_EPreEShower_varyMore[2];

                TH1F *dHist_SigTrans_varyMore_105_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_105_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_11_PBCALPreShowerE[2],  *dHist_SigTheta_varyMore_11_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_115_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_115_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_12_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_12_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_125_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_125_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_13_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_13_PBCALPreShowerE[2];


                TH1F *dHist_SigTrans_varyMore_90_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_90_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_925_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_925_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_95_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_95_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_975_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_975_PBCALPreShowerE[2];

                TH1F *dHist_SigTrans_varyMore_80_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_80_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_825_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_825_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_85_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_85_PBCALPreShowerE[2];
                TH1F *dHist_SigTrans_varyMore_875_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_875_PBCALPreShowerE[2];

                TH2F *dHist_SigTrans_SigTheta_varyMore_PBCALPreShowerE_Scale[2];

            TH1F *dHist_SigTheta_varyMore_piCut_0012_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_0009_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_00075_PBCALPreShowerE[2];
                TH1F *dHist_Delta_Phi[2], *dHist_Delta_Energy_O[2], *dHist_Delta_Energy_Up[2], *dHist_Delta_Theta_O[2], *dHist_Delta_Theta_Up[2];

                TH2F* dHist_DeltaPhi_t[2];
                TH1F *dHist_SigTheta_varyMore_piCut_0013_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_00125_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_00115_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_0011_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_00105_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_001_PBCALPreShowerE[2], *dHist_SigTheta_varyMore_piCut_00095_PBCALPreShowerE[2];

                TH1F* dHist_dPhi_Final[2];


                TH2F* dHist_BCALSigTrans_SigLong_Normal_cutsApplied[2], *dHist_BCALSigTrans_SigTheta_Normal_cutsApplied[2], *dHist_BCALSigLong_SigTheta_Normal_cutsApplied[2];     
        ClassDef(DSelector_compton, 0);
};

void DSelector_compton::Get_ComboWrappers(void)
{
        //Step 0
        dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
        dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
        dPhotonWrapper = static_cast<DNeutralParticleHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
        dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
}

#endif // DSelector_compton_h

                DChargedTrackHypothesis* dProtonWrapper;
                
