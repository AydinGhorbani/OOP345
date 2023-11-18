/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Date       : 11/11/23
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include <iostream>
#include "Utilities.h"

namespace sdds {
    char Utilities::m_delimiter = '|';

    Utilities::Utilities() : m_widthField(1) {}

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string token;
        size_t delimiterPos = str.find(m_delimiter, next_pos);

        if (delimiterPos != std::string::npos) {
            token = str.substr(next_pos, delimiterPos - next_pos);
            next_pos = delimiterPos + 1;
        } else {
            token = str.substr(next_pos);
            next_pos = str.length();
        }
        m_widthField = std::max(token.length(), m_widthField);

        more = (next_pos < str.length());
        token = trim(token);
        
        if (token.empty() || token.find_first_not_of(' ') == std::string::npos) {
            more = false;
            throw std::string("ERROR: No token.");
        }


        return token;
    }

    std::string Utilities::trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
}
