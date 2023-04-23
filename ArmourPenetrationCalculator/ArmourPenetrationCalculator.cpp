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
        double armourNominal = OtherFunx::GetDouble(L"  enter value of nominal armour: ");          //variable for base armour thickness (set by user)
        double armourEffective = OtherFunx::GetDouble(L"enter value of effective armour: ");        //variable for relative thickness of base armour at some angle (set by user)
        double armourAngle = OtherFunx::RadianToDegree(acos(armourNominal / armourEffective));      //variable for shell's impacting angle relative to normal armour

        std::wcout << L"\t\t   impact angle: " << round(armourAngle * 100) / 100 << L"\u00B0\n\n";  //outputting possbile angle for given inputs with ° symbol


        std::vector<Blitz::ShellData> rounds = {
            Blitz::ShellData(L"AP", 5, armourNominal, armourAngle),
            Blitz::ShellData(L"APCR", 2, armourNominal, armourAngle),
            Blitz::ShellData(L"HEAT / HE", armourNominal, armourAngle)
        };

        Blitz::Funx::DisplayData(rounds);
    }

    return 0;
}
