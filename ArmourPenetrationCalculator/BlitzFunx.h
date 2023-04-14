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
	case 1: from 0 to over 2 times the nominal
	case 2: from more than 2 times the nominal to 3 times the nominal
	case 3: from more than 3 times the nominal

	*/
	static void AgainstKeneticRounds(std::string shellDisplayName, double normalizationAngle, double armourNominal, double armourEffective, double armourAngle);

	/*
	Calculates minimum caliber and penetration required to
	overcome armour for HEAT and HE/HESH rounds up until 0%
	*/
	static void AgainstChemicalRounds(std::string shellDisplayName, double shellNormalizaitonAngle, double armourNominal, double armourEffective, double armourAngle);

	/*
	Returns dynamic array filled with all the possbile penetrations values
	*/
	static void PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation);

	/*
	structure under development
	Outputs chance of penetration

	output: >value< %
	*/
	static void ChanceOfPenetration(std::vector<double>& penetrationRange);

	/*
	returns new normalizaiton angle
	new angle = originalAngle * 1.4 * shellCaliber / (2 * primaryArmour)
	*/
	static double NormalizationIncreased(double shellNormalizaitonAngle, double shellCaliber, double armourNominal);

	/*
	returns effective armour accounting normalization
		nominalThickness is taken in mm
		angle is taken in °
		normalizationAngle is taken in °
	*/
	static double ArmourEffectiveness(double armourNominal, double angle, double normalizationAngle);
};

