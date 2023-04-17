#include "BlitzFunx.h"

void BlitzFunx::AgainstKineticRounds(std::string shellDisplayName, double shellNormalizaitonAngle, double armourNominal, double armourAngle){
    
    std::cout << "      Shell type: " << shellDisplayName << "\n";
    std::cout << "Enchanced armour: off" << "\n\n";
    for (unsigned int i = 0; i < 2; i++) {
        double overmatchCalibreTriple = armourNominal * 3;   //lowest calibre right under triple overmatch for given nominal armour
        double overmatchCalibreDouble = armourNominal * 2;   //lowest calibre right under double overmatch for given nominal armour

        if (armourAngle < 70) {
            //calibre case 1
            std::cout << "0mm\t< gun calibre <= " << overmatchCalibreDouble << "mm\n";
            std::cout << "100% penetration at: " << BlitzFunx::ArmourEffectiveness(armourNominal, armourAngle, BlitzFunx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreDouble, armourNominal)) * 1.05 << "mm\n\n";

            //calibre case 2
            std::cout << overmatchCalibreDouble << "mm\t< gun calibre <= " << overmatchCalibreTriple << "mm\n";
            std::cout << "100% penetration at: " << BlitzFunx::ArmourEffectiveness(armourNominal, armourAngle, BlitzFunx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreDouble + 0.01, armourNominal)) * 1.05
                << "mm to " << BlitzFunx::ArmourEffectiveness(armourNominal, armourAngle, BlitzFunx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreTriple, armourNominal)) * 1.05 << "mm\n\n";
        }

        else {
            std::cout << "autoricochet for gun calibre of " << overmatchCalibreTriple << "mm or lower! \n";
        }

        //calibre case 3
        std::cout << overmatchCalibreTriple << "mm\t< gun calibre < INFINITE mm\n";
        std::cout << "100% penetration at: " << BlitzFunx::ArmourEffectiveness(armourNominal, armourAngle, BlitzFunx::NormalizationIncreased(shellNormalizaitonAngle, overmatchCalibreTriple + 0.01, armourNominal)) * 1.05 << "mm to " << armourNominal * 1.05 << "mm\n\n";

        if (i == 0) {
            armourNominal = armourNominal * 1.04;
            std::cout << "\nEnchanced armour: on" << "\n\n";
        }        
    }
}


void BlitzFunx::AgainstChemicalRounds(std::string shellDisplayName, double normalizationAngle, double armourNominal, double armourEffective, double armourAngle){

}


void BlitzFunx::PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation){
    //storing from minimum to maximum possible penetration numbers
    for (double i = averagePenetration * (1 - deviation); i < averagePenetration * (1 + deviation); i += 0.01) {
        penetrationRange.push_back(i);
    }
}


double BlitzFunx::NormalizationIncreased(double shellNormalizaitonAngle, double shellCalibre, double armourNominal){
    if (shellCalibre > armourNominal * 2) {
        return shellNormalizaitonAngle * 1.4 * shellCalibre / armourNominal / 2;
    }

    return shellNormalizaitonAngle;
}


double BlitzFunx::ArmourEffectiveness(double armourNominal, double armourAngle, double normalizationAngle){
    if (armourAngle - normalizationAngle > 0) {
        return armourNominal / cos(OtherFunx::DegreeToRadian(armourAngle - normalizationAngle));
    }
    
    return armourNominal / cos(OtherFunx::DegreeToRadian(0));
}