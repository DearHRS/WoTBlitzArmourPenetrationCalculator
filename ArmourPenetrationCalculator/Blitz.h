#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "OtherFunx.h"


namespace Blitz{
	/*
	stores penetration required data for given armour and shell type
	*/
	struct ShellData {
		std::wstring shellDisplayName;								//stores shell name
		std::vector<std::vector<std::wstring>> enhancedArmourOff;	//stores required penetration value(s) without enhanced armour
		std::vector<std::vector<std::wstring>> enhancedArmourOn;	//stores required penetration value(s) with enhanced armour


		//Constructor for kinetic rounds
		ShellData(std::wstring shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle);

		//Constructor for chemical rounds
		ShellData(std::wstring shellDisplayName, double armourNominal, double armourAngle);
	};


	/*
	Static class related to blitz functions
	includes <iostream>, <string>, <vector> and <math.h>
	*/
	class Funx {

	public:
		/*
		Stores minimum penetration required to overcome 
		armour for AP / APCR rounds for 3 shell caliber cases
		at 100%, 90%, 80%, 70% and 60%
		calibre case 1: less than equals to 2 times the nominal
		calibre case 2: more than 2 times the nominal to 3 times the nominal
		calibre case 3: more than 3 times the nominal
		*/
		static void AgainstKineticRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double normalizationAngle, double armourNominal, double armourAngle);

		/*
		Stores minimum caliber and penetration required to
		overcome armour for HEAT and HE/HESH rounds
		at 100%, 90%, 80%, 70% and 60%
		*/
		static void AgainstChemicalRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double armourNominal, double armourAngle);

		/*
		unutilized function
		Returns dynamic array filled with all the possbile penetrations values
		*/
		static void PenetrationRangeGenerator(std::vector<double>& penetrationRange, double averagePenetration, double deviation);

		/*
		returns penetration value(s) for given chance of penetration array
		*/
		static void PenetrationValueGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, double effectiveArmour);

		/*
		returns penetration range from value(s) to value(s) for given chance of penetration array
		*/
		static void PenetrationValueRangeGenerator(std::vector<std::vector<std::wstring>>& penetrationStorage, std::vector<double>& penetrationChances, std::vector<double> effectiveArmour);

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

		/*
		returns required rng to penetrate an armour plate

		value ranges from ~0.95 to ~1.05
		*/
		static double GetRng(double percentage);

		/*
		Displays all of the data horizontally from shellData array
		*/
		static void DisplayData(std::vector<Blitz::ShellData>& shellData);
	};
}
