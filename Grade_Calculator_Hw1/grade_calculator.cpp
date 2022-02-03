// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    // Variables for exam entries
    double examTotal = 0;
    int examCount    = 0;
    double examFinal = 0;
    int examFinalcount = 0;
    // Variables for hw entries
    double hwTotal = 0;
    int hwCount    = 0;
    // Variables for lw entries
    double lwTotal = 0;
    int lwCount =    0;
    // Variables for engagement entries
    double engagementTotalpercent = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
            examTotal += score;
            examCount += 1;
        } else if (category == "final-exam") {
            // TODO(student): process final score
            examFinal = score;
            examFinalcount += 1;
        } else if (category == "hw") {
            // TODO(student): process hw score
            hwTotal += score;
            hwCount += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            lwCount += 1;
            if (score) {
                lwTotal += 100;
            }
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            engagementTotalpercent += score;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    // Tests if any data has been inputted for exams and creates the average
    double exam_average = examTotal / examCount;
    if (examTotal == 0 && examFinal == 0) {
        exam_average = 0;
    } else if (exam_average < 60){ // Determines if the average should include a final or not
        if (examFinal > (examTotal + examFinal) / 4) {
            exam_average = examFinal;
        } else {
            exam_average = (examTotal + examFinal) / 4;
        }
    } else if (examFinalcount > 0 && examFinal > ((examTotal + examFinal) / (examCount + examFinalcount))) {
        exam_average = examFinal;
    } else {
        exam_average = (examTotal + examFinal) / (examCount + examFinalcount);
    }

    // Tests if any data has been inputted for hw and creates the average
    double hw_average = 0;
    if (hwTotal == 0) {
        hw_average = 0;
    } else {
       hw_average = hwTotal / hwCount;
    }
    // Tests if any data has been inputted for lw and creates the average
    double lw_average = 0;
    if (lwTotal == 0) {
        lw_average = 0;
    } else {
        lw_average = lwTotal / lwCount;
    }
    // Checks percentage then creates the total for engagement
    double engagement = 0;
    if (engagementTotalpercent > 100) {
        engagement = 100;
    } else {
        engagement = engagementTotalpercent;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = 0;
    weighted_total = (exam_average * .4) + (hw_average * .4) + (lw_average * .1) + (engagement * .1);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if (90 <= weighted_total && weighted_total <= 100) {
        final_letter_grade = 'A';
    } else if (80 <= weighted_total && weighted_total < 90) {
        final_letter_grade = 'B';
    } else if (70 <= weighted_total && weighted_total < 80) {
        final_letter_grade = 'C';
    } else if (60 <= weighted_total && weighted_total < 70) {
        final_letter_grade = 'D';
    } else {
        final_letter_grade = 'F';
    }

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
