#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>


/*
Static class for function not directly related to blitz
includes <iostream>, <string>, <cmath> and <vector>
*/
class OtherFunx{
public:
	/*
	gets string input from console,
	returns double if given string is numeric
	*/
	static double GetDouble(std::wstring inputMessage);

	/*
	checks if given string is numeric
	*/
	static bool IsNumeric(std::wstring givenWstring);

	/*
	replaces comma to point
	*/
	static void ReplaceCommaToPoint(std::wstring& givenWstring);

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

	/*
	array dealing wrapper function for RemoveUnnecessaryZerosFromWstring()
	*/
	static void RemoveUnnecessaryZerosFromWstringVector(std::vector<std::wstring>& givenVector);

	/*
	removes unncessary 0 after decimal point or decimal places
	*/
	static void RemoveUnncessaryZeroFromWstring(std::wstring& givenString);
};

