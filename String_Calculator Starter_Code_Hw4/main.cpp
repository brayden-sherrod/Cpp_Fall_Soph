#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): implement the UI

    string leftSide = "";
    string fnct = "";
    string rightSide = "";
    string answer = "";
    cin >> leftSide;
    while (leftSide != "q") {
        cin >> fnct >> rightSide;
        if (leftSide == "ans") {
            leftSide = answer;
        }
        if (rightSide == "ans") {
            rightSide = answer;
        }
    
        leftSide = trim_leading_zeros(leftSide);
        rightSide = trim_leading_zeros(rightSide);

        
        string answer = "0";
        if (fnct == "+") {
            answer = add(leftSide, rightSide);
        } else if (fnct == "-") {
            answer = subtract(leftSide, rightSide);
        } else if (fnct == "*") {
            answer = multiply(leftSide, rightSide);
        }
        cout << ">> " << endl;
        cout << "ans =" << endl << endl << "    " << answer << endl << endl;
        
        cin >> leftSide;
    }
    cout << ">>" << endl << "farvel!" << endl << endl;
}

