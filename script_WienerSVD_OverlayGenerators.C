{

	gROOT->ProcessLine(".L ../myClasses/Util.C");
	gROOT->ProcessLine(".L WienerSVD_OverlayGenerators.cpp");
	//GENIE versions
	gROOT->ProcessLine("WienerSVD_OverlayGenerators()");
	//AltGen
	gROOT->ProcessLine("WienerSVD_OverlayGenerators(false,true)");
	//Closure
	gROOT->ProcessLine("WienerSVD_OverlayGenerators(false,false,false,false,true)");
	//GiBUU
	gROOT->ProcessLine("WienerSVD_OverlayGenerators(false,false,false,false,false,true)");
	//MEC
	gROOT->ProcessLine("WienerSVD_OverlayGenerators(false,false,false,false,false,false,true)");
	//nuclear model
	gROOT->ProcessLine("WienerSVD_OverlayGenerators(false,false,false,false,false,false,false,true)");


}
