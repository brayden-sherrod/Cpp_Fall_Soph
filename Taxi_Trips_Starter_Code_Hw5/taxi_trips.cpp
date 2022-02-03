#include <stdexcept>
#include <string>
using std::string;
#include "taxi_trips.h"


bool is_payment_valid(string type, string valid_types[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  for (size_t index = 0; index < size; index++) {
    if (valid_types[index] == type) {
      return true;
    }
  }
  return false;
}

double max(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  double maxVal = values[0];
  for (size_t index = 0; index < size; index++) {
    if (values[index] > maxVal) {
      maxVal = values[index];
    }
  }
  return maxVal;
}

double min(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  double minVal = values[0];
  for (size_t index = 0; index < size; index++) {
    if (values[index] < minVal) {
      minVal = values[index];
    }
  }
  return minVal;
}

double average(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  double valSum = 0;
  for (size_t index = 0; index < size; index++) {
    valSum += values[index];
  }
  return valSum / size;
}

double mode(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  double maxCountNum = values[0];
  int maxCount = 0;
  for (size_t index1 = 0; index1 < size; index1++) {
    int count = 0;
    double countNum = values[index1];
    for (size_t index2 = 0; index2 < size; index2++) {
      if (countNum == values[index2]) {
        count++;
      }
    }
    if (count > maxCount) {
      maxCount = count;
      maxCountNum = countNum;
    }
  }
  return maxCountNum;
}

unsigned int length_longest_seq_zeros(double values[], unsigned int size) {
  // TODO(student): implement
  if (size == 0) {
    throw std::invalid_argument("");
  }
  int maxZeroCount = 0;
  int zeroCount = 0;
  for (size_t index = 0; index < size; index++) {
    if (values[index] == 0) {
      zeroCount++;
    } else if (values[index] != 0) {
      zeroCount = 0;
    }
    if (zeroCount > maxZeroCount) {
      maxZeroCount = zeroCount;
    }
  }
  return maxZeroCount;
}