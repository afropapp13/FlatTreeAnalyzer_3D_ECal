#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"

#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGraph.h>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

#include "../myClasses/myFunctions.cpp"
#include "../myClasses/Constants.h"
#include "../myClasses/STV_Tools.h"
#include "../myClasses/Tools.h"

using namespace std;
using namespace Constants;

//----------------------------------------//

void FlatTreeAnalyzer::Loop() {

	//----------------------------------------//	

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double Units = 1E38; // so that the extracted cross-section is in 10^{-38} cm^{2}
	double A = 40.; // so that we can have xsecs per nucleus

	int NInte = 6; // Interaction processes: All, QE, MEC, RES, DIS, COH
	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS","COH"};

	//----------------------------------------//	

	Tools tools;

	//----------------------------------------//	

        // Output root file

	// Root

	TString FileNameAndPath = "OutputFiles/" + fweights + "FlatTreeAnalyzerOutput_"+fOutputFile+".root";
	TFile* file = new TFile(FileNameAndPath,"recreate");

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;
	std::cout << "File " << FileNameAndPath << " to be created" << std::endl << std::endl;
	
	//----------------------------------------//

	// Plot declaration

	// 1D Fine Binning

	TH1D* TrueFineBinMuonCosThetaPlot[NInte];
	TH1D* TrueFineBinECalPlot[NInte];

	TH2D* TrueFineBinECal2DPlot[NInte];
	TH2D* TrueFineBinq2DPlot[NInte];

	// 1D Nominal Binning

	TH1D* TrueECalPlot[NInte];
	TH1D* TrueMuonCosThetaPlot[NInte];
	TH1D* TrueFineBinMuonCosThetaSingleBinPlot[NInte];

	// 3D Fine Bin Nominal Binning Uncorrelated
	
	TH1D* TrueFineBinECal_InDeltaPnDeltaAlpha3DqTwoDPlot[NInte][TwoDNBinsDeltaPn][TwoDNBinsDeltaAlpha3Dq];
	TH1D* TrueFineBinECal_InDeltaPTDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaPT][TwoDNBinsDeltaAlphaT];
	TH1D* TrueFineBinECal_InMuonCosThetaMuonMomentumTwoDPlot[NInte][TwoDNBinsMuonCosTheta][TwoDNBinsMuonMomentum];
	TH1D* TrueFineBinECal_InProtonCosThetaProtonMomentumTwoDPlot[NInte][TwoDNBinsProtonCosTheta][TwoDNBinsProtonMomentum];

	// 3D Nominal Binning Uncorrelated
	
	TH1D* TrueECal_InDeltaPnDeltaAlpha3DqTwoDPlot[NInte][TwoDNBinsDeltaPn][TwoDNBinsDeltaAlpha3Dq];
	TH1D* TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[NInte][TwoDNBinsDeltaPT][TwoDNBinsDeltaAlphaT];
	TH1D* TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[NInte][TwoDNBinsMuonCosTheta][TwoDNBinsMuonMomentum];
	TH1D* TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[NInte][TwoDNBinsProtonCosTheta][TwoDNBinsProtonMomentum];

	// 3D Nominal Binning Correlated
	
	TH1D* SerialTrueECal_InDeltaPnDeltaAlpha3DqPlot[NInte];
	TH1D* SerialTrueECal_InDeltaPTDeltaAlphaTPlot[NInte];
	TH1D* SerialTrueECal_InMuonCosThetaMuonMomentumPlot[NInte];
	TH1D* SerialTrueECal_InProtonCosThetaProtonMomentumPlot[NInte];

	//----------------------------------------//

	int NFineBinECal = 18;

	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

	  //--------------------------------------------------//

	  // Post FSI

	  // 1D Fine Binning

	  TrueFineBinMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueFineBinMuonCosThetaPlot",";cos#theta_{#mu}",20,-1,1);
	  TrueFineBinECalPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueFineBinECalPlot",";E^{Cal} [GeV]",NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);

	  TrueFineBinECal2DPlot[inte] = new TH2D(InteractionLabels[inte]+"TrueFineBinECal2DPlot",";E_{#nu}^{true} [GeV];E_{Cal} [GeV]",NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal],NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);
	  TrueFineBinq2DPlot[inte] = new TH2D(InteractionLabels[inte]+"TrueFineBinq2DPlot",";q^{true} [GeV];q^{reco} [GeV/c]",NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal],NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);

	  // 1D Nominal Binning

	  TrueECalPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueECalPlot",";E^{Cal} [GeV]",NBinsECal,ArrayNBinsECal);
	  TrueMuonCosThetaPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueMuonCosThetaPlot",";cos#theta_{#mu}",NBinsMuonCosTheta,ArrayNBinsMuonCosTheta);
	  TrueFineBinMuonCosThetaSingleBinPlot[inte] = new TH1D(InteractionLabels[inte]+"TrueFineBinMuonCosThetaSingleBinPlot",";",1,0,1);


	  // 3D Fine & Nominal Binning Uncorrelated

	  for (int WhichDeltaPn = 0; WhichDeltaPn < TwoDNBinsDeltaPn; WhichDeltaPn++) {

	    for (int WhichDeltaAlpha3Dq = 0; WhichDeltaAlpha3Dq < TwoDNBinsDeltaAlpha3Dq; WhichDeltaAlpha3Dq++) {

	      TString ECalTwoDInDeltaPnDeltaAlpha3DqLabel = "ECal_DeltaPn_"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPn[WhichDeltaPn+1])+"_DeltaAlpha3Dq_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3Dq[WhichDeltaAlpha3Dq])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlpha3Dq[WhichDeltaAlpha3Dq+1])+"Plot";
	      
		TrueECal_InDeltaPnDeltaAlpha3DqTwoDPlot[inte][WhichDeltaPn][WhichDeltaAlpha3Dq] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPnDeltaAlpha3DqLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPnDeltaAlpha3DqSlices[WhichDeltaPn][WhichDeltaAlpha3Dq].size()-1,&TwoDArrayNBinsECalInDeltaPnDeltaAlpha3DqSlices[WhichDeltaPn][WhichDeltaAlpha3Dq][0]);

		TrueFineBinECal_InDeltaPnDeltaAlpha3DqTwoDPlot[inte][WhichDeltaPn][WhichDeltaAlpha3Dq] = new TH1D(InteractionLabels[inte]+"TrueFineBin"+ECalTwoDInDeltaPnDeltaAlpha3DqLabel,LabelXAxisECal,NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);

	    }

	  }


	  for (int WhichDeltaPT = 0; WhichDeltaPT < TwoDNBinsDeltaPT; WhichDeltaPT++) {

	    for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {

	      TString ECalTwoDInDeltaPTDeltaAlphaTLabel = "ECal_DeltaPT_"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaPT[WhichDeltaPT+1])+"_DeltaAlphaT_"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT])+"To"+tools.ConvertToString(TwoDArrayNBinsDeltaAlphaT[WhichDeltaAlphaT+1])+"Plot";
	      
		TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[inte][WhichDeltaPT][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInDeltaPTDeltaAlphaTLabel,LabelXAxisECal,TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices[WhichDeltaPT][WhichDeltaAlphaT].size()-1,&TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices[WhichDeltaPT][WhichDeltaAlphaT][0]);

		TrueFineBinECal_InDeltaPTDeltaAlphaTTwoDPlot[inte][WhichDeltaPT][WhichDeltaAlphaT] = new TH1D(InteractionLabels[inte]+"TrueFineBin"+ECalTwoDInDeltaPTDeltaAlphaTLabel,LabelXAxisECal,NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);

	    }

	  }

	  for (int WhichMuonCosTheta = 0; WhichMuonCosTheta < TwoDNBinsMuonCosTheta; WhichMuonCosTheta++) {

	    for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {

	      TString ECalTwoDInMuonCosThetaMuonMomentumLabel = "ECal_MuonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonCosTheta[WhichMuonCosTheta+1])+"_MuonMomentum_"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsMuonMomentum[WhichMuonMomentum+1])+"Plot";
	      
		TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[inte][WhichMuonCosTheta][WhichMuonMomentum] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInMuonCosThetaMuonMomentumLabel,LabelXAxisECal,TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices[WhichMuonCosTheta][WhichMuonMomentum].size()-1,&TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices[WhichMuonCosTheta][WhichMuonMomentum][0]);

		TrueFineBinECal_InMuonCosThetaMuonMomentumTwoDPlot[inte][WhichMuonCosTheta][WhichMuonMomentum] = new TH1D(InteractionLabels[inte]+"TrueFineBin"+ECalTwoDInMuonCosThetaMuonMomentumLabel,LabelXAxisECal,NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);


	    }

	  }

	  for (int WhichProtonCosTheta = 0; WhichProtonCosTheta < TwoDNBinsProtonCosTheta; WhichProtonCosTheta++) {

	    for (int WhichProtonMomentum = 0; WhichProtonMomentum < TwoDNBinsProtonMomentum; WhichProtonMomentum++) {

	      TString ECalTwoDInProtonCosThetaProtonMomentumLabel = "ECal_ProtonCosTheta_"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonCosTheta[WhichProtonCosTheta+1])+"_ProtonMomentum_"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum])+"To"+tools.ConvertToString(TwoDArrayNBinsProtonMomentum[WhichProtonMomentum+1])+"Plot";
	      TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[inte][WhichProtonCosTheta][WhichProtonMomentum] = new TH1D(InteractionLabels[inte]+"True"+ECalTwoDInProtonCosThetaProtonMomentumLabel,LabelXAxisECal,TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices[WhichProtonCosTheta][WhichProtonMomentum].size()-1,&TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices[WhichProtonCosTheta][WhichProtonMomentum][0]);

	      TrueFineBinECal_InProtonCosThetaProtonMomentumTwoDPlot[inte][WhichProtonCosTheta][WhichProtonMomentum] = new TH1D(InteractionLabels[inte]+"TrueFineBin"+ECalTwoDInProtonCosThetaProtonMomentumLabel,LabelXAxisECal,NFineBinECal,ArrayNBinsECal[0],ArrayNBinsECal[NBinsECal]);

	    }

	  }

	  // 3D Nominal Binning Correlated
	
	  SerialTrueECal_InDeltaPnDeltaAlpha3DqPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialTrueECal_DeltaPnDeltaAlpha3DqPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInDeltaPnDeltaAlpha3DqSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInDeltaPnDeltaAlpha3DqSlices)[0]);  
	  SerialTrueECal_InDeltaPTDeltaAlphaTPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialTrueECal_DeltaPTDeltaAlphaTPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices)[0]);
	  SerialTrueECal_InMuonCosThetaMuonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialTrueECal_MuonCosThetaMuonMomentumPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices)[0]);
	  SerialTrueECal_InProtonCosThetaProtonMomentumPlot[inte] = new TH1D(InteractionLabels[inte]+"SerialTrueECal_ProtonCosThetaProtonMomentumPlot",LabelXAxisECal,tools.Return3DNBins(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices),&tools.Return3DBinIndices(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices)[0]);

	  //--------------------------------------------------//

	} // End of the loop over the interaction processes							

	//----------------------------------------//

	// Counters

	int CounterEventsPassedSelection = 0;

	//----------------------------------------//
	
	// Loop over the events
	cout << "nentries = " << nentries << endl;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

	  //----------------------------------------//	
	
	  Long64_t ientry = LoadTree(jentry);
	  if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;
	  if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

	  //----------------------------------------//			

	  double weight = fScaleFactor*Units*A*Weight;	
	  if (fOutputFile == "GiBUU_2023") { weight = weight/500.; } // To increase the stats, the GiBUU sample has been produced in 500 samples	

	  //----------------------------------------//	

	  // Signal definition

	  if (PDGLep != 13) { continue; } // make sure that we have only a muon in the final state
	  if (cc != 1) { continue; } // make sure that we have only CC interactions		

	  int ProtonTagging = 0, ChargedPionTagging = 0, NeutralPionTagging = 0, MuonTagging = 0, TrueHeavierMesonCounter = 0;
          int ElectronTagging = 0, PhotonTagging = 0;	
	  vector <int> ProtonID; ProtonID.clear();
	  vector <int> MuonID; MuonID.clear();		

	  //----------------------------------------//	

	  // Loop over the final state particles / post FSI

	  for (int i = 0; i < nfsp; i++) {
		
	    double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
	    
              if (pdg[i] == 13 && (pf > 0.1 && pf < 1.2) ) {

	      MuonTagging ++;
	      MuonID.push_back(i);

	    }

	    if (pdg[i] == 2212 && (pf > 0.3 && pf < 1.) ) {

	      ProtonTagging ++;
	      ProtonID.push_back(i);

	    }

	    if (fabs(pdg[i]) == 211 && pf > 0.07)  {

	      ChargedPionTagging ++;

	    }

	    if (pdg[i] == 111)  {

	      NeutralPionTagging ++;

	    }

	    if (fabs(pdg[i]) == 11)  {

	      ElectronTagging++;

	    }

	    if (fabs(pdg[i]) == 22)  {

	      PhotonTagging++;

	    }


	    if ( pdg[i] != NeutralPionPdg && fabs(pdg[i]) != AbsChargedPionPdg && tools.is_meson_or_antimeson(pdg[i]) ) { TrueHeavierMesonCounter++; }


	  } // End of the loop over the final state particles / post FSI

	  //----------------------------------------//	

	  // Classify the events based on the interaction type

	  // https://arxiv.org/pdf/2106.15809.pdf

	  int genie_mode = -1.;

	  if (TMath::Abs(Mode) == 1) { genie_mode = 1; } // QE
	  else if (TMath::Abs(Mode) == 2) { genie_mode = 2; } // MEC
	  else if (
		   TMath::Abs(Mode) == 10 ||
		   TMath::Abs(Mode) == 11 || TMath::Abs(Mode) == 12 || TMath::Abs(Mode) == 13 ||
		   TMath::Abs(Mode) == 17 || TMath::Abs(Mode) == 22 || TMath::Abs(Mode) == 23
		   ) { genie_mode = 3; } // RES
	  else if (TMath::Abs(Mode) == 21 || TMath::Abs(Mode) == 26) { genie_mode = 4; } // DIS
	  else if (TMath::Abs(Mode) == 16) { genie_mode = 5;} // COH
	  else { continue; }  

	  // Feb 8 2022: Only case that is not covered is 15 = diffractive

	  //----------------------------------------//	

	  // If the signal definition post-FSI  is satisfied
	  if ( ProtonTagging == 1 && ChargedPionTagging == 0 && NeutralPionTagging == 0 && MuonTagging == 1 && TrueHeavierMesonCounter == 0) { 

	    CounterEventsPassedSelection++;

	    // Kinematics of muon & proton in the final state

	    TLorentzVector Muon4Vector(px[MuonID[0]], py[MuonID[0]], pz[MuonID[0]], E[MuonID[0]]);
	    TLorentzVector Proton4Vector(px[ProtonID[0]], py[ProtonID[0]], pz[ProtonID[0]], E[ProtonID[0]]);

	    //----------------------------------------//

	    // Variables of interest

	    STV_Tools reco_stv_tool(Muon4Vector.Vect(),Proton4Vector.Vect(),Muon4Vector.E(),TMath::Sqrt( TMath::Power(Proton4Vector.Rho(),2.) + TMath::Power(ProtonMass_GeV,2.) ) );

	    double MuonMomentum = Muon4Vector.Rho();
	    double ProtonMomentum = Proton4Vector.Rho();
	    double MuonCosTheta = Muon4Vector.CosTheta();
	    double ProtonCosTheta = Proton4Vector.CosTheta();
	    double DeltaPT = reco_stv_tool.ReturnPt();
	    double DeltaAlphaT = reco_stv_tool.ReturnDeltaAlphaT();
	    double DeltaAlpha3Dq = reco_stv_tool.ReturnDeltaAlpha3Dq();
	    double DeltaPn = reco_stv_tool.ReturnPn();
	    double ECal = reco_stv_tool.ReturnECalMB();
	    double qtrue = Enu_true - Muon4Vector.E();
	    double qreco = ECal - Muon4Vector.E();


	    //----------------------------------------//

	    // filling in the histo regardless of interaction mode

	    // 1D Fine Binning

	    TrueFineBinMuonCosThetaPlot[0]->Fill(MuonCosTheta,weight);
	    TrueFineBinECalPlot[0]->Fill(ECal,weight);
	    
	    // Nominal binning
	    TrueECalPlot[0]->Fill(ECal,weight);
	    TrueMuonCosThetaPlot[0]->Fill(MuonCosTheta,weight);
	    TrueFineBinMuonCosThetaSingleBinPlot[0]->Fill(0.5,weight);

	    TrueFineBinECal2DPlot[0]->Fill(Enu_true,ECal,weight);
	    TrueFineBinq2DPlot[0]->Fill(qtrue,qreco,weight);

	    // filling in the histo based on the interaction mode

	    // 1D Fine Binning

	    TrueFineBinMuonCosThetaPlot[genie_mode]->Fill(MuonCosTheta,weight);
	    TrueFineBinECalPlot[genie_mode]->Fill(ECal,weight);
	  
	    // Nominal binning
	    TrueECalPlot[genie_mode]->Fill(ECal,weight);
	    TrueMuonCosThetaPlot[genie_mode]->Fill(MuonCosTheta,weight);
	    TrueFineBinMuonCosThetaSingleBinPlot[genie_mode]->Fill(0.5,weight);

	    TrueFineBinECal2DPlot[genie_mode]->Fill(Enu_true,ECal,weight);
            TrueFineBinq2DPlot[genie_mode]->Fill(qtrue,qreco,weight);

	    //----------------------------------------//

	    // Indices for 3D analysis

	    int DeltaPTTwoDIndex = tools.ReturnIndex(DeltaPT, TwoDArrayNBinsDeltaPT); 
	    if (DeltaPTTwoDIndex < 0) { continue; }
	    int DeltaPnTwoDIndex = tools.ReturnIndex(DeltaPn, TwoDArrayNBinsDeltaPn);
	    if (DeltaPnTwoDIndex < 0) { continue; }
	    int DeltaAlphaTTwoDIndex = tools.ReturnIndex(DeltaAlphaT, TwoDArrayNBinsDeltaAlphaT);
	    if (DeltaAlphaTTwoDIndex < 0) { continue; }
	    int DeltaAlpha3DqTwoDIndex = tools.ReturnIndex(DeltaAlpha3Dq, TwoDArrayNBinsDeltaAlpha3Dq);
	    if (DeltaAlpha3DqTwoDIndex < 0) { continue; }

	    int MuonMomentumTwoDIndex = tools.ReturnIndex(MuonMomentum, TwoDArrayNBinsMuonMomentum);
	    if (MuonMomentumTwoDIndex < 0) { cout << "MuonMomentumTwoDIndex = " << MuonMomentumTwoDIndex << endl; }
	    int ProtonMomentumTwoDIndex = tools.ReturnIndex(ProtonMomentum, TwoDArrayNBinsProtonMomentum);
	    if (ProtonMomentumTwoDIndex < 0) { cout << "ProtonMomentumTwoDIndex = " << ProtonMomentumTwoDIndex << endl; }
	    int MuonCosThetaTwoDIndex = tools.ReturnIndex(MuonCosTheta, TwoDArrayNBinsMuonCosTheta);
	    if (MuonMomentumTwoDIndex < 0) { cout << "MuonMomentumTwoDIndex = " << MuonMomentumTwoDIndex << endl; }
	    int ProtonCosThetaTwoDIndex = tools.ReturnIndex(ProtonCosTheta, TwoDArrayNBinsProtonCosTheta);
	    if (ProtonMomentumTwoDIndex < 0) { cout << "ProtonMomentumTwoDIndex = " << ProtonMomentumTwoDIndex << endl; }

	    int SerialECalInDeltaPnDeltaAlpha3DqIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInDeltaPnDeltaAlpha3DqSlices,DeltaPnTwoDIndex,DeltaAlpha3DqTwoDIndex,ECal);	
	    int SerialECalInDeltaPTDeltaAlphaTIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInDeltaPTDeltaAlphaTSlices,DeltaPTTwoDIndex,DeltaAlphaTTwoDIndex,ECal);
	    int SerialECalInMuonCosThetaMuonMomentumIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInMuonCosThetaMuonMomentumSlices,MuonCosThetaTwoDIndex,MuonMomentumTwoDIndex,ECal);
	    int SerialECalInProtonCosThetaProtonMomentumIndex = tools.ReturnIndexIn3DList(TwoDArrayNBinsECalInProtonCosThetaProtonMomentumSlices,ProtonCosThetaTwoDIndex,ProtonMomentumTwoDIndex,ECal);

	    //----------------------------------------//

	    // ECal overflow / underflow bins

	    if (ECal > ArrayNBinsECal[NBinsECal]) { ECal = 0.5 * (ArrayNBinsECal[NBinsECal] + ArrayNBinsECal[NBinsECal-1]); }
	    if (ECal < ArrayNBinsECal[0]) { ECal = 0.5 * (ArrayNBinsECal[0] + ArrayNBinsECal[1]); }


	    // 3D filling for all events

	    TrueECal_InDeltaPnDeltaAlpha3DqTwoDPlot[0][DeltaPnTwoDIndex][DeltaAlpha3DqTwoDIndex]->Fill(ECal,weight);	
	    TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[0][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
	    TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[0][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
	    TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[0][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);

	    TrueFineBinECal_InDeltaPnDeltaAlpha3DqTwoDPlot[0][DeltaPnTwoDIndex][DeltaAlpha3DqTwoDIndex]->Fill(ECal,weight);
	    TrueFineBinECal_InDeltaPTDeltaAlphaTTwoDPlot[0][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
	    TrueFineBinECal_InMuonCosThetaMuonMomentumTwoDPlot[0][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
	    TrueFineBinECal_InProtonCosThetaProtonMomentumTwoDPlot[0][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);

	    SerialTrueECal_InDeltaPnDeltaAlpha3DqPlot[0]->Fill(SerialECalInDeltaPnDeltaAlpha3DqIndex,weight);	
	    SerialTrueECal_InDeltaPTDeltaAlphaTPlot[0]->Fill(SerialECalInDeltaPTDeltaAlphaTIndex,weight);
	    SerialTrueECal_InMuonCosThetaMuonMomentumPlot[0]->Fill(SerialECalInMuonCosThetaMuonMomentumIndex,weight);
	    SerialTrueECal_InProtonCosThetaProtonMomentumPlot[0]->Fill(SerialECalInProtonCosThetaProtonMomentumIndex,weight);

	    // 3D filling based on interaction mode

	    TrueECal_InDeltaPnDeltaAlpha3DqTwoDPlot[genie_mode][DeltaPnTwoDIndex][DeltaAlpha3DqTwoDIndex]->Fill(ECal,weight);	
	    TrueECal_InDeltaPTDeltaAlphaTTwoDPlot[genie_mode][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
	    TrueECal_InMuonCosThetaMuonMomentumTwoDPlot[genie_mode][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
	    TrueECal_InProtonCosThetaProtonMomentumTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);

	    TrueFineBinECal_InDeltaPnDeltaAlpha3DqTwoDPlot[genie_mode][DeltaPnTwoDIndex][DeltaAlpha3DqTwoDIndex]->Fill(ECal,weight);	
	    TrueFineBinECal_InDeltaPTDeltaAlphaTTwoDPlot[genie_mode][DeltaPTTwoDIndex][DeltaAlphaTTwoDIndex]->Fill(ECal,weight);
	    TrueFineBinECal_InMuonCosThetaMuonMomentumTwoDPlot[genie_mode][MuonCosThetaTwoDIndex][MuonMomentumTwoDIndex]->Fill(ECal,weight);
	    TrueFineBinECal_InProtonCosThetaProtonMomentumTwoDPlot[genie_mode][ProtonCosThetaTwoDIndex][ProtonMomentumTwoDIndex]->Fill(ECal,weight);

	    SerialTrueECal_InDeltaPTDeltaAlphaTPlot[genie_mode]->Fill(SerialECalInDeltaPTDeltaAlphaTIndex,weight);
	    SerialTrueECal_InMuonCosThetaMuonMomentumPlot[genie_mode]->Fill(SerialECalInMuonCosThetaMuonMomentumIndex,weight);
	    SerialTrueECal_InProtonCosThetaProtonMomentumPlot[genie_mode]->Fill(SerialECalInProtonCosThetaProtonMomentumIndex,weight);

	    //----------------------------------------//

	  } // End of the post-FSI selection

	  //----------------------------------------//

	} // End of the loop over the events

	//----------------------------------------//	

	std::cout << "Percetage of events passing the selection cuts = " << 
	double(CounterEventsPassedSelection)/ double(nentries)*100. << " %" << std::endl; std::cout << std::endl;

	//----------------------------------------//	
	//----------------------------------------//	

	// The serial plots don't need to be rebinned because the bin width is 1
	// The nominal bin plots also shouldn't be divided by the bin width because we first need to multiply by Ac and then divide by the bin width

	// Division by bin width to get the cross sections only for the finely binned plots
	// Loop over the interaction processes

	for (int inte = 0; inte < NInte; inte++) {

		//----------------------------------------//
	
	        // 1D Fine Binning Post FSI

		Reweight(TrueFineBinMuonCosThetaPlot[inte]);
		Reweight(TrueFineBinECalPlot[inte]);

		// 3D Fine Binning Post FSI
		
		// Loop over the DeltaPn bins

		for (int WhichDeltaPn = 0; WhichDeltaPn < TwoDNBinsDeltaPn; WhichDeltaPn++) {
	
			// Loop over the DeltaAlpha3D bins

			for (int WhichDeltaAlpha3Dq = 0; WhichDeltaAlpha3Dq < TwoDNBinsDeltaAlpha3Dq; WhichDeltaAlpha3Dq++) {	
		
				Reweight(TrueFineBinECal_InDeltaPnDeltaAlpha3DqTwoDPlot[inte][WhichDeltaPn][WhichDeltaAlpha3Dq], 1. / ( (TwoDArrayNBinsDeltaPn.at(WhichDeltaPn+1) - TwoDArrayNBinsDeltaPn.at(WhichDeltaPn)) * (TwoDArrayNBinsDeltaAlpha3Dq.at(WhichDeltaAlpha3Dq+1) - TwoDArrayNBinsDeltaAlpha3Dq.at(WhichDeltaAlpha3Dq)) ) );

			} // End of the loop over DeltaAlpha3Dq bins

		} // End of the loop over the DeltaPn bins

		// Loop over the DeltaPT bins

		for (int WhichDeltaPT = 0; WhichDeltaPT < TwoDNBinsDeltaPT; WhichDeltaPT++) {
	
			// Loop over the DeltaAlphaT bins

			for (int WhichDeltaAlphaT = 0; WhichDeltaAlphaT < TwoDNBinsDeltaAlphaT; WhichDeltaAlphaT++) {	
		
				Reweight(TrueFineBinECal_InDeltaPTDeltaAlphaTTwoDPlot[inte][WhichDeltaPT][WhichDeltaAlphaT], 1. / ( (TwoDArrayNBinsDeltaPT.at(WhichDeltaPT+1) - TwoDArrayNBinsDeltaPT.at(WhichDeltaPT)) * (TwoDArrayNBinsDeltaAlphaT.at(WhichDeltaAlphaT+1) - TwoDArrayNBinsDeltaAlphaT.at(WhichDeltaAlphaT)) ) );

			} // End of the loop over DeltaAlphaT bins

		} // End of the loop over the DeltaPT bins

		for (int WhichMuonCosTheta = 0; WhichMuonCosTheta < TwoDNBinsMuonCosTheta; WhichMuonCosTheta++) {
	
			// Loop over the muon cos theta bins

			for (int WhichMuonMomentum = 0; WhichMuonMomentum < TwoDNBinsMuonMomentum; WhichMuonMomentum++) {	
		
				Reweight(TrueFineBinECal_InMuonCosThetaMuonMomentumTwoDPlot[inte][WhichMuonCosTheta][WhichMuonMomentum], 1. / ( (TwoDArrayNBinsMuonCosTheta.at(WhichMuonCosTheta+1) - TwoDArrayNBinsMuonCosTheta.at(WhichMuonCosTheta)) * (TwoDArrayNBinsMuonMomentum.at(WhichMuonMomentum+1) - TwoDArrayNBinsMuonMomentum.at(WhichMuonMomentum)) ) );

			} // End of the loop over muon momentum bins

		} // End of the loop over the muon cos theta bins


		//----------------------------------------//

	} // End of the loop over the interaction processes		

	//----------------------------------------//		

	file->cd();
	file->Write();
	fFile->Close();

	std::cout << std::endl;
	std::cout << "File " << FileNameAndPath +" has been created" << std::endl; 
	std::cout << std::endl;

	std::cout << std::endl << "------------------------------------------------" << std::endl << std::endl;

	//----------------------------------------//		

} // End of the program

//----------------------------------------//		
