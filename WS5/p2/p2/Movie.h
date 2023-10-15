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
        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };
}
#endif
