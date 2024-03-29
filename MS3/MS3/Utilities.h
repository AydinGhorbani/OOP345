/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Repository : https://github.com/AydinGhorbani/OOP345/
 
 plaese find every commit (Over 50 thought the semester) has been made in this link, icluding the debugging techniques used to develop this project.
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

namespace sdds {
    class Utilities {
        size_t m_widthField = 1;
        static inline char m_delimiter = ',';
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        string extractToken(const string& str, size_t& next_pos, bool& more);
        //MS3 update
        bool checkTokenCount(const std::string& record, size_t expectedCount) ;
        std::string toLower(const std::string& str) const;
    };
    std::string trim(const std::string& str);

}

#endif 
