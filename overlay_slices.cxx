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
#include <map>

#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

void overlay_slices(TString sample = "") {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	int FontStyle = 132;
	double TextSize = 0.06;			

	vector<int> colors = {kAzure-4, kOrange+7, kRed+1, kGreen +2} ; 

	//------------------------------//

	// File to grab plots from
	
	TString file_name = "OutputFiles/FlatTreeAnalyzerOutput_" + sample + ".root";
	TFile* file = new TFile(file_name,"readonly");

	//------------------------------//

	// map to match the 3D slices with the exact plots
	
	std::map<TString, vector<TString> > combos = {
		{ "ECal_DeltaPTDeltaAlphaT", {"ECal_DeltaPT_0_00To0_30_DeltaAlphaT_0_00To90_00Plot",
					      "ECal_DeltaPT_0_00To0_30_DeltaAlphaT_90_00To180_00Plot",
					      "ECal_DeltaPT_0_30To1_00_DeltaAlphaT_0_00To90_00Plot",
					      "ECal_DeltaPT_0_30To1_00_DeltaAlphaT_90_00To180_00Plot"} 
					     },
		{ "ECal_DeltaPnDeltaAlpha3Dq", {"ECal_DeltaPn_0_00To0_30_DeltaAlpha3Dq_0_00To90_00Plot",
						"ECal_DeltaPn_0_00To0_30_DeltaAlpha3Dq_90_00To180_00Plot",
						"ECal_DeltaPn_0_30To1_00_DeltaAlpha3Dq_0_00To90_00Plot",
						"ECal_DeltaPn_0_30To1_00_DeltaAlpha3Dq_90_00To180_00Plot"}
					        },
		{ "ECal_MuonCosThetaMuonMomentum", {"ECal_MuonCosTheta_Minus1_00To0_60_MuonMomentum_0_10To0_50Plot",
						    "ECal_MuonCosTheta_0_60To1_00_MuonMomentum_0_10To0_50Plot",
						    "ECal_MuonCosTheta_Minus1_00To0_60_MuonMomentum_0_50To1_20Plot",
						    "ECal_MuonCosTheta_0_60To1_00_MuonMomentum_0_50To1_20Plot"}
						   },
		{ "ECal_ProtonCosThetaProtonMomentum", {"ECal_ProtonCosTheta_Minus1_00To0_60_ProtonMomentum_0_30To0_60Plot",
							"ECal_ProtonCosTheta_0_60To1_00_ProtonMomentum_0_30To0_60Plot",
							"ECal_ProtonCosTheta_Minus1_00To0_60_ProtonMomentum_0_60To1_00Plot",
							"ECal_ProtonCosTheta_0_60To1_00_ProtonMomentum_0_60To1_00Plot"}
						       },
	};

	int ncombos = combos.size();

	//------------------------------//

	// Loop over the combos

//	for (int icombo = 0; icombo < ncombos; icombo++) {
	for (auto& combo:combos) {


		TString canvas_name = "canvas_overlay_slices_" + combo.first;
		TCanvas* canvas = new TCanvas(canvas_name,canvas_name,205,34,1024,768);
		canvas->cd();
		canvas->SetTopMargin(0.14);
		canvas->SetLeftMargin(0.15);
		canvas->SetBottomMargin(0.14);		
		canvas->Draw();	

		TLegend* leg = new TLegend(0.15,0.87,0.89,0.99);
		leg->SetBorderSize(0);
		leg->SetNColumns(2);
		leg->SetTextSize(0.03);	
		leg->SetTextFont(FontStyle);						
		leg->SetMargin(0.1);						

		// Loop over the slices

		int nslices = combo.second.size();
		std::vector<TH1D*> histos; histos.resize( nslices );

		for (int islice = 0; islice < nslices; islice++) {	
		        
			histos.at(islice) = (TH1D*)(file->Get( "TrueFineBin"  + combo.second.at(islice) ) );
	
			histos.at(islice)->SetLineWidth(3);
			histos.at(islice)->SetLineColor( colors.at(islice) );	

			histos.at(islice)->GetXaxis()->SetTitleFont(FontStyle);
			histos.at(islice)->GetXaxis()->SetLabelFont(FontStyle);
			histos.at(islice)->GetXaxis()->SetNdivisions(8);
			histos.at(islice)->GetXaxis()->SetLabelSize(TextSize);
			histos.at(islice)->GetXaxis()->SetTitleSize(TextSize);	
			histos.at(islice)->GetXaxis()->SetTitleOffset(1.1);					
			histos.at(islice)->GetXaxis()->CenterTitle();						
			
			histos.at(islice)->GetYaxis()->SetTitleFont(FontStyle);
			histos.at(islice)->GetYaxis()->SetLabelFont(FontStyle);
			histos.at(islice)->GetYaxis()->SetNdivisions(6);
			histos.at(islice)->GetYaxis()->SetLabelSize(TextSize);
			histos.at(islice)->GetYaxis()->SetLabelOffset(0.02);
			histos.at(islice)->GetYaxis()->SetTitle("PDF");
			histos.at(islice)->GetYaxis()->SetTitleSize(TextSize);
			histos.at(islice)->GetYaxis()->SetTitleOffset(1.2);
			histos.at(islice)->GetYaxis()->CenterTitle();	

			// convert to pdf
			histos.at(islice)->Scale(1./histos.at(islice)->Integral());

			double imax = TMath::Max( histos.at(islice)->GetMaximum(), histos.at(0)->GetMaximum());
			histos.at(0)->GetYaxis()->SetRangeUser(0.,1.1* imax);

			canvas->cd();
			histos.at(islice)->Draw("hist same");
			histos.at(0)->Draw("hist same");

			TLegendEntry* legColor = leg->AddEntry(histos.at(islice), LatexLabel.at( combo.second.at(islice) ),"l");
			legColor->SetTextColor( colors.at(islice) ); 

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		canvas->cd();
		leg->Draw();

		canvas->SaveAs("/exp/uboone/data/users/apapadop/ThreeDXSec_FlatTTreePlots/"+canvas_name+".pdf");
		//delete canvas;

	} // End of the loop over the combos

	//------------------------------//

} // End of the program
