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


        BlitzFunx::AgainstKeneticRounds("AP", 5, armourNominal, armourAngle);
        std::cout << "____________________________________________________________________________\n";

        BlitzFunx::AgainstKeneticRounds("APCR", 2, armourNominal, armourAngle);
        std::cout << "____________________________________________________________________________\n\n";
    }

    return 0;
}
