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
#include <iostream>
#include <sstream>
#include <iomanip>

namespace sdds {
    Book::Book() : m_year(0), m_price(0.0) {
    }

    Book::Book(const std::string& strBook) {
        std::istringstream iss(strBook);
        std::string token;
        // Tokenize the input string and initialize the attributes
        getline(iss, token, ','); // AUTHOR
        m_author = token;
        getline(iss, token, ','); // TITLE
        m_title = token;
        getline(iss, token, ','); // COUNTRY
        m_country = token;
        getline(iss, token, ','); // PRICE
        m_price = std::stod(token);
        getline(iss, token, ','); // YEAR
        m_year = std::stoi(token);
        getline(iss, token, ','); // DESCRIPTION
        m_description = token;
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

    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << std::setw(20) << book.m_author << "|";
        os << std::setw(20) << book.m_title << "|";
        os << std::setw(5) << book.m_country << "|";
        os << std::setw(5) << book.m_year << "|";
        os << std::fixed << std::setprecision(2) << std::setw(6) << book.m_price << "|";
        os << book.m_description;
        return os;
    }
}
