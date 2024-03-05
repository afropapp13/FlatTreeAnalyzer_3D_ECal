#include "TMath.h"
#include <TH1D.h>
#include <TH2D.h>
#include <TMatrixD.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

//----------------------------------------//

int LocateBinWithValue(TH1D* h, double Value) {

  int NBins = h->GetXaxis()->GetNbins();

  for (int i = 1; i <= NBins; i++) {

    double CurrentEntry = h->GetBinContent(i);
    if (CurrentEntry == Value) { return i; } 

  }

  return -99;

}

//----------------------------------------//                                                                                               

TH1D* Multiply(TH1D* True, TH2D* SmearMatrix) {

  TH1D* TrueClone = (TH1D*)(True->Clone());

  int XBins = SmearMatrix->GetXaxis()->GetNbins();
  int YBins = SmearMatrix->GetYaxis()->GetNbins();

  if (XBins != YBins) { std::cout << "Not symmetric matrix" << std::endl; }

  TVectorD signal(XBins);
  TMatrixD response(XBins,XBins);

  H2V(TrueClone, signal);
  H2M(SmearMatrix, response, kTRUE);

  TVectorD RecoSpace = response * signal;
  V2H(RecoSpace, TrueClone);

  return TrueClone;

}

//----------------------------------------//                                                                                                
void PrettyPlot(TH1D* h) {

  h->GetXaxis()->SetLabelFont(FontStyle);
  h->GetXaxis()->SetTitleFont(FontStyle);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetXaxis()->SetTitleOffset(1.05);
  h->GetXaxis()->SetNdivisions(8);


  h->GetYaxis()->SetLabelFont(FontStyle);
  h->GetYaxis()->SetTitleFont(FontStyle);
  h->GetYaxis()->SetNdivisions(8);
  h->GetYaxis()->SetTitleOffset(1.35);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetLabelSize(0.06);
}

//----------------------------------------//

TString to_string_with_precision(double a_value, const int n = 3)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return TString(out.str());
}

//----------------------------------------//

void CalcChiSquared(TH1D* h_model, TH1D* h_data, TH2D* cov, double &chi, int &ndof, double &pval) {

	// Clone them so we can scale them 

	TH1D* h_model_clone = (TH1D*)h_model->Clone();
	TH1D* h_data_clone  = (TH1D*)h_data->Clone();
	TH2D* h_cov_clone   = (TH2D*)cov->Clone();
	int NBins = h_cov_clone->GetNbinsX();

	// Getting covariance matrix in TMatrix form

	TMatrixD cov_m;
	cov_m.Clear();
	cov_m.ResizeTo(NBins,NBins);

	// loop over rows

	for (int i = 0; i < NBins; i++) {			

		// loop over columns

		for (int j = 0; j < NBins; j++) {

			cov_m[i][j] = h_cov_clone->GetBinContent(i+1, j+1);
 
		}
	
	}

	TMatrixD copy_cov_m = cov_m;

	// Inverting the covariance matrix
	TMatrixD inverse_cov_m = cov_m.Invert();

	// Calculating the chi2 = Summation_ij{ (x_i - mu_j)*E_ij^(-1)*(x_j - mu_j)  }
	// x = data, mu = model, E^(-1) = inverted covariance matrix 

	chi = 0.;
	
	for (int i = 0; i < NBins; i++) {

		//double XWidth = h_data_clone->GetBinWidth(i+1);

		for (int j = 0; j < NBins; j++) {

			//double YWidth = h_data_clone->GetBinWidth(i+1);

			double diffi = h_data_clone->GetBinContent(i+1) - h_model_clone->GetBinContent(i+1);
			double diffj = h_data_clone->GetBinContent(j+1) - h_model_clone->GetBinContent(j+1);
			double LocalChi = diffi * inverse_cov_m[i][j] * diffj; 
			chi += LocalChi;
		}

	}

	ndof = h_data_clone->GetNbinsX();
	pval = TMath::Prob(chi, ndof);

	delete h_model_clone;
	delete h_data_clone;
	delete h_cov_clone;

}

// -------------------------------------------------------------------------------------------------------------------------------------

double PeLEE_ReturnBeamOnRunPOT(TString Run) {

	double DataPOT = -99.;

	if (Run == "Run1") { DataPOT = Fulltor860_wcut_Run1 ; }
	if (Run == "Run2") { DataPOT = Fulltor860_wcut_Run2 ; }
	if (Run == "Run3") { DataPOT = Fulltor860_wcut_Run3 ; }
	if (Run == "Run4") { DataPOT = Fulltor860_wcut_Run4 ; }
	if (Run == "Run4a") { DataPOT = Fulltor860_wcut_Run4a ; }	
	if (Run == "Run4aRutgers") { DataPOT = Fulltor860_wcut_Run4aRutgers ; }
	if (Run == "Run5") { DataPOT = Fulltor860_wcut_Run5 ; }
	if (Run == "Combined") { DataPOT = Fulltor860_wcut_Combined ; }

	return DataPOT;

}

// -------------------------------------------------------------------------------------------------------------------------------------

double ReturnBeamOnRunPOT(TString Run) {

	double DataPOT = -99.;

	if (Run == "Run1") { DataPOT = tor860_wcut_Run1 ; }
	if (Run == "Run2") { DataPOT = tor860_wcut_Run2 ; }
	if (Run == "Run3") { DataPOT = tor860_wcut_Run3 ; }
	if (Run == "Run4") { DataPOT = tor860_wcut_Run4 ; }
	if (Run == "Run5") { DataPOT = tor860_wcut_Run5 ; }

	return DataPOT;

}

// -------------------------------------------------------------------------------------------------------------------------------------

void Reweight2D(TH2D* h, double SF) {

	int NBinsX = h->GetXaxis()->GetNbins();
	int NBinsY = h->GetYaxis()->GetNbins();

	for (int i = 0; i < NBinsX; i++) {

		for (int j = 0; j < NBinsX; j++) {

			double CurrentEntry = h->GetBinContent(i+1,j+1);
			double NewEntry = CurrentEntry * SF / ( h->GetXaxis()->GetBinWidth(i+1) * h->GetYaxis()->GetBinWidth(j+1) );

			double CurrentError = h->GetBinError(i+1,j+1);
			double NewError = CurrentError * SF / ( h->GetXaxis()->GetBinWidth(i+1) * h->GetYaxis()->GetBinWidth(j+1) );

			h->SetBinContent(i+1,j+1,NewEntry); 
//			h->SetBinError(i+1,j+1,NewError); 
			h->SetBinError(i+1,j+1,0.000001); 

		}

	}

}

// -------------------------------------------------------------------------------------------------------------------------------------

void Reweight(TH1D* h, double SF) {

	int NBins = h->GetXaxis()->GetNbins();

	for (int i = 0; i < NBins; i++) {

		double CurrentEntry = h->GetBinContent(i+1);
		double NewEntry = CurrentEntry * SF / h->GetBinWidth(i+1);

		double CurrentError = h->GetBinError(i+1);
		double NewError = CurrentError * SF / h->GetBinWidth(i+1);

		h->SetBinContent(i+1,NewEntry); 
//		h->SetBinError(i+1,NewError); 
		h->SetBinError(i+1,0.000001); 

	}

}

// -------------------------------------------------------------------------------------------------------------------------------------

double round(double var,int acc = 0) 
{ 
    double value = (int)(var * TMath::Power(10.,acc) + .5); 
    return (double)value / TMath::Power(10.,acc); 
} 

// -------------------------------------------------------------------------------------------------------------------------------------

double Chi2(TH1D* h1,TH1D* h2, int LowBin = -1, int HighBin = -1) {

	int NBinsX = h1->GetXaxis()->GetNbins();

	double chi2 = 0;
	
	if (LowBin == -1) { LowBin = 0; }
	if (HighBin == -1) { HighBin = NBinsX; }	

	for (int WhichXBin = LowBin; WhichXBin < HighBin; WhichXBin++) {

		double h1Entry = h1->GetBinContent(WhichXBin+1);
		double h1Error = h1->GetBinError(WhichXBin+1);
		double h2Entry = h2->GetBinContent(WhichXBin+1);
		double h2Error = h2->GetBinError(WhichXBin+1);

		double num = TMath::Power(h1Entry - h2Entry,2.);
		double den = TMath::Power(h1Error,2.) + TMath::Power(h2Error,2.);
		if (den != 0) { chi2 += (num / den); }

	}

	return chi2;

}

// -------------------------------------------------------------------------------------------------------------------------------------

TString ToStringInt(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// -------------------------------------------------------------------------------------------------------------------------------------

TString ToStringFloat(float num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// -------------------------------------------------------------------------------------------------------------------------------------

TString ToString(double num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

// -------------------------------------------------------------------------------------------------------------------------------------

double computeMean(std::vector<double> numbers) {

	if(numbers.empty()) return 0;

	double total = 0;
	for (int number = 0; number < (int)(numbers.size()); number ++) {
		total += numbers[number];
	}

	double average = total / numbers.size();
	return average;
}

// -------------------------------------------------------------------------------------------------------------------------------------

double computeStd(double mean, std::vector<double> numbers) {

	float result = 0;
	for (int number = 0; number < (int)(numbers.size()); number ++) {
		result += (numbers[number] - mean)*(numbers[number] - mean);
	}

	return sqrt(result / (numbers.size() - 1));
}
