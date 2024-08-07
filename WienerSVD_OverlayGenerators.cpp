#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TEfficiency.h>
#include <TMath.h>
#include <TLatex.h>
#include <TMatrixD.h>
#include <TVectorD.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include "../myClasses/myFunctions.cpp"
#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

#include "../myClasses/Util.h"

//----------------------------------------//

void WienerSVD_OverlayGenerators(bool PlotGENIE = true, bool PlotGen = false, bool PlotACHILLES = false, bool PlotANL_SF = false, bool plot_closure = false, bool plot_gibuu = false, bool plot_mec  = false, bool plot_nuclear = false) {


	//----------------------------------------//

	int DecimalAccuracy = 2;

	TH1D::SetDefaultSumw2();
	gStyle->SetEndErrorSize(6);		

	TString PathToFiles = "/exp/uboone/data/users/"+UserID+"/my3DSTVAnalysis/myXSec/v08_00_00_70/";

	//----------------------------------------//

	TString Extra = "";
	if (PlotGen) { Extra = "Gene"; }
	if (PlotGENIE) { Extra = "Genie"; }
	if (PlotACHILLES) { Extra = "ACHILLES"; }
	if (PlotANL_SF) { Extra = "ANL_SF"; }
	if (plot_closure) { Extra = "Closure"; }
	if (plot_gibuu) { Extra = "gibuu"; }
	if (plot_mec) { Extra = "mec"; }
	if (plot_nuclear) { Extra = "nuclear"; }


	//----------------------------------------//

	vector<TString> PlotNames;
	PlotNames.push_back("ECalPlot");
	PlotNames.push_back("MuonCosThetaPlot");
	PlotNames.push_back("MuonCosThetaSingleBinPlot");
	PlotNames.push_back("SerialECal_DeltaPTDeltaAlphaTPlot");
	PlotNames.push_back("SerialECal_DeltaPnDeltaAlpha3DqPlot");
	PlotNames.push_back("SerialECal_MuonCosThetaMuonMomentumPlot");
	PlotNames.push_back("SerialECal_ProtonCosThetaProtonMomentumPlot");

	const int N1DPlots = PlotNames.size();
	cout << "Number of 1D Plots = " << N1DPlots << endl;

	//----------------------------------------//

	vector<TString> Runs;
	//Runs.push_back("Run5");
	Runs.push_back("Combined");

	int NRuns = (int)(Runs.size());
	cout << "Number of Runs = " << NRuns << endl;

	//----------------------------------------//

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		vector<vector<TH1D*> > PlotsFullUncReco; PlotsFullUncReco.clear();
		vector<vector<TH1D*> > PlotsXSecReco; PlotsXSecReco.clear();
		vector<vector<TH1D*> > PlotsTotalReco; PlotsTotalReco.clear();
		vector<vector<TH1D*> > PlotsNormOnly; PlotsNormOnly.clear();		
		vector<vector<TH1D*> > PlotsReco; PlotsReco.clear();
		vector<vector<TH1D*> > PlotsCC1pReco; PlotsCC1pReco.clear();
		vector<vector<TH1D*> > PlotsTrue; PlotsTrue.clear();
		vector<vector<TH1D*> > QEPlotsTrue; QEPlotsTrue.clear();
		vector<vector<TH1D*> > MECPlotsTrue; MECPlotsTrue.clear();
		vector<vector<TH1D*> > RESPlotsTrue; RESPlotsTrue.clear();
		vector<vector<TH1D*> > DISPlotsTrue; DISPlotsTrue.clear();	
		vector<vector<TH1D*> > COHPlotsTrue; COHPlotsTrue.clear();									

		gStyle->SetPalette(55); const Int_t NCont = 999; gStyle->SetNumberContours(NCont); gStyle->SetTitleSize(0.07,"t");

		vector<TString> NameOfSamples; NameOfSamples.clear();
		vector<int> Colors; Colors.clear();		
		vector<TString> Labels; Labels.clear();
		vector<int> LineStyle; LineStyle.clear();
		vector<TString> weighted; weighted.clear();

		// CV

		NameOfSamples.push_back("Overlay9"); Colors.push_back(OverlayColor); Labels.push_back("G18T "); LineStyle.push_back(G18LineStyle); weighted.push_back("");

		//----------------------------------------//	

		if (PlotGENIE) {

			NameOfSamples.push_back("GENIE_v3_4_0_AR23_20i_00_000");  Colors.push_back(GENIEv2Color); Labels.push_back("AR23 "); weighted.push_back("");
			NameOfSamples.push_back("GENIE_v3_0_6"); Colors.push_back(kGreen+2); Labels.push_back("G18 "); LineStyle.push_back(G18LineStyle); weighted.push_back("");
			NameOfSamples.push_back("GENIE_v3_0_6_G21_11b_00_000"); Colors.push_back(kOrange+6); Labels.push_back("G21 "); LineStyle.push_back(G21LineStyle); weighted.push_back("");

		}

		//----------------------------------------//	

		if (PlotANL_SF) {

			NameOfSamples.push_back("GENIE_v3_0_6"); Colors.push_back(kGreen+2); Labels.push_back("G18 "); LineStyle.push_back(G18LineStyle); weighted.push_back(""); 
			NameOfSamples.push_back("SF_noPB_hN"); Colors.push_back(kOrange+7); Labels.push_back("SF noPB hN "); LineStyle.push_back(G21LineStyle); weighted.push_back(""); 

		}


		//----------------------------------------//		

		if (PlotGen) {

			NameOfSamples.push_back("NuWro_19_02_1"); Colors.push_back(NEUTColor); Labels.push_back("NuWro "); LineStyle.push_back(NuWroLineStyle); weighted.push_back("");
			NameOfSamples.push_back("GiBUU_2023"); Colors.push_back(kMagenta+1); Labels.push_back("GiBUU "); LineStyle.push_back(GiBUULineStyle); weighted.push_back(""); 
			NameOfSamples.push_back("NEUT_5_4_0_1"); Colors.push_back(kYellow-6); Labels.push_back("NEUT "); LineStyle.push_back(NEUTLineStyle); weighted.push_back("");

		}	

		//----------------------------------------//		

		if (plot_gibuu) {

			NameOfSamples.push_back("GiBUU_2023_medium"); Colors.push_back(kOrange+7); Labels.push_back("GiBUU in medium "); LineStyle.push_back(kSolid); weighted.push_back(""); 
			NameOfSamples.push_back("GiBUU_2023"); Colors.push_back(kGreen+1); Labels.push_back("GiBUU "); LineStyle.push_back(GiBUULineStyle); weighted.push_back(""); 

		}	

		//----------------------------------------//		

		if (plot_mec) {

			NameOfSamples.push_back("GENIE_v3_0_6"); Colors.push_back(kMagenta+1); Labels.push_back("Nieves "); LineStyle.push_back(kOrange+7); weighted.push_back(""); 
			NameOfSamples.push_back("GENIE_v3_0_6_Empirical"); Colors.push_back(kGreen+1); Labels.push_back("Empirical "); LineStyle.push_back(GiBUULineStyle); weighted.push_back(""); 
			NameOfSamples.push_back("GENIE_v3_0_6_SuSAv2"); Colors.push_back(kOrange+7); Labels.push_back("SuSAv2 "); LineStyle.push_back(kOrange+7); weighted.push_back(""); 

		}	

		//----------------------------------------//		

		if (plot_nuclear) {

			NameOfSamples.push_back("GENIE_v3_0_6"); Colors.push_back(kMagenta+1); Labels.push_back("LFG "); LineStyle.push_back(kOrange+7); weighted.push_back(""); 
			NameOfSamples.push_back("G18_10a_02_11a_SF_Fortran"); Colors.push_back(kGreen+1); Labels.push_back("SF "); LineStyle.push_back(GiBUULineStyle); weighted.push_back(""); 
			NameOfSamples.push_back("GENIE_v3_0_6_RFG"); Colors.push_back(kOrange+7); Labels.push_back("RFG "); LineStyle.push_back(kOrange+7); weighted.push_back(""); 

		}	


		//----------------------------------------//		

		if (PlotACHILLES) {

		  NameOfSamples.push_back("ACHILLES"); Colors.push_back(NEUTColor); Labels.push_back("ACHILLES "); LineStyle.push_back(NuWroLineStyle); weighted.push_back("");
			
		}	

		if (plot_closure) {

			NameOfSamples.push_back("GENIE_v3_0_6"); Colors.push_back(kGreen+2); Labels.push_back("G18 "); LineStyle.push_back(G18LineStyle);
			NameOfSamples.push_back("NoTuneOverlay9"); Colors.push_back(kOrange+7); Labels.push_back("G18D "); LineStyle.push_back(G21LineStyle);

		}

		//----------------------------------------//

		const int NSamples = NameOfSamples.size();
		vector<TFile*> FileSample; FileSample.clear();

		//----------------------------------------//

		// Open the files and grap the relevant plots

		for (int WhichSample = 0; WhichSample < NSamples; WhichSample ++) {

			vector<TH1D*> CurrentPlotsFullUncReco; CurrentPlotsFullUncReco.clear();
			vector<TH1D*> CurrentPlotsXSecReco; CurrentPlotsXSecReco.clear();
			vector<TH1D*> CurrentPlotsTotalReco; CurrentPlotsTotalReco.clear();
			vector<TH1D*> CurrentPlotsNormOnly; CurrentPlotsNormOnly.clear();			
			vector<TH1D*> CurrentPlotsReco; CurrentPlotsReco.clear();
			vector<TH1D*> CurrentPlotsCC1pReco; CurrentPlotsCC1pReco.clear();
			vector<TH1D*> CurrentPlotsTrue; CurrentPlotsTrue.clear();
			vector<TH1D*> QECurrentPlotsTrue; QECurrentPlotsTrue.clear();
			vector<TH1D*> MECCurrentPlotsTrue; MECCurrentPlotsTrue.clear();	
			vector<TH1D*> RESCurrentPlotsTrue; RESCurrentPlotsTrue.clear();
			vector<TH1D*> DISCurrentPlotsTrue; DISCurrentPlotsTrue.clear();	
			vector<TH1D*> COHCurrentPlotsTrue; COHCurrentPlotsTrue.clear();													

			// CV With Statistical Uncertainties

			if (NameOfSamples[WhichSample] == "Overlay9") { // CV with statistical uncertainties only for now

				TString FileSampleName = PathToFiles+"/WienerSVD_ExtractedXSec_"+NameOfSamples[WhichSample]+"_"+Runs[WhichRun]+"_"+UBCodeVersion+".root"; 
				FileSample.push_back(TFile::Open(FileSampleName,"readonly")); 

				for (int WhichPlot = 0; WhichPlot < N1DPlots; WhichPlot ++) {

					TH1D* histTotalReco = (TH1D*)(FileSample[WhichSample]->Get("StatReco"+PlotNames[WhichPlot]));
					CurrentPlotsTotalReco.push_back(histTotalReco);

					TH1D* histXSecReco = (TH1D*)(FileSample[WhichSample]->Get("XSecReco"+PlotNames[WhichPlot]));
					CurrentPlotsXSecReco.push_back(histXSecReco);

					TH1D* histFullUncReco = (TH1D*)(FileSample[WhichSample]->Get("RecoFullUnc"+PlotNames[WhichPlot]));
					CurrentPlotsFullUncReco.push_back(histFullUncReco);										

					TH1D* histNormOnly = (TH1D*)(FileSample[WhichSample]->Get("NormOnlyReco"+PlotNames[WhichPlot]));
					CurrentPlotsNormOnly.push_back(histNormOnly);					

					TH1D* histReco = (TH1D*)(FileSample[WhichSample]->Get("Reco"+PlotNames[WhichPlot]));
					if (PlotNames[WhichPlot] == "MuonCosThetaSingleBinPlot") { histReco = (TH1D*)(FileSample[WhichSample]->Get("RecoFullUnc"+PlotNames[WhichPlot])); }
					CurrentPlotsReco.push_back(histReco);

					TString TrueString = "True" + PlotNames[WhichPlot];

					TH1D* histTrue = (TH1D*)(FileSample[WhichSample]->Get(TrueString));
					CurrentPlotsTrue.push_back(histTrue);

					TH1D* QEhistTrue = (TH1D*)(FileSample[WhichSample]->Get("QE"+TrueString));
					QECurrentPlotsTrue.push_back(QEhistTrue);
					TH1D* MEChistTrue = (TH1D*)(FileSample[WhichSample]->Get("MEC"+TrueString));
					MECCurrentPlotsTrue.push_back(MEChistTrue);
					TH1D* REShistTrue = (TH1D*)(FileSample[WhichSample]->Get("RES"+TrueString));
					RESCurrentPlotsTrue.push_back(REShistTrue);
					TH1D* DIShistTrue = (TH1D*)(FileSample[WhichSample]->Get("DIS"+TrueString));
					DISCurrentPlotsTrue.push_back(DIShistTrue);
					TH1D* COHhistTrue = (TH1D*)(FileSample[WhichSample]->Get("COH"+TrueString));
					COHCurrentPlotsTrue.push_back(COHhistTrue);																								     
		
				}

			}

			else if (NameOfSamples[WhichSample] == "NoTuneOverlay9") { // CV with statistical uncertainties only for now

				TString FileSampleName = PathToFiles+"/NoTuneOverlay9WienerSVD_ExtractedXSec_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root"; 
				FileSample.push_back(TFile::Open(FileSampleName,"readonly")); 

				for (int WhichPlot = 0; WhichPlot < N1DPlots; WhichPlot ++) {

					TH1D* histTotalReco = (TH1D*)(FileSample[WhichSample]->Get("StatReco"+PlotNames[WhichPlot]));
					CurrentPlotsTotalReco.push_back(histTotalReco);

					TH1D* histXSecReco = (TH1D*)(FileSample[WhichSample]->Get("XSecReco"+PlotNames[WhichPlot]));
					CurrentPlotsXSecReco.push_back(histXSecReco);

					TH1D* histFullUncReco = (TH1D*)(FileSample[WhichSample]->Get("RecoFullUnc"+PlotNames[WhichPlot]));
					CurrentPlotsFullUncReco.push_back(histFullUncReco);										

					TH1D* histNormOnly = (TH1D*)(FileSample[WhichSample]->Get("NormOnlyReco"+PlotNames[WhichPlot]));
					CurrentPlotsNormOnly.push_back(histNormOnly);					

					TH1D* histReco = (TH1D*)(FileSample[WhichSample]->Get("Reco"+PlotNames[WhichPlot]));
					if (PlotNames[WhichPlot] == "MuonCosThetaSingleBinPlot") { histReco = (TH1D*)(FileSample[WhichSample]->Get("RecoFullUnc"+PlotNames[WhichPlot])); }
					CurrentPlotsReco.push_back(histReco);

					TString TrueString = "NoSmearAltTrue";

					TH1D* histTrue = (TH1D*)(FileSample[WhichSample]->Get(TrueString+PlotNames[WhichPlot]));
					rm_bin_width(histTrue);
					CurrentPlotsTrue.push_back(histTrue);

					TH1D* QEhistTrue = (TH1D*)(FileSample[WhichSample]->Get("QE"+TrueString+PlotNames[WhichPlot]));
					QECurrentPlotsTrue.push_back(QEhistTrue);
					TH1D* MEChistTrue = (TH1D*)(FileSample[WhichSample]->Get("MEC"+TrueString+PlotNames[WhichPlot]));
					MECCurrentPlotsTrue.push_back(MEChistTrue);
					TH1D* REShistTrue = (TH1D*)(FileSample[WhichSample]->Get("RES"+TrueString+PlotNames[WhichPlot]));
					RESCurrentPlotsTrue.push_back(REShistTrue);
					TH1D* DIShistTrue = (TH1D*)(FileSample[WhichSample]->Get("DIS"+TrueString+PlotNames[WhichPlot]));
					DISCurrentPlotsTrue.push_back(DIShistTrue);
					TH1D* COHhistTrue = (TH1D*)(FileSample[WhichSample]->Get("COH"+TrueString+PlotNames[WhichPlot]));
					COHCurrentPlotsTrue.push_back(COHhistTrue);																								     
		
				}

			}


			else {
		
			  FileSample.push_back(TFile::Open("OutputFiles/FlatTreeAnalyzerOutput_"+NameOfSamples[WhichSample]+".root")); 

				for (int WhichPlot = 0; WhichPlot < N1DPlots; WhichPlot ++) {

					TH1D* histTotalReco = nullptr;
					CurrentPlotsTotalReco.push_back(histTotalReco);

					TH1D* histXSecReco = nullptr;
					CurrentPlotsXSecReco.push_back(histXSecReco);

					TH1D* histFullUncReco = nullptr;
					CurrentPlotsFullUncReco.push_back(histFullUncReco);										

					TH1D* histNormOnly = nullptr;
					CurrentPlotsNormOnly.push_back(histNormOnly);					

					TH1D* histReco = nullptr;
					CurrentPlotsReco.push_back(histReco);

					TH1D* histCC1pReco = nullptr;
					CurrentPlotsCC1pReco.push_back(histCC1pReco);

					TString TrueString = "True"+PlotNames[WhichPlot];

					if (string(PlotNames[WhichPlot]).find("Serial") != std::string::npos) {

						TString CloneString = TrueString;
						CloneString.ReplaceAll("Serial","");
						TrueString = "Serial" + CloneString;
					}
					
					TH1D* histTrue = (TH1D*)(FileSample[WhichSample]->Get(TrueString));
					CurrentPlotsTrue.push_back(histTrue);

					TH1D* QEhistTrue = (TH1D*)(FileSample[WhichSample]->Get("QE"+TrueString));
					QECurrentPlotsTrue.push_back(QEhistTrue);
					TH1D* MEChistTrue = (TH1D*)(FileSample[WhichSample]->Get("MEC"+TrueString));
					MECCurrentPlotsTrue.push_back(MEChistTrue);
					TH1D* REShistTrue = (TH1D*)(FileSample[WhichSample]->Get("RES"+TrueString));
					RESCurrentPlotsTrue.push_back(REShistTrue);
					TH1D* DIShistTrue = (TH1D*)(FileSample[WhichSample]->Get("DIS"+TrueString));
					DISCurrentPlotsTrue.push_back(DIShistTrue);
					TH1D* COHhistTrue = (TH1D*)(FileSample[WhichSample]->Get("COH"+TrueString));
					COHCurrentPlotsTrue.push_back(COHhistTrue);					
		
				}

			}

			PlotsXSecReco.push_back(CurrentPlotsXSecReco);
			PlotsFullUncReco.push_back(CurrentPlotsFullUncReco);			
			PlotsTotalReco.push_back(CurrentPlotsTotalReco);
			PlotsNormOnly.push_back(CurrentPlotsNormOnly);					
			PlotsReco.push_back(CurrentPlotsReco);		
			PlotsCC1pReco.push_back(CurrentPlotsCC1pReco);
			PlotsTrue.push_back(CurrentPlotsTrue);

			QEPlotsTrue.push_back(QECurrentPlotsTrue);			
			MECPlotsTrue.push_back(MECCurrentPlotsTrue);
			RESPlotsTrue.push_back(RESCurrentPlotsTrue);
			DISPlotsTrue.push_back(DISCurrentPlotsTrue);
			COHPlotsTrue.push_back(COHCurrentPlotsTrue);		

		}

		//----------------------------------------//

		// Loop over the plots

		for (int WhichPlot = 0; WhichPlot < N1DPlots; WhichPlot ++) {	

			//----------------------------------------//

			TH2D* Ac = (TH2D*)FileSample[0]->Get("Ac"+PlotNames[WhichPlot]);

			TString CovString = "UnfCov"+PlotNames[WhichPlot];
			//cout << CovString << endl;
			TH2D* Cov = (TH2D*)FileSample[0]->Get(CovString);	
			Cov->Scale(1./TMath::Power(MultiDimScaleFactor[PlotNames[WhichPlot]],2.)); // includes scaling factor for multi dimensional analysis

			TH2D* NormCov = (TH2D*)FileSample[0]->Get("NormUnfCov"+PlotNames[WhichPlot]);	
			NormCov->Scale(1./TMath::Power(MultiDimScaleFactor[PlotNames[WhichPlot]],2.)); // includes scaling factor for multi dimensional analysis

			TH2D* ShapeCov = (TH2D*)FileSample[0]->Get("ShapeUnfCov"+PlotNames[WhichPlot]);	
			ShapeCov->Scale(1./TMath::Power(MultiDimScaleFactor[PlotNames[WhichPlot]],2.)); // includes scaling factor for multi dimensional analysis								

			//----------------------------------------//

			// The covariance matrix needs to be scaled by the 2D bin width

			TH2D* CovClone = (TH2D*)(Cov->Clone());
			TH2D* NormCovClone = (TH2D*)(NormCov->Clone());	
			TH2D* ShapeCovClone = (TH2D*)(ShapeCov->Clone());					 

			int n = Cov->GetXaxis()->GetNbins();

			for (int ix = 1; ix <= n; ix++) {

				for (int iy = 1; iy <= n; iy++) {

					double WidthX = Cov->GetXaxis()->GetBinWidth(ix);
					double WidthY = Cov->GetYaxis()->GetBinWidth(iy);

					double TwoDWidth = WidthX * WidthY;

					double BinContent = Cov->GetBinContent(ix,iy);
					double NewBinContent = BinContent/TwoDWidth;

					double NormBinContent = NormCov->GetBinContent(ix,iy);
					double NormNewBinContent = NormBinContent/TwoDWidth;

					double ShapeBinContent = ShapeCov->GetBinContent(ix,iy);
					double ShapeNewBinContent = ShapeBinContent/TwoDWidth;													

					// Only for the diagonal elements
					// Add the unfolding uncertainty
					// On top of everything else
					// That is done both for the final xsec result and for the unfolded covariance
					if (ix == iy) { 

						// unfolded covariance matrix
//						double UnfUncBin = UncHist->GetBinContent(ix);
						double UnfUncBin = 0.;

						NewBinContent = NewBinContent + TMath::Power(UnfUncBin,2.) ;
						ShapeNewBinContent = ShapeNewBinContent + TMath::Power(UnfUncBin,2.) ;						 

						// xsec uncertainty
						double CurrentUnc = PlotsReco[0][WhichPlot]->GetBinError(ix);
						double NewError = TMath::Sqrt( TMath::Power(CurrentUnc,2.) + TMath::Power(UnfUncBin,2.) ) ;
						PlotsReco[0][WhichPlot]->SetBinError(ix,NewError);

						double CurrentFullUnc = PlotsFullUncReco[0][WhichPlot]->GetBinError(ix);
						double NewFullError = TMath::Sqrt( TMath::Power(CurrentFullUnc,2.) + TMath::Power(UnfUncBin,2.) ) ;
						PlotsFullUncReco[0][WhichPlot]->SetBinError(ix,NewFullError);						
						
					}

					CovClone->SetBinContent(ix,iy,NewBinContent);
					ShapeCovClone->SetBinContent(ix,iy,ShapeNewBinContent);
					NormCovClone->SetBinContent(ix,iy,NormNewBinContent);										

				}					

			}	

			//CovClone->Draw("coltz text");

			// -----------------------------------------------------------------------------------------------------------------------------			

			TCanvas* PlotCanvas = new TCanvas(PlotNames[WhichPlot]+"_"+Runs[WhichRun],PlotNames[WhichPlot]+"_"+Runs[WhichRun],205,34,1024,768);
			PlotCanvas->cd();

//			TPad *midPad = new TPad("midPad", "",0.005, 0.2, 0.995, 0.995);
			TPad *midPad = new TPad("midPad", "",0.005, 0., 0.995, 0.995);
			midPad->SetBottomMargin(0.16);
			midPad->SetTopMargin(0.12);
			midPad->SetLeftMargin(0.19);
			midPad->SetRightMargin(0.03);			
			midPad->Draw();

			TLegend* leg = new TLegend(0.39,0.68,0.72,0.85);
			TLegend* legMC = new TLegend(0.7,0.68,0.8,0.85);
			
			if (

				PlotNames[WhichPlot] == "SerialECal_ProtonCosThetaProtonMomentumPlot" ||
				PlotNames[WhichPlot] == "ECalPlot" ||
				PlotNames[WhichPlot] == "MuonCosThetaPlot"
				) { 
				
			  leg = new TLegend(0.22,0.68,0.55,0.85);	
			  legMC = new TLegend(0.53,0.68,0.63,0.85);

			}

			leg->SetBorderSize(0);
			leg->SetTextSize(0.05);
			leg->SetTextFont(FontStyle);
			leg->SetNColumns(1);
			leg->SetMargin(0.15);

			legMC->SetBorderSize(0);
			legMC->SetTextSize(0.05);
			legMC->SetTextFont(FontStyle);
			legMC->SetNColumns(1);
			legMC->SetMargin(0.3);				

			// ------------------------------------------------------------------------------------------------------------------

			// BeamOn Total Uncertainty

			PrettyPlot(PlotsReco[0][WhichPlot]); // includes scaling factor for multi dimensional analysis

			double MaxValue = PlotsReco[0][WhichPlot]->GetMaximum();
			int MaxValueBin = LocateBinWithValue(PlotsReco[0][WhichPlot],MaxValue);
			double MaxValueError = PlotsReco[0][WhichPlot]->GetBinError(MaxValueBin);

			double MinValue = PlotsReco[0][WhichPlot]->GetMinimum();
	
			PlotsReco[0][WhichPlot]->GetXaxis()->SetLabelOffset(0.02);													
			PlotsReco[0][WhichPlot]->GetYaxis()->SetLabelOffset(0.02);									
			PlotsReco[0][WhichPlot]->GetYaxis()->SetRangeUser(XSecRange[PlotNames[WhichPlot]].first,XSecRange[PlotNames[WhichPlot]].second);

			PlotsReco[0][WhichPlot]->SetLineColor(BeamOnColor);
			PlotsReco[0][WhichPlot]->SetMarkerColor(BeamOnColor);
			PlotsReco[0][WhichPlot]->SetMarkerSize(1.);
			PlotsReco[0][WhichPlot]->SetMarkerStyle(20);
			PlotsReco[0][WhichPlot]->SetLineWidth(1);	
			PlotsReco[0][WhichPlot]->GetYaxis()->SetTitle(VarLabel[PlotNames[WhichPlot]]);					

			midPad->cd();
			
			//------------------------------//

			// The N-dimensional analysis has been developed based on the bin number, not the actual range

			if (string(PlotNames[WhichPlot]).find("Serial") != std::string::npos) {	

				TString XaxisTitle = PlotsReco[0][WhichPlot]->GetXaxis()->GetTitle();
				XaxisTitle.ReplaceAll("deg","bin #");
				XaxisTitle.ReplaceAll("GeV/c","bin #");
				XaxisTitle.ReplaceAll("(GeV/c)^{2}","bin #");
				XaxisTitle.ReplaceAll("GeV","bin #");				
				PlotsReco[0][WhichPlot]->GetXaxis()->SetTitle(XaxisTitle);

				TString YaxisTitle = VarLabel[PlotNames[WhichPlot]];
				YaxisTitle.ReplaceAll("deg","");
				YaxisTitle.ReplaceAll("GeV/c","");
				YaxisTitle.ReplaceAll("(GeV/c)^{2}","");
				YaxisTitle.ReplaceAll("GeV^{2}/c","");
				YaxisTitle.ReplaceAll("GeV","");
				YaxisTitle.ReplaceAll("/c","");
				//YaxisTitle.ReplaceAll("^{2}","");												
				PlotsReco[0][WhichPlot]->GetYaxis()->SetTitle(YaxisTitle);				

			}			

			//------------------------------//

			PlotsReco[0][WhichPlot]->Draw("e1x0 same"); // Total Unc (Shape + Stat)

			PrettyPlot(PlotsTotalReco[0][WhichPlot]); // includes scaling factor for multi dimensional analysis
			PlotsTotalReco[0][WhichPlot]->SetLineColor(BeamOnColor);
			PlotsTotalReco[0][WhichPlot]->SetMarkerColor(BeamOnColor);
			PlotsTotalReco[0][WhichPlot]->SetLineWidth(1);			
			PlotsTotalReco[0][WhichPlot]->Draw("e1x0 same"); // Stat Only

			PrettyPlot(PlotsXSecReco[0][WhichPlot]); // includes scaling factor for multi dimensional analysis
			PlotsXSecReco[0][WhichPlot]->SetLineColor(BeamOnColor);
			PlotsXSecReco[0][WhichPlot]->SetMarkerColor(BeamOnColor);
			PlotsXSecReco[0][WhichPlot]->SetLineWidth(1);
			PlotsXSecReco[0][WhichPlot]->SetMarkerSize(1.);
			PlotsXSecReco[0][WhichPlot]->SetMarkerStyle(20);
			PlotsXSecReco[0][WhichPlot]->GetYaxis()->SetTitle(VarLabel[PlotNames[WhichPlot]]);									
			//PlotsXSecReco[0][WhichPlot]->Draw("e1x0 same"); // XSec Only			
			
			PrettyPlot(PlotsNormOnly[0][WhichPlot]); // includes scaling factor for multi dimensional analysis			
			PlotsNormOnly[0][WhichPlot]->SetFillColorAlpha(kGray+1, 0.75);	
			PlotsNormOnly[0][WhichPlot]->SetLineColor(kGray+1);
			PlotsNormOnly[0][WhichPlot]->SetMarkerColor(kGray+1);
			if (PlotNames[WhichPlot] != "MuonCosThetaSingleBinPlot") { PlotsNormOnly[0][WhichPlot]->Draw("e2 hist same"); } // Norm unc Only					

			// -----------------------------------------------------------------------------------------------------------------

			// Overlay GENIE v3 + Tune

			PrettyPlot(PlotsTrue[0][WhichPlot]); // includes scaling factor for multi dimensional analysis
			PlotsTrue[0][WhichPlot]->SetLineColor(Colors[0]);
			PlotsTrue[0][WhichPlot]->SetMarkerColor(Colors[0]);
			PlotsTrue[0][WhichPlot]->SetLineStyle(LineStyle[0]);

			// Area normalize MC to Data
			double sf = PlotsTotalReco[0][WhichPlot]->Integral("width") / PlotsTrue[0][WhichPlot]->Integral("width");
			//PlotsTrue[0][WhichPlot]->Scale(sf);

			// -----------------------------------------------------------------------------------------------------------------

			// arrays for NSamples

			double Chi2[NSamples];
			double ShapeChi2[NSamples];						
			int Ndof[NSamples];
			double pval[NSamples];
			double sigma[NSamples];

			// Clones for the NSamples-1 model predictions
			// index 0 corresponds to nominal overlay / CV

			TH1D* Clone[NSamples-1];			

			for (int WhichSample = 1; WhichSample < NSamples; WhichSample++) {

				// Apply the additional smearing matrix Ac
				Clone[WhichSample-1] = Multiply(PlotsTrue[WhichSample][WhichPlot],Ac);
				QEPlotsTrue[WhichSample][WhichPlot] = Multiply(QEPlotsTrue[WhichSample][WhichPlot],Ac);		
				MECPlotsTrue[WhichSample][WhichPlot] = Multiply(MECPlotsTrue[WhichSample][WhichPlot],Ac);	
				RESPlotsTrue[WhichSample][WhichPlot] = Multiply(RESPlotsTrue[WhichSample][WhichPlot],Ac);	
				DISPlotsTrue[WhichSample][WhichPlot] = Multiply(DISPlotsTrue[WhichSample][WhichPlot],Ac);
				COHPlotsTrue[WhichSample][WhichPlot] = Multiply(COHPlotsTrue[WhichSample][WhichPlot],Ac);												
				// Divide by the bin width
				Reweight(Clone[WhichSample-1],1.);
				Reweight(QEPlotsTrue[WhichSample][WhichPlot],1.);
				Reweight(MECPlotsTrue[WhichSample][WhichPlot],1.);
				Reweight(RESPlotsTrue[WhichSample][WhichPlot],1.);
				Reweight(DISPlotsTrue[WhichSample][WhichPlot],1.);
				Reweight(COHPlotsTrue[WhichSample][WhichPlot],1.);																		
				// Area normalize MC to data															
				double mc_sf = PlotsTotalReco[0][WhichPlot]->Integral() / Clone[WhichSample-1]->Integral();
				//Clone[WhichSample-1]->Scale(mc_sf);				
				//QEPlotsTrue[WhichSample][WhichPlot]->Scale(mc_sf);				
				//MECPlotsTrue[WhichSample][WhichPlot]->Scale(mc_sf);				
				//RESPlotsTrue[WhichSample][WhichPlot]->Scale(mc_sf);				
				//DISPlotsTrue[WhichSample][WhichPlot]->Scale(mc_sf);				
				//COHPlotsTrue[WhichSample][WhichPlot]->Scale(mc_sf);				

				//Clone[WhichSample-1] = PlotsTrue[WhichSample][WhichPlot];				
				Clone[WhichSample-1]->SetLineColor(Colors[WhichSample]);
				Clone[WhichSample-1]->SetLineStyle(kSolid);
				Clone[WhichSample-1]->SetMarkerColor(Colors[WhichSample]);

				PrettyPlot(Clone[WhichSample-1]); // includes scaling factor for multi dimensional analysis
				Clone[WhichSample-1]->SetLineWidth(3);		
				Clone[WhichSample-1]->Draw("hist same");		

//				CalcChiSquared(PlotsTrue[WhichSample][WhichPlot],PlotsReco[0][WhichPlot],CovClone,Chi2[WhichSample],Ndof[WhichSample],pval[WhichSample]);
				CalcChiSquared(Clone[WhichSample-1],PlotsReco[0][WhichPlot],CovClone,Chi2[WhichSample],Ndof[WhichSample],pval[WhichSample],sigma[WhichSample]);
				TString Chi2NdofAlt = "(" + to_string_with_precision(Chi2[WhichSample],1) + "/" + TString(std::to_string(Ndof[WhichSample])) +")";
				if (PlotNames[WhichPlot] == "MuonCosThetaSingleBinPlot") { Chi2NdofAlt = ""; } 

				TLegendEntry* lGenie = legMC->AddEntry(Clone[WhichSample-1],Labels[WhichSample] + Chi2NdofAlt,"l");
				lGenie->SetTextColor(Colors[WhichSample]); 										


			}

			//----------------------------------------//

			// Legend & Run / POT

			double tor860_wcut = -99.;
			if (Runs[WhichRun] == "Run1") { tor860_wcut = Fulltor860_wcut_Run1; }
			if (Runs[WhichRun] == "Run2") { tor860_wcut = Fulltor860_wcut_Run2; }
			if (Runs[WhichRun] == "Run3") { tor860_wcut = Fulltor860_wcut_Run3; }
			if (Runs[WhichRun] == "Run5") { tor860_wcut = Fulltor860_wcut_Run5; }
			if (Runs[WhichRun] == "Combined") { tor860_wcut = Fulltor860_wcut_Combined; }
			TString Label = ToString(tor860_wcut).ReplaceAll("e"," #times 10").ReplaceAll("+","^{")+"} POT";

			// ---------------------------------------------------------------------------------------------------------

			// Total Chi2
			CalcChiSquared(PlotsTrue[0][WhichPlot],PlotsReco[0][WhichPlot],CovClone,Chi2[0],Ndof[0],pval[0],sigma[0]);
			TString Chi2NdofNom = "(" + to_string_with_precision(Chi2[0],1) + "/" + TString(std::to_string(Ndof[0])) +")";
			if (PlotNames[WhichPlot] == "MuonCosThetaSingleBinPlot") { Chi2NdofNom = ""; }
			// Shape + Stat Chi2
			CalcChiSquared(PlotsTrue[0][WhichPlot],PlotsReco[0][WhichPlot],ShapeCovClone,ShapeChi2[0],Ndof[0],pval[0],sigma[0]);
			TString ShapeChi2NdofNom = "(" + to_string_with_precision(ShapeChi2[0],1) + "/" + TString(std::to_string(Ndof[0])) +")";	
			if (PlotNames[WhichPlot] == "MuonCosThetaSingleBinPlot") { ShapeChi2NdofNom = ""; }			

			TLegendEntry* lGenie_GenieOverlay = legMC->AddEntry(PlotsTrue[0][WhichPlot],Labels[0]+Chi2NdofNom,"l");
			PlotsTrue[0][WhichPlot]->SetLineWidth(3); 
			PlotsTrue[0][WhichPlot]->Draw("hist same"); 
			lGenie_GenieOverlay->SetTextColor(Colors[0]); 

			// ---------------------------------------------------------------------------------------------------------
			// ---------------------------------------------------------------------------------------------------------

			PlotsTotalReco[0][WhichPlot]->Draw("e1x0 same"); // Stat Only
			PlotsReco[0][WhichPlot]->Draw("e1x0 same"); // BeamOn Stat Total

			leg->AddEntry(PlotsReco[0][WhichPlot],"MicroBooNE Data","");
			leg->AddEntry(PlotsReco[0][WhichPlot],Label,"");
			leg->AddEntry(PlotsReco[0][WhichPlot],"Stat #oplus Shape","ep");			
			leg->AddEntry(PlotsNormOnly[0][WhichPlot],"Norm","f"); 
			leg->Draw();			

			legMC->Draw();			

			TLatex *textSlice = new TLatex();
			textSlice->SetTextFont(FontStyle);
			textSlice->SetTextSize(0.06);
			TString PlotNameDuplicate = PlotNames[WhichPlot];
			TString ReducedPlotName = PlotNameDuplicate.ReplaceAll("Reco","") ;
			textSlice->DrawLatexNDC(0.24, 0.92, LatexLabel[ ReducedPlotName ].ReplaceAll("All events","") );

			TLatex *textPanel = new TLatex();
			textPanel->SetTextFont(FontStyle);
			textPanel->SetTextSize(TextSize);

			//TString Panel = "(a)";
			//if (Extra == "Genie") { Panel = "(b)"; }
			
			TString Panel = "";
			if (Extra == "Genie") { Panel = ""; }


			if (
			    PlotNames[WhichPlot] == "DeltaPnPerpPlot" ||
			    PlotNames[WhichPlot] == "DeltaPnPlot" ||
			    PlotNames[WhichPlot] == "DeltaPhi3DPlot"
			    ) {

			  textPanel->DrawLatexNDC(0.22, 0.8, Panel);

			} else {

                          textPanel->DrawLatexNDC(0.87, 0.8, Panel);

			}

			//----------------------------------------//
/*
			// Plot vertical lines
			// Add latex label with phase space limits

			if (string(PlotNames[WhichPlot]).find("Serial") != std::string::npos) {	

				TString clone_name = PlotNames[WhichPlot];
				clone_name.ReplaceAll("Reco","");
				vector<int> bin_break_points = get_3d_bin_break_points( map_to_3d_bin.at(clone_name) );

				int nbreaks = bin_break_points.size() - 1;
				vector<TLine*> line; line.resize(nbreaks);

				for (int ipoint = 0; ipoint < nbreaks; ipoint ++) {

					line.at(ipoint) = new TLine( bin_break_points.at(ipoint) + 0.5,0., bin_break_points.at(ipoint) + 0.5, PlotsReco[0][WhichPlot]->GetMaximum() );
					midPad->cd();
					line.at(ipoint)->SetLineStyle(kDashed);
					line.at(ipoint)->Draw("same");

				}
	
				//----------------------------------------//

				vector<TLatex*> slice; slice.resize(nbreaks+1);

				for (int ipoint = 0; ipoint < nbreaks + 1; ipoint ++) {

					slice.at(ipoint) = new TLatex();
					slice.at(ipoint)->SetTextFont(FontStyle);
					slice.at(ipoint)->SetTextSize(0.025);
					TString phase_space = MapUncorCor[ clone_name + "_" + TString(std::to_string(ipoint) ) ];
					midPad->cd();
					if (ipoint == 0) { slice.at(ipoint)->DrawLatex( bin_break_points.at(ipoint) / 5. , 0.7 * PlotsReco[0][WhichPlot]->GetMaximum(), LatexLabel[phase_space ]); }
					else { slice.at(ipoint)->DrawLatex( bin_break_points.at(ipoint - 1) + ( bin_break_points.at(ipoint) - bin_break_points.at(ipoint-1) ) / 5. , 0.7 * PlotsReco[0][WhichPlot]->GetMaximum(), LatexLabel[phase_space ]); }

				}

			}

*/			//----------------------------------------//

			// Saving the canvas with the data (total uncertainties) vs overlay & generator predictions

			PlotCanvas->SaveAs("/exp/uboone/data/users/"+UserID+"/FlatTTreePlots/ECal_3D_XSec/XSections_"+Extra+ "_"+PlotNames[WhichPlot]+"_"+Runs[WhichRun]+"_"+UBCodeVersion+".pdf");
			delete PlotCanvas;

			//----------------------------------------//

		} // End of the loop over the plots

		//----------------------------------------//					

	} // End of the loop over the runs	

} // End of the program 
