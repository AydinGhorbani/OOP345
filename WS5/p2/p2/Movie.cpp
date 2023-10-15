#include "Movie.h"

namespace sdds {
    Movie::Movie() : m_year(0) {}

    Movie::Movie(std::string& strMovie){

        std::istringstream iss(strMovie);
        std::string token;

        std::getline(iss, token, ',');
        m_title = trim(token);
        
        std::getline(iss, token, ',');
        m_year = stoi(trim(token));

        std::getline(iss, token);
        m_description = trim(token);

    }

    const std::string& Movie::title() const {
        return m_title;
    }

    std::string Movie::trim(std::string str) {
        std::string result = str.erase(0, str.find_first_not_of(" "));
        result = result.substr(0, result.find_last_not_of(" ") + 1);
        return result;
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
