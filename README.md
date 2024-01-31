# Loop over the input files
root -b script_LoopGenerators.C

# To overlay the outputs of the loop w/o any Ac multiplication
# Generators variations
root -b script_GeneratorOverlay.cxx

# Interaction breakdown
root -b GeneratorInteBreakDown.cxx

# XSecs with Ac multiplication
root -b script_WienerSVD_OverlayGenerators.C
root -b script_ThreeDimWienerSVD_OverlayGenerators.C

# merge the 3D xsecs
hadd -f OutputFiles/All_XSecs_3D_ECal.root OutputFiles/All_XSecs_3D_ECal_*

