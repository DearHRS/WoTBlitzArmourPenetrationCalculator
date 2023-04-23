#include "OtherFunx.h"


double OtherFunx::GetDouble(std::wstring inputMessage){
    while (true) {
        std::wstring userInput;

        std::wcout << inputMessage;
        std::getline(std::wcin, userInput);

        if (IsNumeric(userInput)) {
            ReplaceCommaToPoint(userInput);
            return std::stod(userInput);
        }
        else {
            std::wcout << L"\terror: >" << userInput << L"< isn't numeric\n\n";
        }
    }
}


bool OtherFunx::IsNumeric(std::wstring givenWstring){
    unsigned int commaPointCounter = 0;

    if (givenWstring.size() == 0 || givenWstring[givenWstring.size() - 1] == L'.' || givenWstring[givenWstring.size() - 1] == L',') {
        return false;
    }

    for (unsigned int i = 0; i < givenWstring.size(); i++) {
        switch (givenWstring[i]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            continue;

        case '.':
        case ',':
            commaPointCounter++;
            if (commaPointCounter > 1) {
                return false;
            }
            continue;

        default:
            return false;
        }
    }

    return true;
}


void OtherFunx::ReplaceCommaToPoint(std::wstring& givenWstring){
    for (unsigned int i = 0; i < givenWstring.size(); i++) {
        switch (givenWstring[i]) {
        case ',':
            givenWstring[i] = '.';
            break;
        }
    }
}


double OtherFunx::RadianToDegree(double givenRadian){
    return givenRadian * 180 / 3.14159265359;
}


double OtherFunx::DegreeToRadian(double givenDegree){
    return givenDegree * 3.14159265359 / 180;
}


void OtherFunx::RemoveUnnecessaryZerosFromWstringVector(std::vector<std::wstring>& givenVector){
    for (unsigned int a = 0; a < givenVector.size(); a++) {
        OtherFunx::RemoveUnncessaryZeroFromWstring(givenVector[a]);
    }
}


void OtherFunx::RemoveUnncessaryZeroFromWstring(std::wstring& givenString){
    if (OtherFunx::IsNumeric(givenString)) {
        std::wstring replacementWstring = givenString;

        for (int a = givenString.size() - 1; a >= 0; a--) {
            switch (givenString[a]) {
            case '0':
                replacementWstring.erase(a);
                break;


            case '.':
                replacementWstring.erase(a);

            default:
                givenString = replacementWstring;
                return;
            }
        }
    }
}
