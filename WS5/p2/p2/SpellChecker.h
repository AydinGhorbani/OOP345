/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/

#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <string>
#include "Collection.h"

namespace sdds {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
    public:
 
        SpellChecker(const char* filename);
        void operator()(std::string& text)const;
        void showStatistics(std::ostream& os) const;
    };
}

#endif 
