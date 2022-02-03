#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;


unsigned int digit_to_decimal(char digit) {
    // int decimal = std::atoi(digit);
    int decimal = digit;
    decimal -= 48;
    if (decimal < 0 || decimal > 9) {
        throw std::invalid_argument("");
    } else {
        return decimal;
    }
}

char decimal_to_digit(unsigned int decimal) {
    char digit = decimal + 48;
    if (digit < 48 || digit > 57) {
        throw std::invalid_argument("");
    } else {
        return digit;
    }
}

string trim_leading_zeros(string num) {
    // TODO(student): implement
    bool neg = false;
    if (num[0] == '-') {
        num.replace(0, 1, "");
        neg = true;
    }
    int index = num.find("0");
    while (index == 0) {
        if (num.size() == 1) {
            break;
        }
            num.replace(index, 1, "");
            index = num.find("0");
        }
    if (neg && num != "0") {
        num.insert(0, "-");
    }
    return num;
}

string add(string lhs, string rhs) {
    // TODO(student): implement
    string answer = "";
    string greater = "";
    string lesser = "";
    bool addOne = false;
    bool negativeNums = false;
    if (lhs[0] == '-' && rhs[0] != '-') {
        lhs.replace(0, 1, "");
        answer = subtract(lhs, rhs);
        if (answer.at(0) != '0') {
            answer.insert(0, "-");
        }
        if (answer.at(0) == '-' && answer.at(1) == '-') {
            answer.replace(0, 2, "");
        }
        return answer;
    } else if (lhs[0] != '-' && rhs[0] =='-') {
        rhs.replace(0, 1, "");
        answer = subtract(lhs,rhs);
        return answer;
    }
    if (lhs[0] == '-') {
        lhs.replace(0,1, "");
        rhs.replace(0,1,"");
        negativeNums = true;
    }
    if (lhs.size() >= rhs.size()) {
        greater = lhs;
        lesser = rhs;
    } else {
        greater = rhs;
        lesser = lhs;
    }
    // Loop to go through and add digits
    string carryOver(greater.size(), '0');
    while (!greater.empty()) {
        int lastIndexG = greater.size() - 1;
        // Create Decimals and add
        int decmialCarryOver = digit_to_decimal(carryOver.at(lastIndexG));
        int decimalG = digit_to_decimal(greater.at(lastIndexG));
        carryOver.replace(lastIndexG, 1, "");
        greater.replace(lastIndexG, 1, "");
        int lastIndexL = 0;
        int decimalL = 0;
        if (!lesser.empty()) {
            lastIndexL = lesser.size() - 1;
            decimalL = digit_to_decimal(lesser.at(lastIndexL));
            lesser.replace(lastIndexL, 1, "");
        }
        int newDecimal = decimalG + decimalL + decmialCarryOver;
        if (newDecimal >= 10) {
            newDecimal %= 10;
            if (lastIndexG == 0 && lastIndexL == 0) {
                addOne = true;
            } else {
                carryOver.replace(lastIndexG - 1, 1, "1");
            }
        }
        char newChar = decimal_to_digit(newDecimal);
        answer = newChar + answer;
    }
    if (addOne) {
        answer.insert(0, "1");
        addOne = false;
    }
    if (negativeNums) {
        answer.insert(0, "-");
    }
    return answer;
}

string subtract(string lhs, string rhs) {
    // TODO(student): implement
    string answer = "";
    bool negativeNums = false;
    if (lhs.at(0) != '-' && rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
        answer = add(lhs, rhs);
        return answer;
    } else if (lhs.at(0) == '-' && rhs.at(0) != '-') {
        rhs.insert(0, "-");
        answer = add(lhs, rhs);
        return answer;
    } else if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
        lhs.replace(0, 1, "");
        answer = subtract(rhs, lhs);
        return answer;
    }
    if (lhs.size() < rhs.size()) {
        answer = subtract(rhs, lhs);
        if (answer.at(0) == '-') {
            answer.replace(0, 1, "-");
        } else {
            answer.insert(0, "-");
        }
        return answer;
    }

    // Create copies of each string so can revert if abs(rhs) > abd(lhs)
    string leftCopy = lhs; 
    string rightCopy = rhs; 
    while (!rightCopy.empty()) {
        int lastIndexLeft = leftCopy.size() - 1;
        int lastIndexRight = rightCopy.size() - 1;
        int leftDecimal = digit_to_decimal(leftCopy.at(lastIndexLeft));
        int rightDecimal = digit_to_decimal(rightCopy.at(lastIndexRight));
        int result = leftDecimal - rightDecimal;
        if (result < 0) {
            bool carryOver1 = false;
            int carryOverPlaces = 0;
            for (int i = 0; i <= lastIndexLeft; i++) {
                // Re-call subtract if carry over place doesn't exist
                if (lastIndexLeft - i < 1){
                    answer = subtract(rhs,lhs);
                    answer.insert(0, "-");
                    return answer;
                }
                int carryOverDecimal = digit_to_decimal(leftCopy.at(lastIndexLeft - i - 1));
                if (carryOverDecimal > 0) {
                    if (i >= 1) {
                        carryOver1 = true;
                        carryOverPlaces = i;
                    }
                    int replaceValue = carryOverDecimal - 1;
                    char replaceDigit = decimal_to_digit(replaceValue);
                    leftCopy.replace(lastIndexLeft - i - 1, 1, 1, replaceDigit);
                    break;
                }
                
            } // Handles carryover if the digit more than 1 away
            if (carryOver1) {
                for (int i = 0; i < carryOverPlaces; i++) {
                    leftCopy.replace(lastIndexLeft - carryOverPlaces + i, 1, "9");
                }
            }
            result = (leftDecimal + 10) - rightDecimal;
        }
        char insertDigit = decimal_to_digit(result);
        answer = insertDigit + answer;
        leftCopy.replace(lastIndexLeft, 1, "");
        rightCopy.replace(lastIndexRight, 1, "");
        
    }
    while (!leftCopy.empty()) {
        int lastIndexLeft = leftCopy.size() - 1;
        char result = leftCopy.at(lastIndexLeft);
        if (result == 0 && lastIndexLeft == 0) {
             break;
        }
        answer = result + answer;
        leftCopy.replace(lastIndexLeft, 1, "");
        
    }
    if (negativeNums) {
        answer.insert(0, "-");
    }
    return trim_leading_zeros(answer);
}

string multiply(string lhs, string rhs) {
    // TODO(student): implement
    string answer = "";
    string greater = "";
    string lesser = "";
    bool negativeNums = false;
    if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        lhs.replace(0,1, "");
        rhs.replace(0,1,"");
    } else if (lhs.at(0) == '-') {
        lhs.replace(0, 1, "");
        negativeNums = true;
    } else if (rhs.at(0) == '-') {
        rhs.replace(0, 1, "");
        negativeNums = true;
    }
    if (lhs.size() > rhs.size()) {
        greater = lhs;
        lesser = rhs;
    } else {
        greater = rhs;
        lesser = lhs;
    }
    // Loop to multiply each of the digits
    string carryOver(greater.size(), '0');
    int zeroAdjustCount = 0;
    while (!lesser.empty()) {
        bool insertExtra = false;
        string newSum = "";
        int lastIndexG = greater.size() - 1;
        int lastIndexL = lesser.size() - 1;
        int decimalL = digit_to_decimal(lesser.at(lastIndexL));
        // Loop through all of the digits in greater
        for (int i =0; i <= lastIndexG; i++) {
            // Continues to iterate through each of the digits in the shorter number
            int decmialCarryOver = digit_to_decimal(carryOver.at(lastIndexG - i));
            carryOver.replace(lastIndexG - i, 1, "0");
            int decimalG = digit_to_decimal(greater.at(lastIndexG - i));
            int newDecimal = (decimalG * decimalL) + decmialCarryOver;
            char carryOverDigit ='0';
            // Handles the case where the digit would be greater than 10
            if (newDecimal >= 10) {
                int carryOverDecimal =  (newDecimal / 10) % 10;
                newDecimal %= 10;
                carryOverDigit = decimal_to_digit(carryOverDecimal);
                if (i + 1 <= lastIndexG) {
                    carryOver.replace(lastIndexG - i - 1, 1, 1, carryOverDigit);
                } else {
                    insertExtra = true;
                }
            }
            char newChar = decimal_to_digit(newDecimal);
            newSum = newChar + newSum;
            if (insertExtra) {
                newSum = carryOverDigit + newSum;
                insertExtra =false;
            }
        }
        for (int i = 0; i < zeroAdjustCount; i++) {
            newSum.insert(newSum.size(), "0");
        }
        answer = add(answer, newSum);
        lesser.replace(lastIndexL, 1, "");
        zeroAdjustCount ++;
    }
    // Adds the negative sign if the two numbers had opposing signs
    if (negativeNums) {
        answer.insert(0, "-");
    }
    return answer;
}

