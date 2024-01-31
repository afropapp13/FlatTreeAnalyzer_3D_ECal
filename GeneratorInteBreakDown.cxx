#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TPad.h>
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

void GeneratorInteBreakDown() {

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

	std::vector<int> Colors{kBlack,kBlue,kRed+1,kOrange+7,kGreen+1, kMagenta+1};
	std::vector<TString> Process{"","QE","MEC","RES","DIS"};

	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GENIE_v3_0_6.root"); Labels.push_back("G18");
	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GiBUU_2023.root"); Labels.push_back("GiBUU");
	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_GENIE_v3_4_0_AR23_20i_00_000.root"); Labels.push_back("AR23");
	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NEUT_5_4_0_1.root"); Labels.push_back("NEUT");
	Names.push_back(OutFilePath+"FlatTreeAnalyzerOutput_NuWro_19_02_1.root"); Labels.push_back("NuWro");

	const int NSamples = Names.size();
	const int NColors = Colors.size();
	const int NProcesses = Process.size();

	// Sanity check
	if (NColors < NProcesses) { cout << "Give me some more colors for all the processes!" << endl; return; }

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

		for (int iSample = 0; iSample < NSamples; iSample++) {	

		  TString LabelCopy = Labels[iSample];
		  TString CanvasName = "ThreeDXSec_"+LabelCopy.ReplaceAll(" ","_")+"_InteBreakDown_" + PlotNames[iPlot];
		  TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
		  PlotCanvas->cd();
		  PlotCanvas->SetTopMargin(0.13);
		  PlotCanvas->SetLeftMargin(0.21);
		  PlotCanvas->SetRightMargin(0.05);
		  PlotCanvas->SetBottomMargin(0.16);		
		  PlotCanvas->Draw();	

		  TLegend* leg = new TLegend(0.2,0.88,0.8,0.99);
		  leg->SetBorderSize(0);
		  leg->SetNColumns(5);
		  leg->SetTextSize(TextSize);	
		  leg->SetTextFont(FontStyle);						
		  leg->SetMargin(0.2);				
		  leg->SetFillColor(0);				

		  // Loop over the interaction processes

		  std::vector<TH1D*> Histos; Histos.resize(NProcesses);

		  for (int iprocess = 0; iprocess < NProcesses; iprocess++) {	

		        Histos[iprocess] = (TH1D*)(Files[iSample]->Get(Process[iprocess]+PlotNames[iPlot]));

			Histos[iprocess]->SetLineWidth(4);
			Histos[iprocess]->SetLineColor( Colors.at(iprocess) );	

			Histos[iprocess]->GetXaxis()->SetTitleFont(FontStyle);
			Histos[iprocess]->GetXaxis()->SetLabelFont(FontStyle);
			Histos[iprocess]->GetXaxis()->SetNdivisions(8);
			Histos[iprocess]->GetXaxis()->SetLabelSize(TextSize);
			Histos[iprocess]->GetXaxis()->SetTitleSize(TextSize);	
			Histos[iprocess]->GetXaxis()->SetTitleOffset(1.1);					
			Histos[iprocess]->GetXaxis()->CenterTitle();						

			Histos[iprocess]->GetYaxis()->SetTitleFont(FontStyle);
			Histos[iprocess]->GetYaxis()->SetLabelFont(FontStyle);
			Histos[iprocess]->GetYaxis()->SetNdivisions(6);
			Histos[iprocess]->GetYaxis()->SetLabelSize(TextSize);
			Histos[iprocess]->GetYaxis()->SetTitle(YAxisLabel.at(iPlot));
			Histos[iprocess]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iprocess]->GetYaxis()->SetTitleOffset(1.6);
			//Histos[iprocess]->GetYaxis()->SetTickSize(0);
			Histos[iprocess]->GetYaxis()->CenterTitle();	
			Histos[iprocess]->GetYaxis()->SetRangeUser(0.0001,1.05*Histos[0]->GetMaximum());
			Histos[0]->GetYaxis()->SetRangeUser(0.0001,1.05*Histos[0]->GetMaximum());

			Histos[iprocess]->Draw("hist same");
			Histos[0]->Draw("hist same");	

			TString LegLabel = Process[iprocess];
			if (LegLabel == "") { LegLabel = "Total"; }
			TLegendEntry* legColor = leg->AddEntry(Histos[iprocess],LegLabel,"l");
			legColor->SetTextColor( Colors.at(iprocess) ); 

		  } // End of the loop over the processes



		  PlotCanvas->cd();
		  leg->Draw();

		  gPad->RedrawAxis();

                  TLatex *textSlice = new TLatex();
                  textSlice->SetTextFont(FontStyle);
                  textSlice->SetTextSize(TextSize);
                  TString PlotNameDuplicate = PlotNames[iPlot];
                  TString ReducedPlotName = PlotNameDuplicate.ReplaceAll("TrueFineBin","") ;
                  textSlice->DrawLatexNDC(0.26, 0.8, LatexLabel[ReducedPlotName].ReplaceAll("All events",""));

		  TLegend* leggen = new TLegend(0.8,0.89,0.95,0.98);
		  leggen->SetNColumns(5);
		  leggen->SetTextSize(TextSize);	
		  leggen->SetTextFont(FontStyle);						
		  leggen->SetMargin(0.2);				
		  leggen->SetFillColor(0);				
		  //leggen->AddEntry(Histos[0],Labels[iSample],"");
		  TLegendEntry *le1 = leggen->AddEntry(Histos[0],Labels[iSample],"");
		  le1->SetTextAlign(22);
		  leggen->Draw();

		  PlotCanvas->SaveAs("/uboone/data/users/apapadop/ThreeDXSec_FlatTTreePlots/"+CanvasName+".pdf");
		  delete PlotCanvas;

		} // End of the loop over the samples grabing the plots	

	} // End of the loop over the plots

	//------------------------------//

} // End of the program
