#include "Blitz.h"


Blitz::ShellData::ShellData(std::wstring shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle, double externalModuleThickness, double spaceArmourNominal, double spacedArmourAngle) {
    this->shellDisplayName = shellDisplayName;

    Funx::AgainstKineticRounds(enhancedArmourOff, normalizationAngle, armourNominal, armourAngle, externalModuleThickness, spaceArmourNominal, spacedArmourAngle);
    Funx::AgainstKineticRounds(enhancedArmourOn, normalizationAngle, armourNominal * 1.04, armourAngle, externalModuleThickness, spaceArmourNominal * 1.04, spacedArmourAngle);
}


Blitz::ShellData::ShellData(std::wstring shellDisplayName, double armourNominal, double armourAngle) {
    this->shellDisplayName = shellDisplayName;

    Funx::AgainstChemicalRounds(enhancedArmourOff, armourNominal, armourAngle);
    Funx::AgainstChemicalRounds(enhancedArmourOn, armourNominal * 1.04, armourAngle);
}


void Blitz::Funx::AgainstKineticRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double shellNormalizationAngle, double primaryArmourNominal, double primaryArmourAngle, double externalModuleThickness, double spacedArmourNominal, double spacedArmourAngle) {
    double primaryArmourOvermatchCalibreTriple = primaryArmourNominal * 3;      //lowest calibre right under triple overmatch for given nominal armour
    double primaryArmourOvermatchCalibreDouble = primaryArmourNominal * 2;      //lowest calibre right under double overmatch for given nominal armour

    std::vector<double> penetrationChance = { 100, 80, 60, 40, 20 };            //penetration chances for plugging into PenetrationValueGenerator and PenetrationValueGeneratorRange functions

    //penetration case 1
    if (primaryArmourAngle < 70) {
        //calibre case with no double overmatch
        //done separately to not include newline char
        penetrationStorage.push_back(std::vector<std::wstring>{L""});
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"For gun calibre: (",
            L"0",
            L", ",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L"] mm applied normalizaiton ",
            std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble, primaryArmourNominal) * 100) / 100),
            L"°"
            }
        );


        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance,
            externalModuleThickness +
            Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble, primaryArmourNominal)) +
            Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0)
        );


        //calibre case with double overmatch
        //done separately to not include newline char
        penetrationStorage.push_back(std::vector<std::wstring>{L""});
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"For gun calibre: (",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L", ",
            std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
            L"] mm applied normalizaion [",
            std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble + 0.01, primaryArmourNominal) * 100) / 100),
            L", ",
            std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple, primaryArmourNominal) * 100) / 100),
            L"] °"
            }
        );
        penetrationStorage.push_back(std::vector<std::wstring>{L"These gun calibres trigger double overmatch!"});


        Blitz::Funx::PenetrationValueRangeGenerator(penetrationStorage, penetrationChance, std::vector<double>{
            externalModuleThickness +
            Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble + 0.01, primaryArmourNominal)) +
            Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0),

            externalModuleThickness +
            Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple, primaryArmourNominal)) +
            Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0)
            }
        );
    }

    //penetration case 2
    else if (externalModuleThickness > 0 || spacedArmourNominal > 0) {
        double tripleOverMatchBypass;                       //lowest calibre right under triple overmatch bypass for given spaced armour or external module        
        std::wstring triggerStatement;                      //custom statement for external module or spaced armour trigger

        if (externalModuleThickness == 0) {
            tripleOverMatchBypass = spacedArmourNominal * 3;
            triggerStatement = L"Triple overmatch bypass triggered on spaced armour!";
        }
        else if (spacedArmourNominal == 0) {
            tripleOverMatchBypass = externalModuleThickness * 3;
            triggerStatement = L"Triple overmatch bypass triggered on external module!";
        }
        else if (spacedArmourNominal < externalModuleThickness) {
            tripleOverMatchBypass = spacedArmourNominal * 3;
            triggerStatement = L"Triple overmatch bypass triggered on spaced armour!";
        }
        else {
            tripleOverMatchBypass = externalModuleThickness * 3;
            triggerStatement = L"Triple overmatch bypass triggered on external module!";
        }

        /*
        checking if tripleOvermatchBypass is greater than primaryArmourOvermatchCalibreTriple
        super niche case where TripleOverMatch can be lower than required calibre to triple overmatch bypass
        */
        if (primaryArmourOvermatchCalibreTriple >= tripleOverMatchBypass) {
            penetrationStorage.push_back(std::vector<std::wstring>{L""});
            penetrationStorage.push_back(std::vector<std::wstring>{triggerStatement});
            penetrationStorage.push_back(std::vector<std::wstring>{L""});

        
            /*
            checking if tripleOvermatchBypass is greater than primaryArmourOvermatchCalibreDouble
            niche case where doubleOverMatch can be lower than required calibre to triple overmatch bypass
            */
            if (primaryArmourOvermatchCalibreDouble <= tripleOverMatchBypass) {
                primaryArmourOvermatchCalibreDouble = tripleOverMatchBypass;
            }
            else {
                //calibre case with no double overmatch

                penetrationStorage.push_back(std::vector<std::wstring>{L""});
                penetrationStorage.push_back(std::vector<std::wstring>{
                    L"For gun calibre: (",
                    std::to_wstring(round(tripleOverMatchBypass * 100) / 100),
                    L", ",
                    std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
                    L"] mm applied normalizaion ",
                    std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, tripleOverMatchBypass + 0.01, primaryArmourNominal) * 100) / 100),
                    L"°"
                    }
                );


                Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance,
                    externalModuleThickness +
                    Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
                    Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, tripleOverMatchBypass + 0.01, primaryArmourNominal))
                );
            }
        

            //calibre case with double overmatch
            //done separately to not include newline char
            penetrationStorage.push_back(std::vector<std::wstring>{L""});
            penetrationStorage.push_back(std::vector<std::wstring>{
                L"For gun calibre: (",
                std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
                L", ",
                std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
                L"] mm applied normalization [",
                std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble + 0.01, primaryArmourNominal) * 100) / 100),
                L", ",
                std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple, primaryArmourNominal) * 100) / 100),
                L"] °"
                }
            );
            penetrationStorage.push_back(std::vector<std::wstring>{L"These gun calibres trigger double overmatch!"});


            Blitz::Funx::PenetrationValueRangeGenerator(penetrationStorage, penetrationChance, std::vector<double>{
                externalModuleThickness +
                Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
                Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble + 0.01, primaryArmourNominal)),

                externalModuleThickness +
                Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
                Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple, primaryArmourNominal))
                }
            );
        }
            
    }

    //penetration case 3
    else {
        //done separately to not include newline char
        penetrationStorage.push_back(std::vector<std::wstring>{L""});
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"Auto-ricochet for gun calibre of ",
            std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
            L"mm or lower!"
            }
        );
        penetrationStorage.push_back(std::vector<std::wstring>{L""});
    }

    //calibre case with triple overmatch
    //done separately to not include newline char
    penetrationStorage.push_back(std::vector<std::wstring>{L""});
    penetrationStorage.push_back(std::vector<std::wstring>{
        L"For gun calibre: (",
        std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
        L",   \u221e   ) mm applied normalization [",
        std::to_wstring(round(Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple + 0.01, primaryArmourNominal) * 100) / 100),
        L",  90   ] °"
        }
    );
    penetrationStorage.push_back(std::vector<std::wstring>{L"These gun calibres trigger double and triple overmatch!"});


    Blitz::Funx::PenetrationValueRangeGenerator(penetrationStorage, penetrationChance, std::vector<double>{
        externalModuleThickness +
        Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
        Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreTriple + 0.01, primaryArmourNominal)),
        
        externalModuleThickness +
        Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
        primaryArmourNominal
        }
    );
}


void Blitz::Funx::AgainstChemicalRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double armourNominal, double armourAngle){
    std::vector<double> penetrationChance = { 100, 80, 60, 40, 20 };    //penetration chances for plugging into PenetrationValueGenerator
    
    //done separately to not include newline char
    penetrationStorage.push_back(std::vector<std::wstring>{L">Note maths related to these shell types does not"});
    penetrationStorage.push_back(std::vector<std::wstring>{L"account for external modules or spaced armour!"});

    Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, 0));
}


void Blitz::Funx::PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation){
    //storing from minimum to maximum possible penetration numbers
    for (double i = averagePenetration * (1 - deviation); i < averagePenetration * (1 + deviation); i += 0.01) {
        penetrationRange.push_back(i);
    }
}


void Blitz::Funx::PenetrationValueGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, double totalEffectiveArmour){
    penetrationStorage.push_back(std::vector<std::wstring>{L"Chance of penetration:"});

    //repeating over rest of the given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"% for average penetration of ",
            std::to_wstring(round(totalEffectiveArmour / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm"
            }
        );
    }
}


void Blitz::Funx::PenetrationValueRangeGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, std::vector<double> totalEffectiveArmour){
    penetrationStorage.push_back(std::vector<std::wstring>{L"Chance of penetration:"});

    //repeating over rest of the given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"% for average penetration: [",
            std::to_wstring(round(totalEffectiveArmour[0] / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L", ",
            std::to_wstring(round(totalEffectiveArmour[1] / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"] mm for respective calibres"
            }
        );
    }
}


double Blitz::Funx::NormalizationIncreased(double shellNormalizaitonAngle, double shellCalibre, double armourNominal){
    if (shellCalibre > armourNominal * 2) {
        return shellNormalizaitonAngle * 1.4 * shellCalibre / armourNominal / 2;
    }

    return shellNormalizaitonAngle;
}


double Blitz::Funx::ArmourEffectiveness(double armourNominal, double armourAngle, double normalizationAngle){
    if (armourAngle - normalizationAngle > 0) {
        return armourNominal / cos(OtherFunx::DegreeToRadian(armourAngle - normalizationAngle));
    }
    
    return armourNominal / cos(OtherFunx::DegreeToRadian(0));
}


double Blitz::Funx::GetRng(double percentage){
    if (percentage > 100) {
        percentage = 100;
    }

    else if (percentage < 0) {
        percentage = 0;
    }

    return 1 + ((percentage - 50.05) / (-9.99) / 100);
}

//foch 155 bug, table is sliding left /*quite possibly a console resizing bug not related to this code*/
void Blitz::Funx::DisplayData(std::vector<Blitz::ShellData>& shellData) {
    unsigned int longestSentenceInEnhancedArmourOff = 0;        //stores size of longest string in enchanced armour off of ShellData element

    /*
    removing unnecessary 0 artifacts from given shellData Array after converting double to string via std::to_wstring()
    
    also finding longest sentence in enhanced armour off (for tabular view)
    
    increasing size of enhanced armour off array so all lines from enhanced armour on can be outputted 
    niche case where triple overmatch bypass on tracks is equals to double overmatch on primary armour, this case is
    ignored for enhanced armour off but with enhanced armour on nominal armour value changes and thus not ignored
    */
    for (unsigned int a = 0; a < shellData.size(); a++) {
        for (unsigned int b = 0; b < shellData[a].enhancedArmourOff.size(); b++) {
            OtherFunx::RemoveUnnecessaryZerosFromWstringVector(shellData[a].enhancedArmourOff[b]);

            //determining longest size of line in shellData
            unsigned int currentLinesLength = OtherFunx::GetWstringVectorLength(shellData[a].enhancedArmourOff[b]);
            if (longestSentenceInEnhancedArmourOff < currentLinesLength) {
                longestSentenceInEnhancedArmourOff = currentLinesLength;
            }
        }

        for (unsigned int b = 0; b < shellData[a].enhancedArmourOn.size(); b++) {
            OtherFunx::RemoveUnnecessaryZerosFromWstringVector(shellData[a].enhancedArmourOn[b]);
        }


        for (unsigned int b = shellData[a].enhancedArmourOff.size(); b < shellData[a].enhancedArmourOn.size(); b++) {
            shellData[a].enhancedArmourOff.push_back(std::vector<std::wstring>{L""});
        }
    }

    
    //outputting all shell type data from shellData
    for (unsigned int a = 0; a < shellData.size(); a++) {
        std::wcout << L"     Shell Type: " << shellData[a].shellDisplayName << "\n\n";

        for (unsigned int b = 0; b <= 2 * longestSentenceInEnhancedArmourOff; b++) {
            std::wcout << "-";
        }

        std::wcout << L"\nenhanced armour: off"; 

        for (unsigned int b = 20; b < longestSentenceInEnhancedArmourOff; b++) {
            std::wcout << " ";
        }
        std::wcout << L"| enhanced armour: on\n";

        //outputting all strings from shell types
        for (unsigned int b = 0; b < shellData[a].enhancedArmourOff.size(); b++) {
            unsigned int lastLineStopedAt = OtherFunx::GetWstringVectorLength(shellData[a].enhancedArmourOff[b]);       //stores where last enchanced armour off sentance left off

            //outputting all characters of enhance armour off line
            for (unsigned int c = 0; c < shellData[a].enhancedArmourOff[b].size(); c++) {
                std::wcout << shellData[a].enhancedArmourOff[b][c];
            }

            for (unsigned int c = lastLineStopedAt; c < longestSentenceInEnhancedArmourOff; c++) {
                std::wcout << L" ";
            }

            std::wcout << "| ";

            //outputting enhance armour on line
            for (unsigned int c = 0; c < shellData[a].enhancedArmourOn[b].size(); c++) {
                std::wcout << shellData[a].enhancedArmourOn[b][c];
            }

            std::wcout << "\n";
        }
        

        for (unsigned int b = 0; b <= 2 * longestSentenceInEnhancedArmourOff; b++) {
            std::wcout << "-";
        }
        std::wcout << "\n\n";
    }
}
