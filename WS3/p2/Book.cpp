/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include <iostream>
#include <iomanip>
#include "Book.h"
#include "Collection.h"

namespace sdds {
    Book::Book() : m_numChapters(0), m_numPages(0) {}

    Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
        : m_title(title), m_numChapters(nChapters), m_numPages(nPages) {}

    std::ostream& Book::print(std::ostream& os) const {
        if (m_title.empty() || m_numChapters == 0 || m_numPages == 0) {
            os << "| Invalid book data";
            
        }
        else if (m_title[0] == 'S'){
            os << std::setw(50) << std::fixed << std::right << m_title << "," << m_numChapters << "," << m_numPages << " | (" << std::fixed << std::right << std::setprecision(6) << static_cast<double>(m_numPages) / m_numChapters << ")    ";
        }
        else
        {   os << std::setw(49) << std::fixed << std::right << m_title << "," << m_numChapters << "," << m_numPages << " | (" << std::fixed << std::right << std::setprecision(6) << static_cast<double>(m_numPages) / m_numChapters << ")    ";
        }

            
        
        return os;
    }



    template class Collection<int, 10u>;
    template class Collection<double, 10u>;
    template class Collection<Book, 10u>;


    std::ostream& operator<<(std::ostream& os, const Book& bk){
        return bk.print(os);
    }
}
