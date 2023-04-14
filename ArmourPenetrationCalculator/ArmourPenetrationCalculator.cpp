// ArmourAngleCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cmath>
#include "OtherFunx.h"
#include "BlitzFunx.h"


int main(){
    while (true){
        double armourNominal = OtherFunx::GetDouble("  enter value of nominal armour: ");       //variable for nominal armour (set by user)
        double armourEffective = OtherFunx::GetDouble("enter value of effective armour: ");     //variable for effective armour (set by user)
        double armourAngle = OtherFunx::RadianToDegree(acos(armourNominal / armourEffective));  //variable for shell's impacting angle relative to armour's normal 

        std::cout << "impact angle = " << armourAngle << "\370 \n\n";

        /*std::vector<double> test;
        BlitzFunx::PenetrationRangeGenerator(test, 315, 0.05);*/

    }

    return 0;
}
