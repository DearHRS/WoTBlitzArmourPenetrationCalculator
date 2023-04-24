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
		ShellData(std::wstring shellDisplayName, double normalizationAngle, double armourNominal, double armourAngle, double externalModuleThickness, double spaceArmourNominal, double spacedArmourAngle);

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
		Stores minimum penetration required to overcome given primary armour, spaced
		and external module with AP / APCR rounds for 5 shell penetration cases
		at 100%, 80%, 60%, 40% and 20%
		penetration case 1: shell angle  < 70° effective primary armour + external module thickness + effective spaced armour
		penetration case 2: shell angle >= 70° && external module triple calibre bypass && || spaced armour triple calibre bypass
		penetration case 3: shell angle >= 70° && primary armour triple calibre overmatch
		*/
		static void AgainstKineticRounds(std::vector<std::vector<std::wstring>>& penetrationStorage, double normalizationAngle, double armourNominal, double armourAngle, double externalModuleThickness, double spaceArmourNominal, double spacedArmourAngle);

		/*
		Stores minimum caliber and penetration required to
		overcome armour for HEAT and HE/HESH rounds
		at 100%, 80%, 60%, 40% and 20%
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
