#include "Blitz.h"


Blitz::ShellData::ShellData(std::wstring shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle) {
    this->shellDisplayName = shellDisplayName;

    Funx::AgainstKineticRounds(enhancedArmourOff, normalizationAngle, armourNominal, armourAngle);
    Funx::AgainstKineticRounds(enhancedArmourOn, normalizationAngle, armourNominal * 1.04, armourAngle);
}


Blitz::ShellData::ShellData(std::wstring shellDisplayName, double armourNominal, double armourAngle) {
    this->shellDisplayName = shellDisplayName;

    Funx::AgainstChemicalRounds(enhancedArmourOff, armourNominal, armourAngle);
    Funx::AgainstChemicalRounds(enhancedArmourOn, armourNominal * 1.04, armourAngle);
}


void Blitz::Funx::AgainstKineticRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double shellNormalizaitonAngle, double armourNominal, double armourAngle){
    double overmatchCalibreTriple = armourNominal * 3;                  //lowest calibre right under triple overmatch for given nominal armour
    double overmatchCalibreDouble = armourNominal * 2;                  //lowest calibre right under double overmatch for given nominal armour
    std::vector<double> penetrationChance = { 100, 90, 80, 70, 60 };    //penetration chances for plugging into PenetrationValueGenerator and PenetrationValueGeneratorRange functions

    if (armourAngle < 70) {
        //calibre case 1
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"0 mm", 
            L"<", 
            L"gun calibre", 
            L"<=", 
            std::to_wstring(round(overmatchCalibreDouble * 100) / 100),
            L"mm"
        });

        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreDouble, armourNominal)));

        /*
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"100% penetration at:", 
            std::to_wstring(round(Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreDouble, armourNominal)) / (1 - Blitz::Funx::GetRng(100)) * 100) / 100),
            L"mm"
        });
        */

        
        //calibre case 2
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(overmatchCalibreDouble * 100) / 100),
            L"mm",
            L"<", 
            L"gun calibre", 
            L"<=", 
            std::to_wstring(round(overmatchCalibreTriple * 100) / 100),
            L"mm"
        });
        
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"100% penetration at:", 
            std::to_wstring(round(Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreDouble, armourNominal)) / 0.95 * 100) / 100),
            L"mm", 
            L"to",
            std::to_wstring(round(Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreTriple, armourNominal)) / 0.95 * 100) / 100),
            L"mm"
        });
    }

    else {
        penetrationStorage.push_back(std::vector<std::wstring>{
            L"autoricochet for gun calibre of " + std::to_wstring(round(overmatchCalibreTriple * 100) / 100),
            L"mm or lower!"
        });
    }

    //calibre case 3
    penetrationStorage.push_back(std::vector<std::wstring>{
        std::to_wstring(round(overmatchCalibreTriple * 100) / 100),
        L"mm",
        L"<",
        L"gun calibre",
        L"<=",
        L"\u221e mm"
    });

    penetrationStorage.push_back(std::vector<std::wstring>{
        L"100% penetration at:",
        std::to_wstring(round(Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreTriple + 0.01, armourNominal)) / 0.95 * 100) / 100),
        L"mm",
        L"to",
        std::to_wstring(round(armourNominal / 0.95 * 100) / 100),
        L"mm"
    });
}


void Blitz::Funx::AgainstChemicalRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double armourNominal, double armourAngle){
    penetrationStorage.push_back(std::vector<std::wstring>{
        L"100% penetration at:",
        std::to_wstring(round(Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, 0) / 0.95 * 100) / 100),
        L"mm"
    });
}


void Blitz::Funx::PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation){
    //storing from minimum to maximum possible penetration numbers
    for (double i = averagePenetration * (1 - deviation); i < averagePenetration * (1 + deviation); i += 0.01) {
        penetrationRange.push_back(i);
    }
}


void Blitz::Funx::PenetrationValueGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, double effectiveArmour){
    //repeating over every given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"chance of penetration at:",
            std::to_wstring(round(effectiveArmour / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm"
        });
    }
}


void Blitz::Funx::PenetrationValueRangeGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, double effectiveArmour1, double effectiveArmour2){
    //repeating over every given chance and adding result to given string vector vector
    for (unsigned int a = 0; a < penetrationChances.size(); a++) {
        penetrationStorage.push_back(std::vector<std::wstring>{
            std::to_wstring(round(penetrationChances[a] * 100) / 100),
            L"chance of penetration from ",
            std::to_wstring(round(effectiveArmour1 / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100),
            L"mm to",
            std::to_wstring(round(effectiveArmour2 / Blitz::Funx::GetRng(penetrationChances[a]) * 100) / 100)
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


    //had idea to put all this into 1 string and later output
}
