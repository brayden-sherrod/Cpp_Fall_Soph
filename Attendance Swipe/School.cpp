#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Student.h"
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;


// one method is provided to students; students implement all other methods
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

// check if student is enrolled by id
bool School::isEnrolled(std::string student_id) const {
  for (size_t index = 0; index < students.size(); index++) {
    if (student_id == students[index].get_id()) {
      return true;
    }
  }
  return false;
}

// list enrolled students
void School::listStudents(std::ostream& os) const {
  if (students.empty()) {
    os << "No students" << endl;
  } else {
    for (size_t index = 0; index < students.size(); index++) {
      os << students[index].get_id() << "," << students[index].get_name() << endl;
    }
  }
}

// Add course objects to school
void School::addCourses(std::string filename) {
  ifstream ifs;
  ifs.open(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("");
  }
  while (!ifs.eof()) {
    std::string line;
    getline(ifs, line);
    if (ifs.fail()) {
      break;
    }
    size_t npos = -1;
    while (line.find(' ') < 16 && line.find(' ') != npos) {
      size_t index = line.find(' ');
      line.replace(index, 1 , "");
    }
    istringstream ss(line);
    std::string course_id;
    getline(ss, course_id, ',');
    std::string timeInput;
    getline(ss, timeInput, ':');
    int startHour = stoi(timeInput);
    getline(ss, timeInput, ',');
    int startMin = stoi(timeInput);
    getline(ss, timeInput, ':');
    int endHour = stoi(timeInput);
    getline(ss, timeInput, ',');
    int endMin = stoi(timeInput);
    std::string title;
    getline(ss, title);
    Date startTime(startHour, startMin, 0);
    Date endTime(endHour, endMin, 0);
    Course tempCourse(course_id, title, startTime, endTime);
    courses.push_back(tempCourse);
  }
  ifs.close();
}

// List courses
void School::listCourses(std::ostream& os) const {
  if (courses.empty()) {
    os << "No courses" << endl;
  } else {
    for (size_t index = 0; index < courses.size(); index++) {
      Course tempCourse = courses[index];
      os << tempCourse.getID() << "," << tempCourse.getStartTime().getTime(false) << "," << tempCourse.getEndTime().getTime(false) << "," << tempCourse.getTitle() << endl;
    }
  }
}

// Add Attendance Data
unsigned int School::addAttendanceData(std::string filename) {
  ifstream ifs;
  ifs.open(filename);
  unsigned int invalidCount = 0;
  while (!ifs.eof()) {
    std::string input;
    getline(ifs, input);
    if (ifs.fail()){
      break;
    }
    int year = stoi(input.substr(0,4));
    int month = stoi(input.substr(5,2));
    int day = stoi(input.substr(8,2));
    int hour = stoi(input.substr(11,2));
    int min = stoi(input.substr(14,2));
    int sec = stoi(input.substr(17,2));
    std::string courseID = input.substr(20,3);
    std::string studentID = input.substr(24,9);
    // Search for course ID
    bool foundID = false;
    for (size_t index = 0; index < courses.size(); index++) {
      if (courseID == courses[index].getID()) {
        foundID = true;
      }
    }
    // Search for student ID
    bool foundStudent = false;
    for (size_t index = 0; index < students.size(); index++) {
      if (studentID == students[index].get_id()) {
        foundStudent = true;
      }
    }
    // Test Validity of date
    bool dateIsValid = false;
    Date test(year, month, day, hour, min, sec);
    dateIsValid = test.isValid();
    // Increments invalid count if any invalid
    if (foundID == false || foundStudent == false  || dateIsValid == false) {
      invalidCount++;
    } else {
      for (size_t index = 0; index < courses.size(); index++) {
        if (courseID == courses[index].getID()) {
          AttendanceRecord insert(courseID, studentID, test);
          courses[index].addAttendanceRecord(insert);
        }
      }
    }
  }
  ifs.close();
  return invalidCount;
}

// Output attendance based on course
void School::outputCourseAttendance(std::ostream& os, std::string course_id) const {
  bool foundCourse = false;
  for (size_t index = 0; index < courses.size(); index++) {
    if (course_id == courses[index].getID()) {
      foundCourse = true;
      Course temp = courses[index];
      temp.outputAttendance(os);
    }
  }
  if (!foundCourse) {
    throw std::invalid_argument("Couldn't Find Course");
  }
}

// Output attendance for a specific student
void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const {
  bool foundStudent = false;
  for (size_t index = 0; index < students.size(); index++) {
    if (student_id == students[index].get_id()) {
      foundStudent = true;
    }
  }
  if (!foundStudent) {
    throw std::invalid_argument("Didn't Find Student");
  }
  bool foundCourse = false;
  for (size_t index = 0; index < courses.size(); index++) {
    if (course_id == courses[index].getID()) {
      foundCourse = true;
      Course temp = courses[index];
      temp.outputAttendance(os, student_id);
    }
  }
  if (!foundCourse) {
    throw std::invalid_argument("Didn't Find Course");
  }
}
