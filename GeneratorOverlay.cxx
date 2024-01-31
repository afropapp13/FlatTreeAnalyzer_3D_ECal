#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLatex.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

void GeneratorOverlay(TString Tag = "") {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	int FontStyle = 132;
	double TextSize = 0.06;			

	TString OutFilePath = "OutputFiles/";

	//------------------------------//

	// Event generators

	std::vector<TString> Names; std::vector<TString> Labels; 

	vector<int> Colors;  vector<int> LineStyle;

	if (Tag == "") {

	  Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GENIE_v3_0_6.root"); Labels.push_back("G18"); Colors.push_back(kBlack); LineStyle.push_back(kSolid);
	  Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GENIE_v3_4_0_AR23_20i_00_000.root"); Labels.push_back("AR23"); Colors.push_back(kBlue); LineStyle.push_back(Gv2LineStyle);
	  Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NEUT_5_4_0_1.root"); Labels.push_back("NEUT"); Colors.push_back(kMagenta); LineStyle.push_back(NEUTLineStyle); // kMagenta - 9
	  Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NuWro_19_02_1.root"); Labels.push_back("NuWro"); Colors.push_back(NEUTColor); LineStyle.push_back(NuWroLineStyle);
	  Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GiBUU_2023.root"); Labels.push_back("GiBUU"); Colors.push_back(GiBUUColor); LineStyle.push_back(GiBUULineStyle);

	}


	const int NSamples = Names.size();
	const int NColors = Colors.size();

	// Sanity check
	if (NColors < NSamples) { cout << "Give me some more colors!" << endl; return; }

	std::vector<TFile*> Files; Files.resize(NSamples);

	//------------------------------//

	// Plots to overlay

	std::vector<TString> PlotNames;
	std::vector<TString> YAxisLabel;

	//------------------------------//

	// Post FSI

	// 1D

	PlotNames.push_back("TrueFineBinECalPlot"); YAxisLabel.push_back("#frac{d#sigma}{dE^{Cal}} #left[10^{-38} #frac{cm^{2}}{GeV Ar}#right]");

	// 3D

	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_00To0_20_DeltaAlphaT_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_00To0_20_DeltaAlphaT_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_00To0_20_DeltaAlphaT_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_00To0_20_DeltaAlphaT_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_20To0_40_DeltaAlphaT_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_20To0_40_DeltaAlphaT_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_20To0_40_DeltaAlphaT_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_20To0_40_DeltaAlphaT_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_40To1_00_DeltaAlphaT_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_40To1_00_DeltaAlphaT_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_40To1_00_DeltaAlphaT_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPT_0_40To1_00_DeltaAlphaT_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{T}dp_{T}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");


	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_00To0_20_DeltaAlpha3Dq_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_00To0_20_DeltaAlpha3Dq_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_00To0_20_DeltaAlpha3Dq_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_00To0_20_DeltaAlpha3Dq_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_20To0_40_DeltaAlpha3Dq_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_20To0_40_DeltaAlpha3Dq_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_20To0_40_DeltaAlpha3Dq_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_20To0_40_DeltaAlpha3Dq_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_40To1_00_DeltaAlpha3Dq_0_00To45_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_40To1_00_DeltaAlpha3Dq_45_00To90_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_40To1_00_DeltaAlpha3Dq_90_00To135_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_DeltaPn_0_40To1_00_DeltaAlpha3Dq_135_00To180_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}d#alpha_{3D}dp_{n}} #left[10^{-38} #frac{cm^{2}}{deg (GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_Minus1_00To0_00_MuonMomentum_0_10To0_40Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_00To0_50_MuonMomentum_0_10To0_40Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_50To0_75_MuonMomentum_0_10To0_40Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_75To1_00_MuonMomentum_0_10To0_40Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_Minus1_00To0_00_MuonMomentum_0_40To0_60Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_00To0_50_MuonMomentum_0_40To0_60Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_50To0_75_MuonMomentum_0_40To0_60Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_75To1_00_MuonMomentum_0_40To0_60Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_Minus1_00To0_00_MuonMomentum_0_60To1_20Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_00To0_50_MuonMomentum_0_60To1_20Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_50To0_75_MuonMomentum_0_60To1_20Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_MuonCosTheta_0_75To1_00_MuonMomentum_0_60To1_20Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{#mu}dp_{#mu}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");

	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_Minus1_00To0_00_ProtonMomentum_0_30To0_50Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_00To0_50_ProtonMomentum_0_30To0_50Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_50To0_75_ProtonMomentum_0_30To0_50Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_75To1_00_ProtonMomentum_0_30To0_50Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_Minus1_00To0_00_ProtonMomentum_0_50To0_70Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_00To0_50_ProtonMomentum_0_50To0_70Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_50To0_75_ProtonMomentum_0_50To0_70Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_75To1_00_ProtonMomentum_0_50To0_70Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_Minus1_00To0_00_ProtonMomentum_0_70To1_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_00To0_50_ProtonMomentum_0_70To1_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_50To0_75_ProtonMomentum_0_70To1_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");
	PlotNames.push_back("TrueFineBinECal_ProtonCosTheta_0_75To1_00_ProtonMomentum_0_70To1_00Plot"); YAxisLabel.push_back("#frac{d^{3}#sigma}{dE^{Cal}dcos#theta_{p}dp_{p}} #left[10^{-38} #frac{cm^{2}}{(GeV^{2}/c) Ar}#right]");


	//------------------------------//

	const int NPlots = PlotNames.size();
	const int NLabels = YAxisLabel.size();

	// sanity check
	if ( NPlots != NLabels) { cout << "Inconsistent number of plots and labels! Aborting !" << endl; return; }

	//------------------------------//	

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		Files[iSample] = new TFile(Names[iSample],"readonly");

	} // End of the loop over the samples

	//------------------------------//

	// Loop over the plots to be compared

	for (int iPlot = 0; iPlot < NPlots; iPlot++) {

		TString CanvasName = "ThreeDXSec_GeneratorOverlay_" + PlotNames[iPlot];
		TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
		PlotCanvas->cd();
		PlotCanvas->SetTopMargin(0.15);
		PlotCanvas->SetLeftMargin(0.22);
		PlotCanvas->SetRightMargin(0.05);
		PlotCanvas->SetBottomMargin(0.16);		
		PlotCanvas->Draw();	

		TLegend* leg = new TLegend(0.17,0.87,0.99,0.99);
		leg->SetBorderSize(0);
		leg->SetNColumns(6);
		leg->SetTextSize(TextSize);	
		leg->SetTextFont(FontStyle);						
		leg->SetMargin(0.3);						

		// Loop over the samples to open the files and to get the corresponding plot

		std::vector<TH1D*> Histos; Histos.resize(NSamples);

		for (int iSample = 0; iSample < NSamples; iSample++) {	

		        Histos[iSample] = (TH1D*)(Files[iSample]->Get(PlotNames[iPlot]));

			Histos[iSample]->SetLineWidth(3);
			Histos[iSample]->SetLineColor( Colors.at(iSample) );	
			Histos[iSample]->SetLineStyle( LineStyle.at(iSample) );	

			Histos[iSample]->GetXaxis()->SetTitleFont(FontStyle);
			Histos[iSample]->GetXaxis()->SetLabelFont(FontStyle);
			Histos[iSample]->GetXaxis()->SetNdivisions(8);
			Histos[iSample]->GetXaxis()->SetLabelSize(TextSize);
			Histos[iSample]->GetXaxis()->SetTitleSize(TextSize);	
			Histos[iSample]->GetXaxis()->SetTitleOffset(1.1);					
			Histos[iSample]->GetXaxis()->CenterTitle();						
			
			Histos[iSample]->GetYaxis()->SetTitleFont(FontStyle);
			Histos[iSample]->GetYaxis()->SetLabelFont(FontStyle);
			Histos[iSample]->GetYaxis()->SetNdivisions(8);
			Histos[iSample]->GetYaxis()->SetLabelSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitle(YAxisLabel.at(iPlot));
			Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitleOffset(1.7);
			//Histos[iSample]->GetYaxis()->SetTickSize(0);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());
			double MaxScale = 1.07;
			Histos[iSample]->GetYaxis()->SetRangeUser(0.0001,MaxScale*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.0001,MaxScale*imax);			

			PlotCanvas->cd();
			Histos[iSample]->Draw("hist same");
			//Histos[0]->Draw("hist same");	

			TLegendEntry* legColor = leg->AddEntry(Histos[iSample],Labels[iSample],"l");
			legColor->SetTextColor( Colors.at(iSample) ); 

			TLatex *textSlice = new TLatex();
			textSlice->SetTextFont(FontStyle);
			textSlice->SetTextSize(TextSize);
			TString PlotNameDuplicate = PlotNames[iPlot];
			TString ReducedPlotName = PlotNameDuplicate.ReplaceAll("TrueFineBin","") ;

			textSlice->DrawLatexNDC(0.26, 0.8, LatexLabel[ReducedPlotName].ReplaceAll("All events",""));

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();

		PlotCanvas->SaveAs("/uboone/data/users/apapadop/ThreeDXSec_FlatTTreePlots/"+Tag+CanvasName+".pdf");
		delete PlotCanvas;

	} // End of the loop over the plots

	//------------------------------//

} // End of the program
