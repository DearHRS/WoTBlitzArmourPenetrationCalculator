#include "Blitz.h"


Blitz::ShellData::ShellData(std::wstring shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle, double externalModuleThickness, double spaceArmourNominal, double spacedArmourAngle) {
    this->shellDisplayName = shellDisplayName;

    Funx::AgainstKineticRounds(enhancedArmourOff, normalizationAngle, armourNominal, armourAngle, externalModuleThickness, spaceArmourNominal, spacedArmourAngle);
    Funx::AgainstKineticRounds(enhancedArmourOn, normalizationAngle, armourNominal * 1.04, armourAngle, externalModuleThickness * 1.04, spaceArmourNominal * 1.04, spacedArmourAngle);
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
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"0",
            L"mm < gun calibre <= ",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L"mm"
            }
        );

        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance,
            externalModuleThickness +
            Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, primaryArmourOvermatchCalibreDouble, primaryArmourNominal)) +
            Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0)
        );


        //calibre case with double overmatch
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"\n",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L"mm < gun calibre <= ",
            std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
            L"mm"
            }
        );

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
            triggerStatement = L"Triple overmatch bypass triggered on spaced armour!\n";
        }
        else if (spacedArmourNominal == 0) {
            tripleOverMatchBypass = externalModuleThickness * 3;
            triggerStatement = L"Triple overmatch bypass triggered on external modules!\n";
        }
        else if (spacedArmourNominal < externalModuleThickness) {
            tripleOverMatchBypass = spacedArmourNominal * 3;
            triggerStatement = L"Triple overmatch bypass triggered on spaced armour!\n";
        }
        else {
            tripleOverMatchBypass = externalModuleThickness * 3;
            triggerStatement = L"Triple overmatch bypass triggered on external modules!\n";
        }

        //calibre case with no double overmatch
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"\n",
            triggerStatement,
            std::to_wstring(round(tripleOverMatchBypass * 100) / 100),
            L"mm < gun calibre <= ",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L"mm"
            }
        );

        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance,
            externalModuleThickness +
            Blitz::Funx::ArmourEffectiveness(spacedArmourNominal, spacedArmourAngle, 0) +
            Blitz::Funx::ArmourEffectiveness(primaryArmourNominal, primaryArmourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizationAngle, tripleOverMatchBypass + 0.01, primaryArmourNominal))
        );


        //calibre case with double overmatch
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"\n",
            std::to_wstring(round(primaryArmourOvermatchCalibreDouble * 100) / 100),
            L"mm < gun calibre <= ",
            std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
            L"mm"
            }
        );

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

    //penetration case 3
    else {
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"\n",
            L"Auto-ricochet for gun calibre of ",
            std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
            L"mm or lower!"
            }
        );
    }

    //calibre case with triple overmatch
    penetrationStorage.push_back(std::vector<std::wstring>{
        L"\n",
        std::to_wstring(round(primaryArmourOvermatchCalibreTriple * 100) / 100),
        L"mm < gun calibre <    \u221e   mm"
        }
    );

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

    Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, 0));
}


void Blitz::Funx::PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation){
    //storing from minimum to maximum possible penetration numbers
    for (double i = averagePenetration * (1 - deviation); i < averagePenetration * (1 + deviation); i += 0.01) {
        penetrationRange.push_back(i);
    }
}


void Blitz::Funx::PenetrationValueGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, double totalEffectiveArmour){
    //repeating over rest of the given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"% chance of penetration for average penetration of ",
            std::to_wstring(round(totalEffectiveArmour / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm"
        });
    }
}


void Blitz::Funx::PenetrationValueRangeGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, std::vector<double> totalEffectiveArmour){
    //repeating over rest of the given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"% chance of penetration for average penetration of ",
            std::to_wstring(round(totalEffectiveArmour[0] / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm and ",
            std::to_wstring(round(totalEffectiveArmour[1] / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm, for respective calibre"
        });
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


void Blitz::Funx::DisplayData(std::vector<Blitz::ShellData>& shellData) {
    std::vector<unsigned int> longestSentence;      //used to find longest string of characters per ShellData element

    //removing unnecessary 0 artifacts from given shellData Array after converting double to string via std::to_wstring()
    for (unsigned int a = 0; a < shellData.size(); a++) {
        for (unsigned int b = 0; b < shellData[a].enhancedArmourOff.size(); b++) {
            OtherFunx::RemoveUnnecessaryZerosFromWstringVector(shellData[a].enhancedArmourOff[b]);
        }

        for (unsigned int b = 0; b < shellData[a].enhancedArmourOn.size(); b++) {
            OtherFunx::RemoveUnnecessaryZerosFromWstringVector(shellData[a].enhancedArmourOn[b]);
        }
    }


    for (unsigned int a = 0; a < shellData.size(); a++) {
        std::wcout << L"     Shell Type: " << shellData[a].shellDisplayName << "\n";
        std::wcout << L"enhanced armour: off\n";

        //outputting all strings from
        for (unsigned int b = 0; b < shellData[a].enhancedArmourOff.size(); b++) {
            for (unsigned int c = 0; c < shellData[a].enhancedArmourOff[b].size(); c++) {
                std::wcout << shellData[a].enhancedArmourOff[b][c];
            }

            std::wcout << "\n";
        }
        std::wcout << "\n\n";

        std::wcout << L"enhanced armour: on\n";

        for (unsigned int b = 0; b < shellData[a].enhancedArmourOn.size(); b++) {
            for (unsigned int c = 0; c < shellData[a].enhancedArmourOn[b].size(); c++) {
                std::wcout << shellData[a].enhancedArmourOn[b][c];
            }

            std::wcout << "\n";
        }
        std::wcout << "------------------------------------------------------------------------------------------------------\n\n";
    }
}
