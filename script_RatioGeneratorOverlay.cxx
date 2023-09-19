{

	gROOT->ProcessLine(".L RatioGeneratorOverlay.cxx+");
	//gROOT->ProcessLine("GeneratorOverlay()");
	//gROOT->ProcessLine("GeneratorOverlay(\"GENIE\")");
	//gROOT->ProcessLine("GeneratorOverlay(\"Closure\")");
	gROOT->ProcessLine("RatioGeneratorOverlay(\"Weights\")");
	//gROOT->ProcessLine("GeneratorOverlay(\"DUNE\")");

};
