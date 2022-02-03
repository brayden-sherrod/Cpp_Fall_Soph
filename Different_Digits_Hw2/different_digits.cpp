#include <iostream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl;

// call this function to reset cin to a good state
void reset_cin();

int main() {
    int a = 0;
    int b = 0;
    bool valid;
    int count = 0;
    // TODO(student): print prompt for input
    cout << "Enter numbers 0 < a <= b <= 10000: ";

    // TODO(student): read the numbers from standard input
    cin >> a >> b;

    // TODO(student): validate input (and reprompt on invalid input)
    valid = is_valid_range(a, b);
    while (!valid)
    {
        cout << "Invalid input" << endl << "Enter numbers 0 < a <= b <= 10000: ";
        reset_cin();
        cin >> a >> b;
        valid = is_valid_range(a ,b);
    }
    // TODO(student): compute and display solution
    count = count_valid_numbers(a, b);
    cout << "There are " << count << " valid numbers between " << a << " and " << b << endl;
    return 0;
}

void reset_cin() {
    // clear the stream state flags
    cin.clear();
    // clear the stream buffer up to the first newline character
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
