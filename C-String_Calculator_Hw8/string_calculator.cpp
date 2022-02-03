// string_calculator.cpp
#include <iostream>
#include "my_string.h"
#include "./string_calculator.h"

using std::cout, std::endl;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): put your existing implementation here
    int decimal = digit;
    decimal -= 48;
    if (decimal < 0 || decimal > 9) {
        throw std::invalid_argument("");
    } else {
        return decimal;
    }
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): put your existing implementation here
    char digit = decimal + 48;
    if (digit < 48 || digit > 57) {
        throw std::invalid_argument("");
    } else {
        return digit;
    }
}

my_string trim_leading_zeros(const my_string& numConst) {
    // TODO(student): put your existing implementation here
    my_string num = numConst;
    bool neg = false;
    if (num[0] == '-') {
        num.remove(0);
        neg = true;
    }
    int index = num.find('0');
    while (index == 0) {
        if (num.size() == 1) {
            break;
        }
            num.remove(index);
            index = num.find('0');
        }
    if (neg && num[0] != '0') {
        num.insert(0, '-');
    }
    return num;
}

my_string add(const my_string& lhsConst, const my_string& rhsConst) {
    // TODO(student): put your existing implementation here
    my_string lhs = lhsConst;
    my_string rhs = rhsConst;
    my_string answer;
    my_string greater;
    my_string lesser;
    bool addOne = false;
    bool negativeNums = false;
    if (lhs[0] == '-' && rhs[0] != '-') {
        lhs.remove(0);
        answer = subtract(lhs, rhs);
        if (answer.at(0) != '0') {
            answer.insert(0, '-');
        }
        if (answer.at(0) == '-' && answer.at(1) == '-') {
            answer.remove(0);
            answer.remove(0);
        }
        return answer;
    } else if (lhs[0] != '-' && rhs[0] =='-') {
        rhs.remove(0);
        answer = subtract(lhs,rhs);
        return answer;
    }
    if (lhs[0] == '-') {
        lhs.remove(0);
        rhs.remove(0);
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
    my_string carryOver;
    carryOver.resize(greater.size());
    while (!greater.empty()) {
        int lastIndexG = greater.size() - 1;
        // Create Decimals and add
        int decmialCarryOver = digit_to_decimal(carryOver.at(lastIndexG));
        int decimalG = digit_to_decimal(greater.at(lastIndexG));
        carryOver.remove(lastIndexG);
        greater.remove(lastIndexG);
        int lastIndexL = 0;
        int decimalL = 0;
        if (!lesser.empty()) {
            lastIndexL = lesser.size() - 1;
            decimalL = digit_to_decimal(lesser.at(lastIndexL));
            lesser.remove(lastIndexL);
        }
        int newDecimal = decimalG + decimalL + decmialCarryOver;
        if (newDecimal >= 10) {
            newDecimal %= 10;
            if (lastIndexG == 0 && lastIndexL == 0) {
                addOne = true;
            } else {
                carryOver.replace(lastIndexG - 1, '1');
            }
        }
        char newChar = decimal_to_digit(newDecimal);
        answer = newChar + answer;
    }
    if (addOne) {
        answer.insert(0, '1');
        addOne = false;
    }
    if (negativeNums) {
        answer.insert(0, '-');
    }
    return answer;
}

my_string subtract(const my_string& lhsConst, const my_string& rhsConst) {
    // TODO(student): put your existing implementation here
    my_string lhs = lhsConst;
    my_string rhs = rhsConst;
    my_string answer;
    my_string greater;
    my_string lesser;
    bool addOne = false;
    bool negativeNums = false;
    if (lhs[0] == '-' && rhs[0] != '-') {
        lhs.remove(0);
        answer = subtract(lhs, rhs);
        if (answer.at(0) != '0') {
            answer.insert(0, '-');
        }
        if (answer.at(0) == '-' && answer.at(1) == '-') {
            answer.remove(0);
            answer.remove(0);
        }
        return answer;
    } else if (lhs[0] != '-' && rhs[0] =='-') {
        rhs.remove(0);
        answer = subtract(lhs,rhs);
        return answer;
    }
    if (lhs[0] == '-') {
        lhs.remove(0);
        rhs.remove(0);
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
    my_string carryOver;
    carryOver.resize(greater.size());
    while (!greater.empty()) {
        int lastIndexG = greater.size() - 1;
        // Create Decimals and add
        int decmialCarryOver = digit_to_decimal(carryOver.at(lastIndexG));
        int decimalG = digit_to_decimal(greater.at(lastIndexG));
        carryOver.remove(lastIndexG);
        greater.remove(lastIndexG);
        int lastIndexL = 0;
        int decimalL = 0;
        if (!lesser.empty()) {
            lastIndexL = lesser.size() - 1;
            decimalL = digit_to_decimal(lesser.at(lastIndexL));
            lesser.remove(lastIndexL);
        }
        int newDecimal = decimalG + decimalL + decmialCarryOver;
        if (newDecimal >= 10) {
            newDecimal %= 10;
            if (lastIndexG == 0 && lastIndexL == 0) {
                addOne = true;
            } else {
                carryOver.replace(lastIndexG - 1, '1');
            }
        }
        char newChar = decimal_to_digit(newDecimal);
        answer = newChar + answer;
    }
    if (addOne) {
        answer.insert(0, '1');
        addOne = false;
    }
    if (negativeNums) {
        answer.insert(0, '-');
    }
    return answer;
}

my_string multiply(const my_string& lhsConst, const my_string& rhsConst) {
    // TODO(student): put your existing implementation here
    my_string lhs = lhsConst;
    my_string rhs = rhsConst;
    my_string answer;
    my_string greater;
    my_string lesser;
    bool negativeNums = false;
    if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        lhs.remove(0);
        rhs.remove(0);
    } else if (lhs.at(0) == '-') {
        lhs.remove(0);
        negativeNums = true;
    } else if (rhs.at(0) == '-') {
        rhs.remove(0);
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
    my_string carryOver;
    carryOver.resize(greater.size());
    int zeroAdjustCount = 0;
    while (!lesser.empty()) {
        bool insertExtra = false;
        my_string newSum;
        int lastIndexG = greater.size() - 1;
        int lastIndexL = lesser.size() - 1;
        int decimalL = digit_to_decimal(lesser.at(lastIndexL));
        // Loop through all of the digits in greater
        for (int i =0; i <= lastIndexG; i++) {
            // Continues to iterate through each of the digits in the shorter number
            int decmialCarryOver = digit_to_decimal(carryOver.at(lastIndexG - i));
            carryOver.replace(lastIndexG - i, '0');
            int decimalG = digit_to_decimal(greater.at(lastIndexG - i));
            int newDecimal = (decimalG * decimalL) + decmialCarryOver;
            char carryOverDigit ='0';
            // Handles the case where the digit would be greater than 10
            if (newDecimal >= 10) {
                int carryOverDecimal =  (newDecimal / 10) % 10;
                newDecimal %= 10;
                carryOverDigit = decimal_to_digit(carryOverDecimal);
                if (i + 1 <= lastIndexG) {
                    carryOver.replace(lastIndexG - i - 1, carryOverDigit);
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
            newSum.insert(newSum.size(), '0');
        }
        answer = add(answer, newSum);
        lesser.remove(lastIndexL);
        zeroAdjustCount ++;
    }
    // Adds the negative sign if the two numbers had opposing signs
    if (negativeNums) {
        answer.insert(0, '-');
    }
    return answer;
}