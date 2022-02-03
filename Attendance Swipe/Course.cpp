#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;


// Constructor
Course::Course(std::string id, std::string title, Date startTime, Date endTime) : id(id), title(title), 
startTime(startTime), endTime(endTime) {}

//Getters
std::string Course::getID() const {return id;}
std::string Course::getTitle() const {return title;}
Date Course::getStartTime() const {return startTime;}
Date Course::getEndTime() const {return endTime;}

// Add Attendance Record and check validity
void Course::addAttendanceRecord(AttendanceRecord ar) {
    Date time(ar.getDate().getHour(), ar.getDate().getMin(), ar.getDate().getSec());
    if (startTime <= time && time <= endTime) {
        attendanceRecords.push_back(ar);
    } else {
        throw std::invalid_argument("Didn't Add Attendance Records");
    }
}

// Output Attendance without specified student
void Course::outputAttendance(std::ostream& os) const {
    if (attendanceRecords.empty()) {
        os << "No records" << endl;
    } else {
        for (size_t index = 0; index < attendanceRecords.size(); index++) {
            AttendanceRecord temp = attendanceRecords[index];
            os << temp.getDate().getDateTime() << "," << temp.getCourseID() << "," << temp.getStudentID() << endl;
        }
    }
}

// Output Attendance for specific student
void Course::outputAttendance(std::ostream& os, std::string student_id) const {
    if (attendanceRecords.empty()) {
        os << "No records" << endl;
    } else {
        int count = 0;
        for (size_t index = 0; index < attendanceRecords.size(); index++) {
            if (attendanceRecords[index].getStudentID() == student_id) {
                AttendanceRecord temp = attendanceRecords[index];
                os << temp.getDate().getDateTime() << "," << temp.getCourseID() << "," << temp.getStudentID() << endl;
                count++;
            }
        }
        if (count == 0) {
            os << "No records" << endl;
        }
    }
}
