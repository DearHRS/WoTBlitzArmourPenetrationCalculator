#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "OtherFunx.h"


/*
Static class related to blitz functions
includes <iostream>, <string> and <vector>
*/
class BlitzFunx {
public:
	/*
	Calculates minimum penetration required to overcome 
	armour for AP / APCR rounds for 3 shell caliber cases
	calibre case 1: less than equals to 2 times the nominal
	calibre case 2: more than 2 times the nominal to 3 times the nominal
	calibre case 3: more than 3 times the nominal

	*/
	static void AgainstKineticRounds(std::string shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle);

	/*
	unitilized function
	Calculates minimum caliber and penetration required to
	overcome armour for HEAT and HE/HESH rounds up until 0%
	*/
	static void AgainstChemicalRounds(std::string shellDisplayName, double shellNormalizaitonAngle, double armourNominal, double armourEffective, double armourAngle);

	/*
	Returns dynamic array filled with all the possbile penetrations values
	*/
	static void PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation);

	/*
	unitilized function
	structure under development
	Outputs chance of penetration

	output: >value< %
	*/
	static void ChanceOfPenetration(std::vector<double>& penetrationRange);

	/*
	returns normalizaiton angle
	if shell caliber > nominal armour * 2 
		new angle = originalAngle * 1.4 * shellCaliber / (2 * primaryArmour)
	else
		no changes
	*/
	static double NormalizationIncreased(double shellNormalizaitonAngle, double shellCaliber, double armourNominal);

	/*
	returns effective armour accounting normalization
		nominalThickness is taken in mm
		angle is taken in °
		normalizationAngle is taken in °
	*/
	static double ArmourEffectiveness(double armourNominal, double armourAngle, double normalizationAngle);
};

