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

#include "SpellChecker.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "Collection.h"

namespace sdds {
    class Book {
        std::string m_author;
        std::string m_title;
        std::string m_country;
        size_t m_year;

        std::string m_description;

    public:
        double m_price;
        Book();  // Default constructor
        Book(const std::string& strBook); // Constructor that extracts information from a string
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price() ;
        void setPrice(double price);
        std::string eraseSpaces(std::string& str);
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
        void fixSpelling( SpellChecker& spellChecker) const;
        
    };
}

#endif // SDDS_BOOK_H

