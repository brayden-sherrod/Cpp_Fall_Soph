#include <iostream>
#include <fstream>
#include <string>
#include "taxi_trips.h"
using std::string, std::ifstream, std::cin, std::cout, std::endl;

int main() {
 string taxiIdVals[MAX_TRIPS];
 double timeVals[MAX_TRIPS];
 double distVals[MAX_TRIPS];
 double fareVals[MAX_TRIPS];
 double tipVals[MAX_TRIPS];
 string paymentVals[MAX_TRIPS];
  // TODO(student): implement
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    cout << "Can't open " << filename << endl;
    return 1;
  }
  string inputLine;
  int index = 0;
  int invalidNum = 0;
  while (!ifs.eof()) {
    bool valid = true;
    string taxiIDTemp, paymentTemp;
    double timeTemp, distTemp, fareTemp, tipTemp;
    ifs >> taxiIDTemp >> timeTemp >> distTemp >> fareTemp >> tipTemp >> paymentTemp;
    // Validate the incoming data before putting it in
    // cout << taxiIDTemp << " " << timeTemp << " " << distTemp << " " << fareTemp << " " << tipTemp << " " << paymentTemp << endl;          // TESTING STATEMENTS
    if (timeTemp > 86400) {
      valid = false;
    }
    if (distTemp > 1500) {
      valid = false;
    }
    if ((fareTemp + tipTemp) > 5000) {
      valid = false;
    }
    if (timeTemp == 0 && distTemp == 0 && fareTemp != 0) {
      valid = false;
    }
    if (paymentTemp != "CreditCard" && paymentTemp != "Cash" && paymentTemp != "NoCharge" && paymentTemp != "Unknown") {
      valid = false;
    }
    if (valid) {
      taxiIdVals[index] = taxiIDTemp;
      timeVals[index] = timeTemp;
      distVals[index] = distTemp;
      fareVals[index] = fareTemp;
      tipVals[index] = tipTemp;
      paymentVals[index] = paymentTemp;
      index++;
      // cout << "Is valid, there are " << index << " valid inputs now" << endl;                                                            // TESTING STATEMENTS
    } else {
      invalidNum++;
      // cout << "Invalid, there are " << invalidNum << " invalid inputs now" << endl;                                                      // TESTING STATEMENTS
     }
    

  }

  int numTrips = index;
  // Output results
  cout << "Number of trips: " << numTrips << endl;
  cout << "Number of trips with invalid data: " << invalidNum << endl;
  cout << "Duration: max " << max(timeVals, numTrips) << " min " << min(timeVals, numTrips) << " avg " << average(timeVals, numTrips) << " mode " << mode(timeVals, numTrips) << endl;
  cout << "Distance: max " << max(distVals, numTrips) << " min " << min(distVals, numTrips) << " avg " << average(distVals, numTrips) << " mode " << mode(distVals, numTrips) << endl;
  cout << "Fare: max " << max(fareVals, numTrips) << " min " << min(fareVals, numTrips) << " avg " << average(fareVals, numTrips) << " mode " << mode(fareVals, numTrips) << endl;
  cout << "Tip: max " << max(tipVals, numTrips) << " min " << min(tipVals, numTrips) << " avg " << average(tipVals, numTrips) << " mode " << mode(tipVals, numTrips) << endl;
  cout << "Length of longest sequence without tips: " << length_longest_seq_zeros(tipVals, numTrips) << endl;
  return 0;
}