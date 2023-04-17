// ArmourAngleCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
#include "OtherFunx.h"
#include "BlitzFunx.h"


int main(){
    while (true){
        double armourNominal = OtherFunx::GetDouble("  enter value of nominal armour: ");       //variable for base armour thickness (set by user)
        double armourEffective = OtherFunx::GetDouble("enter value of effective armour: ");     //variable for relative thickness of base armour at some angle (set by user)
        double armourAngle = OtherFunx::RadianToDegree(acos(armourNominal / armourEffective));  //variable for shell's impacting angle relative to normal armour

        std::cout << "\t\t  impact angle : " << armourAngle << "\370 \n\n";


        BlitzFunx::AgainstKineticRounds("AP", 5, armourNominal, armourAngle);
        std::cout << "____________________________________________________________________________\n";

        BlitzFunx::AgainstKineticRounds("APCR", 2, armourNominal, armourAngle);
        std::cout << "____________________________________________________________________________\n";

        BlitzFunx::AgainstChemicalRounds("HEAT / HE", armourNominal, armourAngle);
        std::cout << "____________________________________________________________________________\n";

        std::cout << std::endl;
    }

    return 0;
}
