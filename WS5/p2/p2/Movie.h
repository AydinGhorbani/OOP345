/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "SpellChecker.h"
#include "Collection.h"

namespace sdds {
    class Movie {
        std::string m_title;
        size_t m_year;
        std::string m_description;

    public:
        Movie();
        Movie(std::string& strMovie);
        const std::string& title() const;
        void fixSpelling(SpellChecker& spellChecker) const ;
        std::string trim(std::string str);
        std::string getDescription() const {
            return m_description;
        }

        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };
}
#endif
