/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <string>
#include <iostream>
#include <iomanip>

namespace sdds {
    class Book {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;
        double m_price;
        std::string m_description;

    public:
        Book();  // Default constructor
        Book(const std::string& strBook); // Constructor that extracts information from a string
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };
}

#endif // SDDS_BOOK_H
