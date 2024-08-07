{
	vector<TString> WhichSample; vector<TString> WhichName;

	//----------------------------------------//

	WhichSample.push_back("/pnfs/uboone/persistent/users/mastbaum/tuning2022/mc/bnb_ub/flat/bnb.ub.num.genie_v3_00_06.flat.root"); WhichName.push_back("GENIE_v3_0_6");			 
	WhichSample.push_back("/pnfs/uboone/persistent/users/mastbaum/tuning2022/mc/bnb_ub/flat/bnb.ub.num.nuwro_19_02_1.flat.root"); WhichName.push_back("NuWro_19_02_1");
	WhichSample.push_back("/pnfs/uboone/persistent/users/mastbaum/tuning2022/mc/bnb_ub/flat/bnb.ub.num.neut_5_4_0_1.flat.root"); WhichName.push_back("NEUT_5_4_0_1");		
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/gntp.0.gprep_G21_11b_00_000.flat.root"); WhichName.push_back("GENIE_v3_0_6_G21_11b_00_000");
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/gntp.0.ghep_v3_4_0_G18_10a_02_11a.prep.flat.root"); WhichName.push_back("GENIE_v3_4_0_G18_10a_02_11a");
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_4_0_AR23_20i_00_000_CC/14_1000180400_CC_v3_4_0_AR23_20i_00_000.flat.root"); WhichName.push_back("GENIE_v3_4_0_AR23_20i_00_000");
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_4_2_G18_10a_02_11a_SuSAv2_CC/14_1000180400_CC_v3_4_2_G18_10a_02_11a.flat.root"); WhichName.push_back("GENIE_v3_0_6_SuSAv2");		
 	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_4_2_G18_10a_02_11a_EmpiricalMEC_CC/14_1000180400_CC_v3_4_2_G18_10a_02_11a.flat.root"); WhichName.push_back("GENIE_v3_0_6_Empirical");		
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/v3_4_0_ANL_SF/BNB_SF_Ar40.flat.root"); WhichName.push_back("G18_10a_02_11a_SF_Fortran");
	WhichSample.push_back("/pnfs/uboone/persistent/users/apapadop/GENIETweakedSamples/gntp.0.gprep_RFG.flat.root"); WhichName.push_back("GENIE_v3_0_6_RFG");

	// GiBUU
        WhichSample.push_back("/pnfs/uboone/persistent/users/bbogart/GiBUU_samples/GiBUU/GiBUU.flat.root"); WhichName.push_back("GiBUU_2023");
        WhichSample.push_back("/pnfs/uboone/persistent/users/bbogart/GiBUU_samples/GiBUU_flagInMedium/GiBUU_flagInMedium.flat.root");WhichName.push_back("GiBUU_2023_medium"); // 73 runs

	//----------------------------------------//

        gROOT->ProcessLine(".L ../myClasses/Tools.cxx+");
        gROOT->ProcessLine(".L ../myClasses/STV_Tools.cxx+");
	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	for (int i =0;i < (int)(WhichSample.size()); i++) {

		gROOT->ProcessLine("FlatTreeAnalyzer(\""+WhichSample[i]+"\",\""+WhichName[i]+"\").Loop()");

	}
	//gROOT->ProcessLine(".q");
};
