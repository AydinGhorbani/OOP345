//
//  Utilities.cpp
//  MS1
//
//  Created by aydin ghorbani on 2023-11-08.
//

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
    if (next_pos < str.length()) {
        size_t delimiterPos = str.find(m_delimiter, next_pos);
        if (delimiterPos != std::string::npos) {
            token = str.substr(next_pos, delimiterPos - next_pos);
            next_pos = delimiterPos + 1;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
        }
        // Trim leading and trailing spaces
        while (!token.empty() && token[0] == ' ')
            token.erase(0, 1);
        while (!token.empty() && token[token.length() - 1] == ' ')
            token.erase(token.length() - 1, 1);
        if (!token.empty() && m_widthField < token.length())
            m_widthField = token.length();
    }
    else {
        more = false;
    }
    return token;
}

}
