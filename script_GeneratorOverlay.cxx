{

	gROOT->ProcessLine(".L GeneratorOverlay.cxx+");
	gROOT->ProcessLine("GeneratorOverlay()");
	gROOT->ProcessLine("GeneratorOverlay(\"GENIE\")");
	gROOT->ProcessLine("GeneratorOverlay(\"Closure\")");
	gROOT->ProcessLine("GeneratorOverlay(\"Weights\")");
	gROOT->ProcessLine("GeneratorOverlay(\"DUNE\")");

};
