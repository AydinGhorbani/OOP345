#include "Movie.h"

namespace sdds {
    Movie::Movie() : m_year(0) {}

    Movie::Movie(std::string& strMovie){
        size_t start = 0;
        size_t end = strMovie.find(',');
        m_title = strMovie.substr(start, end - start);
        start = end + 1;
        end = strMovie.find(',', start);
        m_year = std::stoul(strMovie.substr(start, end - start));
        start = end + 1;
        m_description = strMovie.substr(start);
    }

    const std::string& Movie::title() const {
        return m_title;
    }

 
void Movie::fixSpelling(SpellChecker& spellChecker) const {
    // Call the SpellChecker operator() on the title and description
    spellChecker(const_cast<std::string&>(m_title));
    spellChecker(const_cast<std::string&>(m_description));
}

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::setw(40) << movie.m_title << " | ";
        os << std::setw(4) << movie.m_year << " | ";
        os << movie.m_description;
        return os;
    }
}
