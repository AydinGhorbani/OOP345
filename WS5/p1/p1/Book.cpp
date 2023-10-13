/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */

#include "Book.h"


namespace sdds {

    Book::Book() : m_year(0), m_price(0.0) {}

    Book::Book(const std::string& strBook) : m_year(0), m_price(0.0) {
        size_t next_pos = 0;
        size_t current_pos = 0;
        for (int i = 0; i < 6; i++) {
            next_pos = strBook.find(',', current_pos);
            std::string token = strBook.substr(current_pos, next_pos - current_pos);
            switch (i) {
                case 0:
                    m_author = token;
                    break;
                case 1:
                    m_title = token;
                    break;
                case 2:
                    m_country = token;
                    break;
                case 3:
                    m_price = std::stod(token);
                    break;
                case 4:
                    m_year = std::stoi(token);
                    break;
                case 5:
                    m_description = token;
                    break;
            }
            current_pos = next_pos + 1;
        }
    }

    // Queries
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

    // Friend helper to overload the insertion operator
    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << book.m_author << "| ";
        os << std::setw(22) << book.m_title << "| ";
        os <<std::setw(5) << book.m_country << "| ";
        os << std::setw(4) << book.m_year << "| ";
        return os;
    }
}
