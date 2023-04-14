#include "BlitzFunx.h"

void BlitzFunx::AgainstKeneticRounds(std::string shellDisplayName, double shellNormalizaitonAngle, double armourNominal, double armourEffective, double armourAngle){
    double overmatchCalibreTriple = armourNominal * 3;   //lowest calibre right under triple overmatch for given nominal armour
    double overmatchCalibreDouble = armourNominal * 2;   //lowest calibre right under double overmatch for given nominal armour
    

    if (armourAngle < 70) {
        std::cout << "caliber: <=" << overmatchCalibreDouble << "mm\n";
        std::cout << "required penetration: " << BlitzFunx::ArmourEffectiveness(armourNominal, armourAngle, shellNormalizaitonAngle);

            
    }

    std::vector<double> penetrationRange;
    BlitzFunx::PenetrationRangeGenerator(penetrationRange, 1, 0.05);
}


void BlitzFunx::AgainstChemicalRounds(std::string shellDisplayName, double normalizationAngle, double armourNominal, double armourEffective, double armourAngle){

}


void BlitzFunx::PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation){
    //storing from minimum to maximum possible penetration numbers
    for (double i = averagePenetration * (1 - deviation); i < averagePenetration * (1 + deviation); i += 0.01) {
        penetrationRange.push_back(i);
    }
}


double BlitzFunx::NormalizationIncreased(double shellNormalizaitonAngle, double shellCaliber, double armourNominal){
    return shellNormalizaitonAngle * 1.4 * shellCaliber / armourNominal / 2;
}


double BlitzFunx::ArmourEffectiveness(double armourNominal, double angle, double normalizationAngle){
    if (angle - normalizationAngle > 0) {
        return armourNominal / cos(OtherFunx::DegreeToRadian(angle - normalizationAngle));
    }
    else {
        return armourNominal / cos(OtherFunx::DegreeToRadian(0));
    }
    
}