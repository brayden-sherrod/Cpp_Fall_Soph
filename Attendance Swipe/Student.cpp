#include <iostream>
#include <string>
#include "Student.h"

using std::cout, std::endl;


// constructor
Student::Student(std::string student_id, std::string student_name) {
    id = student_id;
    name = student_name;
}

// Getters
// Id
std::string Student::get_id() const {
    return id;
}
// Name
std::string Student::get_name() const {
    return name;
}

// Add course id
void Student::addCourse(std::string course_id) {
    for (size_t index = 0; index < course_ids.size(); index++) {
        if (course_ids[index] == course_id) {
            throw std::invalid_argument("");
        }
    }
    // adding id
    course_ids.push_back(course_id);
}

// List courses
void Student::listCourses(std::ostream& os) const {
    os << "Courses for " << id << endl;
    if (course_ids.size() == 0) {
        os << "No courses" << endl;
    }
    for (size_t index = 0; index < course_ids.size(); index++) {
    os << course_ids[index] << endl;
    }
}
