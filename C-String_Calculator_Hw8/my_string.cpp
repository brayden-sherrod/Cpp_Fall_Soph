// my_string.cpp
#include <iostream>
#include "my_string.h"
#include "my_sstream.h"

// TODO(student): define all necessary my_string methods
// NOTE: some methods suggested here may not be required for you.
//       if you don't need a method, then you are not required to implement it
// NOTE: some methods not suggested here may be required for you.
//       if you need a method, then you are required to implement it (or re-engineer your solution to no longer need the method).

// my_string methods

// constructors
//   default (done for you.  you're welcome.)
my_string::my_string() : _data(new char[1]{0}), _capacity(1), _size(0) {}
//   rule of "3"
//     my_string copy constructor
my_string::my_string(const my_string& other) {
    _capacity = other._capacity;
    _size = other._size;
    _data = new char[_size];
    for (size_t index = 0; index < _size; index++){
        _data[index] = other._data[index];
    }
}
//     my_string copy assignment
my_string& my_string::operator=(const my_string& rhs) {
    if (this != &rhs) {
        _capacity = rhs._capacity;
        _size = rhs._size;
        delete[] _data;
        _data = new char[_size];
        for (size_t index = 0; index < _size; index++){
            _data[index] = rhs._data[index];
        }
    }
    return *this;
}
//     destructor
my_string::~my_string() { 
    delete[] _data;
}
//   c-string copy constructor
my_string::my_string(const char* other) {
   size_t index = 0;
   while (other[index] != '\0') {
       index++;
   }
   _size = index + 1;
   _data = new char[_size];
   for (size_t index = 0; index < _size; index++) {
       _data[index] = other[index];
   }
   _capacity = _size;
}
// element access
//   at
const char& my_string::at(size_type index) const {
    return _data[index];
}
char& my_string::at(size_type index) {
    return _data[index];
}
//   front
const char& my_string::front() const {
    return _data[0];
}
char& my_string::front() {
    return _data[0];
}
//   operator[]
const char& my_string::operator[](size_type index) const {
    return _data[index];
}
char& my_string::operator[](size_type index) {
    return _data[index];
}
// capacity
//   empty
bool my_string::empty() const {
    if (_size == 0) {
        return true;
    } else {
        return false;
    }
}
//   size
my_string::size_type my_string::size() const {
    return _size;
}

// operations
// resize ################################################
void my_string::resize(size_t capacity) {
    char* tempPointer = new char[capacity];
    for (size_t index = 0; index < _size; index++) {
        tempPointer[index] = _data[index];
    }
    delete[] _data;
    _data = tempPointer;
    _capacity = capacity;
}
// insert
void my_string::insert(size_t inputIndex, char element) {
    char* tempChar = new char[_capacity +1];
    for (size_t index = 0; index < _size + 1; index++) {
        if (index < inputIndex) {
            tempChar[index] = _data[index];
        } else {
            tempChar[index + 1] = _data[index];
        }
         
    }
    tempChar[inputIndex] = element;
    delete[] _data;
    _data = tempChar;
    _size++;
    _capacity++;
}
 // replace
 void my_string::replace(size_t replaceIndex, char element) {
    _data[replaceIndex] = element;
 }
// remove
void my_string::remove(size_t removeIndex){
    char* tempChar = new char[_capacity];
    for (size_t index = 0; index < removeIndex; index++) {
        tempChar[index] = _data[index];
    }
    for (size_t index = removeIndex; index < _size-1; index++) {
        tempChar[index] = _data[index+1];
    }
    delete[] _data;
    _data = tempChar;
    _size--;
}
// #######################################################
//   concatenation
//     my_string + my_string (non-member, friend)
my_string operator+(my_string lhs, const my_string& rhs) {
    lhs.resize(lhs._capacity + rhs._capacity);
    for (size_t index = 0; index < rhs._size; index++) {
        lhs._data[index + lhs._size] = rhs._data[index];
    }
    return lhs;
}
//     my_string + c-string (non-member, friend)
my_string operator+(my_string lhs, const char* rhs) {
    size_t index = 0;
    while (rhs[index] != '\0') {
        if (lhs._size == lhs._capacity) {
            lhs.resize(lhs._capacity*2);
        }
        lhs._data[index+lhs._size] = rhs[index];
        index++;
    }
    return lhs;
}
//     my_string + char (non-member, friend)
my_string operator+(my_string lhs, char rhs) {
    if (lhs._size == lhs._capacity) {
        lhs.resize(lhs._size+1);
    }
    lhs._data[lhs._size+1] = rhs;
    return lhs;
}
//     c-string + my_string (non-member, friend)
my_string operator+(const char* lhs, const my_string& rhs) {
    my_string tempVal;
    size_t index = 0;
    while (lhs[index] != '\0') {
        if (tempVal._size == tempVal._capacity) {
            tempVal.resize(tempVal._capacity*2);
        }
        tempVal._data[index] = lhs[index];
        index++;
    }
    size_t firstSize = tempVal._size;
    tempVal.resize(tempVal._capacity + rhs._capacity);
    for (size_t index = 0; index < rhs._size; index++) {
        tempVal._data[index + firstSize] = rhs._data[index];
    }
    return tempVal;
}
//     char + my_string (non-member, friend)
my_string operator+(char lhs, my_string rhs) {
    rhs.insert(0, lhs);
    return rhs;
}
//     my_string += my_string
my_string& my_string::operator+=(const my_string& rhs) {
    *this = *this + rhs;
    return *this;
}
//     my_string += c-string
my_string& my_string::operator+=(const char* rhs) {
    *this = *this + rhs;
    return *this;
}
//     my_string += char
my_string& my_string::operator+=(char rhs) {
    *this = *this + rhs;
    return *this;
}

// search
//   find
my_string::size_type my_string::find(char value) {
    for (size_t index = 0; index < _size; index++) {
        if (_data[index] == value) {
            return index;
        }
    }
    return npos;
}

// non-member functions
//   relational operators
//     my_string == my_string
bool operator==(const my_string& lhs, const my_string& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t index = 0; index < lhs.size(); index++) {
        if (lhs.at(index) != rhs.at(index)) {
            return false;
        }
    }
    return true;
}
//     my_string == c-string
bool operator==(const my_string& lhs, const char* rhs) {
    if (rhs[lhs.size()] != '\0') {
        return false;
    }
    for (size_t index = 0; index < lhs.size(); index++) {
        if (lhs.at(index) != rhs[index]) {
            return false;
        }
        
    }
    return true;
}
//   stream operators
//     ostream instertion operator
//     istream extraction operator
//     getline
//   numeric conversions
//     to_string


// my_istringstream methods

my_istringstream::my_istringstream(const my_string& str) : _str(str), idx(0), state_fail(false), state_eof(str.empty()) {}

void my_istringstream::eat_whitespaces() {
    while (idx < _str.size() && isspace(_str[idx])) {
        idx++;
    }
}

my_istringstream& my_istringstream::operator>>(my_string& str) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    my_string s;
    while (idx < _str.size() && !isspace(_str[idx])) {
        s += _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    str = s;
    return *this;
}

my_istringstream& my_istringstream::operator>>(char& c) {
    eat_whitespaces();
    if (eof()) {
        state_fail = true;
    }
    if (fail()) {
        return *this;
    }
    if (idx < _str.size()) {
        c = _str[idx++];
    }
    if (idx == _str.size()) {
        state_eof = true;
    }
    return *this;
}

bool my_istringstream::good() const { return !(state_fail || state_eof); }
bool my_istringstream::fail() const { return state_fail; }
bool my_istringstream::eof() const { return state_eof; }

// TODO(student): define other my_istringstream methods, if any
