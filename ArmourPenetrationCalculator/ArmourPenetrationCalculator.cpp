// ArmourAngleCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include "OtherFunx.h"
#include "Blitz.h"


int main(){
    //setting console to use unicode hex characters
    _setmode(_fileno(stdin), 0x00020000);
    _setmode(_fileno(stdout), 0x00020000);

    while (true){
        double armourNominal = OtherFunx::GetDouble(L"  enter value of nominal armour: ");      //variable for base armour thickness (set by user)
        double armourEffective = OtherFunx::GetDouble(L"enter value of effective armour: ");    //variable for relative thickness of base armour at some angle (set by user)
        double armourAngle = OtherFunx::RadianToDegree(acos(armourNominal / armourEffective));  //variable for shell's impacting angle relative to normal armour

        std::wcout << L"\t\t  impact angle : " << round(armourAngle * 100) / 100 << L"\u00B0\n\n";

        std::vector<double> penetrationChance = { 100, 90, 80, 70, 60 };
        std::vector<std::vector<std::wstring>> penetrationStorage;

        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(5, 100, armourNominal)));
        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(2, 100, armourNominal)));
        Blitz::Funx::PenetrationValueGenerator(penetrationStorage, penetrationChance, Blitz::Funx::ArmourEffectiveness(armourNominal, armourAngle, Blitz::Funx::NormalizationIncreased(0, 0, armourNominal)));
        
        for (unsigned int a = 0; a < penetrationStorage.size(); a++) {
            for (unsigned int b = 0; b < penetrationStorage[a].size(); b++) {
                std::wcout << penetrationStorage[a][b] << " ";
            }

            std::wcout << "\n\n";
        }




        /*std::vector<Blitz::ShellData> rounds = {
            Blitz::ShellData(L"AP", 5, armourNominal, armourAngle),
            Blitz::ShellData(L"APCR", 2, armourNominal, armourAngle),
            Blitz::ShellData(L"HEAT / HE", armourNominal, armourAngle)
        };

        Blitz::Funx::DisplayData(rounds);*/
    }

    return 0;
}
