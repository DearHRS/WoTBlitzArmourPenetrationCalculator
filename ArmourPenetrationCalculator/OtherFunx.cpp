#include "OtherFunx.h"


double OtherFunx::GetDouble(std::string inputMessage){
    while (true) {
        std::string userInput;

        std::cout << inputMessage;
        std::getline(std::cin, userInput);

        if (IsNumeric(userInput)) {
            ReplaceCommaToPoint(userInput);
            return std::stod(userInput);
        }
        else {
            std::cout << "\terror: >" << userInput << "< isn't numeric\n";
        }
    }
}


bool OtherFunx::IsNumeric(std::string givenString){
    unsigned int commaPointCounter = 0;

    if (givenString.size() > 0 && (givenString[givenString.size() - 1] == '.' || givenString[givenString.size() - 1] == ',')) {
        return false;
    }

    for (unsigned int i = 0; i < givenString.size(); i++) {
        switch (givenString[i]) {
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


void OtherFunx::ReplaceCommaToPoint(std::string& givenString){
    for (unsigned int i = 0; i < givenString.size(); i++) {
        switch (givenString[i]) {
        case ',':
            givenString[i] = '.';
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
