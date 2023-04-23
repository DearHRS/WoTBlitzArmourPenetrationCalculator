# BlitzPenetration-Test

Currently updating over to c++
-new version will include gui but no plans to add models

log:15.04.2023 0115
-added module to handle input and other functions
-added module with functions related to blitz penetration physics
-modules barely interact with each other at the moment

log:15.04.2023 1516
-completed functions related to calculation of kinetic rounds (ap/apcr)
-intregated those functions and programme finally does calculations related to 100% chance of penetration

log:17.04.2023 1425
-minor fixes to bugs and typos

log:17.04.2023 1752
-completed functions related to calculation of chemical rounds (heat/he)
-intregated those functions

log:23.04.2023 1944
-reworked structure of programme (not all modules in source code are intregated yet, Blitz namespace and rework of many many functions)
-std::wstrings are now used instead of std::string
-added struct to store shell data (Blitz::ShellData)
-Blitz::Funx::AgainstKineticRounds() & Blitz::Funx::AgainstChemicalRounds() no longer output on console but store penetration data to vector of string vector 
-added functions to get penetration rng for what chance of penetration is desired (in Blitz::Funx::GetRng())
-working on tabular display (incomplete at the moment, Blitz::Funx::DisplayData())
-excel sheet and paint.net now include mafs used to discover Blitz::Funx::GetRng()
