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
            std::wcout << L"\t|error: >" << userInput << L"< isn't numeric|\n\n";
        }
    }
}

double OtherFunx::GetPositiveDouble(std::wstring inputMessage){
    while (true) {
        double result = OtherFunx::GetDouble(inputMessage);

        if (result <= 0) {
            std::wcout << "\t|error: >" << result << "< should be positive!|\n\n";
        }
        else {
            return result;
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
        case '-':
            if (i == 0) {
                continue;
            }
            return false;

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
        OtherFunx::MakeNumberLookGood(givenVector[a], 6);
    }
}


void OtherFunx::RemoveUnncessaryZeroFromWstring(std::wstring& givenWstring){
    if (OtherFunx::IsNumeric(givenWstring)) {
        std::wstring replacementWstring = givenWstring;

        for (int a = givenWstring.size() - 1; a >= 0; a--) {
            switch (givenWstring[a]) {
            case '0':
                replacementWstring.erase(a);
                break;


            case '.':
                replacementWstring.erase(a);

            default:
                givenWstring = replacementWstring;
                return;
            }
        }
    }
}


void OtherFunx::MakeNumberLookGood(std::wstring& givenWstring, int mustBeSize){
    if (OtherFunx::IsNumeric(givenWstring) && givenWstring.size() <= mustBeSize) {
        int decimalPosition = -1;       //intializing at impossible decimal position

        //finding where decimal is at
        for (unsigned int a = 0; a < givenWstring.size(); a++) {
            if (givenWstring[a] == L'.') {
                decimalPosition = a;
                break;
            }
        }

        //if no decimal in given number
        if (decimalPosition == -1) {
            decimalPosition = mustBeSize - givenWstring.size();

            for (unsigned int a = 0; a < decimalPosition; a++) {
                if (a % 2 == 0) {
                    givenWstring = givenWstring + L" ";
                }
                else {
                    givenWstring = L" " + givenWstring;
                }
                
            }

            return;
        }

        //if decimal found, we first deal with make sure there is atleast 100th place
        if (givenWstring.size() - 1 - decimalPosition < 2) {
            givenWstring.push_back(' ');
        }

        //dealing with front
        if (decimalPosition < (mustBeSize - 1 - 2)) {
            decimalPosition = mustBeSize - 1 - 2 - decimalPosition;

            for (unsigned int a = 0; a < decimalPosition; a++) {
                givenWstring = L" " + givenWstring;
            }
        }
    }
}

int OtherFunx::GetWstringVectorLength(std::vector<std::wstring>& givenVector){
    unsigned int length = 0;

    for (unsigned int a = 0; a < givenVector.size(); a++) {
        length += givenVector[a].size();
    }

    return length;
}
