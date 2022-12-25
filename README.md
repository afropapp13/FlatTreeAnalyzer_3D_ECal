# To loop over the input files
root -b script_LoopGenerators.cxx

# To overlay the outputs of the loop w/o any Ac multiplication
# Generators and GENIE variations
root -b script_GeneratorOverlay.cxx

# Interaction breakdown
root -b GeneratorInteBreakDown.cxx

# FSI Study
root -b GeneratorFSIStudy.cxx

# XSecs with Ac multiplication
root -b script_WienerSVD_OverlayGenerators.C
root -b script_TwoDimWienerSVD_OverlayGenerators.C