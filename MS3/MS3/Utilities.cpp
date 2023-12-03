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
#include <string>
#include "Utilities.h"
#include "CustomerOrder.h"

namespace sdds {
    std::vector<CustomerOrder> g_pending;
    std::vector<CustomerOrder> g_completed;
    std::vector<CustomerOrder> g_incomplete;
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
    size_t delimiter_pos = str.find(m_delimiter, next_pos);

    if (delimiter_pos != std::string::npos) {
        token = str.substr(next_pos, delimiter_pos - next_pos);
        next_pos = delimiter_pos + 1;
    } else {
        token = str.substr(next_pos);
        more = false;
    }

    if (token.empty()) {
        throw std::out_of_range("Error: Empty token found.");
    }

    trim(token);
    return token;
}


std::string Utilities::trim(std::string& src)const {
    size_t first = src.find_first_not_of(" \t\n");
    if (first == std::string::npos) {
        src.clear();  // Clear the string if it only contains whitespace characters
    } else {
        size_t last = src.find_last_not_of(" \t\n");
        src = src.substr(first, last - first + 1);
        
    }
    return src;
}

    bool Utilities::checkTokenCount(const std::string& record, size_t expectedCount) {
        size_t count = 0;
        size_t pos = 0;
        bool more = true;

        while (more) {
            extractToken(record, pos, more);
            ++count;
        }

        return count == expectedCount;
    }
}
