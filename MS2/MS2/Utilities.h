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

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
    class Utilities {
        size_t m_widthField ;
        static char m_delimiter ;
        // private methode to trim the find_first_of spaces
        // in Stations2.
        std::string trim(const std::string& str);
    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    };
}

#endif /*SDDS_UTILITIES_H*/
