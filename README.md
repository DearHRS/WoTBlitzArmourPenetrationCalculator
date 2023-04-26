# ArmourPenetrationCalculator
Calculator written in C++, displays required level of penetration for predetermined chance for different shell types and calibers
Current features:

-Fully realized penetration for primary armour against AP rounds

-Fully realized penetration for primary armour against APCR rounds

-Partially realized penetration for primary armour against HEAT / HE / HESH / HEP  rounds (can not be fully realized without tank models)

-mafs with spaced armour

-mafs with external modules (for 3 calibre bypass)

-tabular view between enhanced armour off and on


Missing features:

-understandable gui



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



log:24.04.2023 0119

-fully integrated newly reworked structure

-reworked Blitz::Funx::GetRng() to return result between 0.95 to 1.05 (+-5% shell penetration rng)

-completed Blitz::Funx::DisplayData()

-added OtherFunx::MakeNumberLookGood() (called inside of Other::Funx::RemoveUnnecessaryZerosFromWstringVector()), used to fix string length to make data look more even



log:25.04.2023 0023

-reworked Blitz::Funx::AgainstKineticRounds() (now supports all maths related to spaced armour and external modules)

-calculator now asks user if they want to launch armourInspector or BlitzHangar before it starts or not

-fixed few bugs that could crash calculator when entered incorrect input



log:26.04.2023 0837

-made input messages slightly less wordy

-made output data less wordy while also making them understandable what causes this penetration

-currently working on displaying data more tabularly, same shell type's enhanced armour off and on should be displayed side by side 



log: 26.04.2023 1413

-fixed bug where 3calibre overmatch bypass being higher than double overmatch caused incorrect data display

-fixed bug where 3calibre overmatch bypass being higher than triple overmatch caused incorrect data display

-added new function OtherFunx::GetWstringVectorLength(); gets size total size from a string vector

-finally finished tabular view between enhanced armour off and on
