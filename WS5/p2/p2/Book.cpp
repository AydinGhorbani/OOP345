/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/

#include "Book.h"
#include <sstream>
using namespace std;

namespace sdds {

    Book::Book() {
        m_author = {};
        m_title = {};
        m_country = {};
        m_year = 0;
        m_price = 0.0;
        m_description = {}; 
    }

    const std::string& Book::title() const {
        return m_title;
    }

    const std::string& Book::country() const {
        return m_country;
    }

    const size_t& Book::year() const {
        return m_year;
    }

    double& Book::price() {
        return m_price;
    }

    std::string trim(std::string str) {
        std::string result = str.erase(0, str.find_first_not_of(" "));
        result = result.substr(0, result.find_last_not_of(" ") + 1);
        return result;
    }

    Book::Book(const std::string& strBook) {
        std::istringstream iss(strBook);
        std::string token;

        std::getline(iss, token, ',');
        m_author = trim(token);
        
        std::getline(iss, token, ',');
        m_title = trim(token);

        std::getline(iss, token, ',');
        m_country = trim(token);

        std::getline(iss, token, ',');
        m_price = stod(trim(token));

        std::getline(iss, token, ',');
        m_year = stoi(trim(token));

        std::getline(iss, token);
        m_description = trim(token);
    }


    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << std::right << book.m_author << " | ";
        os << std::setw(22) << std::right << book.title() << " | ";
        os << std::setw(5) << std::right << book.country() << " | ";
        os << std::setw(4) << book.year() << " | ";
        os << std::setw(6) << std::setprecision(2) << std::fixed << std::right << book.m_price << " | ";
        os << std::left << book.m_description << std::endl;

        return os;
    }

    void Book::setPrice(double price) {
        m_price = price;
    }

    void Book::fixSpelling(SpellChecker& spellChecker) const {
        // Call the SpellChecker operator() on the title and description
        spellChecker(const_cast<std::string&>(m_title));
        spellChecker(const_cast<std::string&>(m_description));
    }

}  // namespace sdds
