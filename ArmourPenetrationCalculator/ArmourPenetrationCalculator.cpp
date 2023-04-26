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
    //setting console to use unicode hex characters on input and output
    _setmode(_fileno(stdin), 0x00020000);
    _setmode(_fileno(stdout), 0x00020000);
    

    //launch blitzHangar and armourInspector?
    while (true) {
        std::wstring givenAnswer;
        std::wcout << "Would you like to launch ArmorInspector or Blitzhangar? (yes/no)\n";
        std::getline(std::wcin, givenAnswer);

        if (givenAnswer == L"yes" || givenAnswer == L"no") {
            if (givenAnswer == L"yes") {
                system("start /max https://blitzhangar.com/en");
                system("start /max https://armor.wotinspector.com/?targetVehicleId=9489,23058,18451,14100&mode=xray.armor&platform=blitz");
            }

            system("cls");
            break;
        }
        else {
            std::wcout << "\terror: >" << givenAnswer << "< is not 'yes' or 'no'\n\n";
        }
    }


    while (true){
        std::wcout << L"Enter value of below parameters (in mm) |\n";
        std::wcout << L"________________________________________|\n\n";

        double armourNominal = OtherFunx::GetPositiveDouble(L"                                   nominal armour thickness: ");                          //variable for base armour thickness (set by user)
        double armourEffective;                                                                                                                         //variable for relative thickness of base armour at some angle (set by user)
        
        //repeating until correct effective armour value is passed
        while (true) {
            armourEffective = OtherFunx::GetPositiveDouble(L"                                 effective armour thickness: ");

            if (armourNominal <= armourEffective) {
                break;
            }
            else{
                std::wcout << "\n\t |error: given effective armour >" << armourEffective << "< can not be lower that nominal armour!|\n\n";
            }
        }
       
        double armourAngle = OtherFunx::RadianToDegree(acos(armourNominal / armourEffective));                                                          //variable for shell's impacting angle relative to normal armour                      
        std::wcout << L"                                         shell impact angle: " << round(armourAngle * 100) / 100 << L"°\n";                     //outputting possbile angle for given inputs with ° symbol


        double trackThickness = OtherFunx::GetDouble(L"      external module thickness (enter '0' if not impacted): ");                                 //variable for track thickness
        
        double armourSpacedNominal = OtherFunx::GetDouble(L"nominal spaced armour thickness (enter '0' if not impacted): ");                            //varible for nominal spaced armour
        double armourSpacedEffective = 0;                                                                                                               //variable for effective spaced armour
        double armourSpacedAngle = 0;                                                                                                                   //variable for shell's impacting angle relative to normal of spaced armour

        if (armourSpacedNominal > 0) {
            while (true) {
                armourSpacedEffective = OtherFunx::GetPositiveDouble(L"                          effective spaced armour thickness: ");

                if (armourSpacedNominal <= armourSpacedEffective) {
                    double armourSpacedAngle = OtherFunx::RadianToDegree(acos(armourSpacedNominal / armourSpacedEffective));
                    std::wcout << L"                                         shell impact angle: " << round(armourSpacedAngle * 100) / 100 << L"°\n";   //outputting possbile angle for given inputs with ° symbol
                    break;
                }
                else {
                    std::wcout << "\n\t |error: given effective armour >" << armourSpacedEffective << "< can not be lower that nominal spaced armour!|\n\n";
                }
            }            
        }        
        
        std::wcout << "\n";


        std::vector<Blitz::ShellData> rounds = {
            Blitz::ShellData(L"AP", 5, armourNominal, armourAngle, trackThickness, armourSpacedNominal, armourSpacedAngle),
            Blitz::ShellData(L"APCR", 2, armourNominal, armourAngle, trackThickness, armourSpacedNominal, armourSpacedAngle),
            Blitz::ShellData(L"HEAT / HE / HESH / HEP", armourNominal, armourAngle)
        };

        Blitz::Funx::DisplayData(rounds);
    }

    return 0;
}
