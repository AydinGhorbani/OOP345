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
#include <iostream>
#include <algorithm>
#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds {

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more){
        if (str.at(next_pos) == m_delimiter) {
            more = false;
        }

        size_t index = str.find_first_of(m_delimiter, next_pos);
        std::string substring = str.substr(next_pos, index - next_pos);
        more = index != str.npos;
        next_pos = index + 1;

        substring.erase(0, substring.find_first_not_of(' '));

        if (m_widthField < substring.length())
            m_widthField = substring.length();
        
        return substring;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
    std::string trim(const std::string& str) {
        const auto strBegin = str.find_first_not_of(' ');
        if (strBegin == std::string::npos)
            return "";
        const auto strEnd = str.find_last_not_of(' ');
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

}
