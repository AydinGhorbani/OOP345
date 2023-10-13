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

#include <iostream>
#include <string>

namespace sdds {
    class Book {
    protected:
        std::string m_title{};
        unsigned m_numChapters{};
        unsigned m_numPages{};
    public:
        Book();
        Book(const std::string& title, unsigned nChapters, unsigned nPages);

        std::ostream& print(std::ostream& os) const;
        
        bool operator<(const Book& other) const {
            return m_numPages < other.m_numPages;
        }

        bool operator>(const Book& other) const {
            return m_numPages > other.m_numPages;
        }
    };
   
    std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif // SDDS_BOOK_H
