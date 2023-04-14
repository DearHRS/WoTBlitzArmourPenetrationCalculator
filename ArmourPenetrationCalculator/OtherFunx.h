#pragma once
#include <iostream>
#include <string>
#include <cmath>


/*
Static class for function not directly related to blitz
includes <iostream>, <string> and <cmath>
*/
class OtherFunx{
public:
	/*
	gets string input from console,
	returns double if given string is numeric
	*/
	static double GetDouble(std::string inputMessage);

	/*
	checks if given string is numeric
	*/
	static bool IsNumeric(std::string givenString);

	/*
	replaces comma to point
	*/
	static void ReplaceCommaToPoint(std::string& givenString);

	/*
	converts radian to degrees
	pi = 180°
	*/
	static double RadianToDegree(double givenRadian);

	/*
	converts degrees to radians
	pi = 180°
	*/
	static double DegreeToRadian(double givenDegree);
};

