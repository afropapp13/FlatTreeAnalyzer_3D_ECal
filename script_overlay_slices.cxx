{
	vector<TString> sample;

	//----------------------------------------//

//	sample.push_back("GiBUU_2023"); 
	sample.push_back("GENIE_v3_0_6");			 
//	sample.push_back("NuWro_19_02_1");
//	sample.push_back("NEUT_5_4_0_1");		
//	sample.push_back("GENIE_v3_0_6_G21_11b_00_000");
//	sample.push_back("GENIE_v3_4_0_AR23_20i_00_000");

	//----------------------------------------//

        gROOT->ProcessLine(".L overlay_slices.cxx+");

	for (int i =0;i < (int)(sample.size()); i++) {

		gROOT->ProcessLine("overlay_slices(\""+sample[i]+"\")");

	}
	//gROOT->ProcessLine(".q");
};
