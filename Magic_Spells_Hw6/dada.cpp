/*
DADA function definitions
*/

#include <iostream>
#include <cmath>
#include "dada.h"
using std::cout, std::endl, std::abs, std::sqrt;

int amax(const double x[], const unsigned int len) {
    //TODO: student implement code here
    if (len == 0) {
        return -1;
    }
    double max = x[0];
    int index = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (abs(x[i]) > max) {
            max = abs(x[i]);
            index = i;
        }
    }
    return index;
}

double asum(const double x[], const unsigned int len) {
    //TODO: student implement code here
    double sum = 0.0;
    for (unsigned int i = 0; i < len; i++) {
        sum += abs(x[i]);
    }
    return sum;
}

void axpy(const double a, const double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    for (unsigned int i = 0; i < len; i++) {
        y[i] = a * x[i] + y[i];
    }
}

void copy(const double src[], double dest[], const unsigned int len) {
    //TODO: student implement code here
    for (unsigned int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

double dot(const double x[], const double y[], const unsigned int len) {
    //TODO: student implement code here
    double dot = 0.0;
    for (unsigned int i = 0; i < len; i++) {
        dot += x[i] * y[i];
    }
    return dot;
}

double norm2(const double x[], const unsigned int len) {
    //TODO: student implement code here
    double squaredSum = 0.0;
    for (unsigned int i = 0; i < len; i++) {
        squaredSum += x[i] * x[i];
    }
    return sqrt(squaredSum);
}

void scale(const double a, double x[], const unsigned int len) {
    //TODO: student implement code here
    for (unsigned int i = 0; i < len; i++) {
        x[i] = x[i] * a;
    }
}

void swap(double x[], double y[], const unsigned int len) {
    //TODO: student implement code here
    for (unsigned int i = 0; i < len; i++) {
        double tempVal = x[i];
        x[i] = y[i];
        y[i] = tempVal;
    }
}