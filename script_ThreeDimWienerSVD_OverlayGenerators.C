{

	gROOT->ProcessLine(".L ../myClasses/Util.C");
	gROOT->ProcessLine(".L ../myClasses/Tools.cxx");
	gROOT->ProcessLine(".L ThreeDimWienerSVD_OverlayGenerators.cpp");

	std::vector<TString> PlotNames; std::vector<int> NumberFirstDiscrSlices;  std::vector<int> NumberSecondDiscrSlices; 

	PlotNames.push_back("ECal_DeltaPTDeltaAlphaTPlot"); NumberFirstDiscrSlices.push_back(3); NumberSecondDiscrSlices.push_back(4);
	PlotNames.push_back("ECal_DeltaPtxDeltaPtyPlot"); NumberFirstDiscrSlices.push_back(3); NumberSecondDiscrSlices.push_back(3);
	PlotNames.push_back("ECal_MuonCosThetaMuonMomentumPlot"); NumberFirstDiscrSlices.push_back(4); NumberSecondDiscrSlices.push_back(3);
	PlotNames.push_back("ECal_ProtonCosThetaProtonMomentumPlot"); NumberFirstDiscrSlices.push_back(4); NumberSecondDiscrSlices.push_back(3);

	for (int i = 0; i < (int)(PlotNames.size()); i++) {


	  for (int j = 0; j < NumberFirstDiscrSlices.at(i); j++) {

	    //GENIE versions
	    gROOT->ProcessLine("ThreeDimWienerSVD_OverlayGenerators(\""+PlotNames[i]+"\","+TString(std::to_string(j))+","+TString( std::to_string(j * NumberSecondDiscrSlices[i]) ) + ")");
	    //AltGen
	    gROOT->ProcessLine("ThreeDimWienerSVD_OverlayGenerators(\""+PlotNames[i]+"\","+TString(std::to_string(j))+","+TString( std::to_string(j * NumberSecondDiscrSlices[i]) ) +",false,true)");

	  }

	}

}
