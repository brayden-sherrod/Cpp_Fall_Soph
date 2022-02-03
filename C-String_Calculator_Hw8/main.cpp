// main.cpp
#include <iostream>
#include <limits>
#include "my_string.h"
#include "my_sstream.h"
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    // TODO(student): put your existing implementation of main here
    /*
    my_string leftSide;
    my_string fnct;
    my_string rightSide;
    my_string answer;
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

        
        my_string answer;
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
    */
}
