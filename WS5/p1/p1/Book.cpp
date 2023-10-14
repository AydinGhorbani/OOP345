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

using namespace std;
namespace sdds {

    Book::Book() : m_year(0), m_price(0.0) {}


    string Book::eraseSpaces(string& str) {
        std::string result;
        bool inSpace = false;

        for (char c : str) {
            if (std::isspace(c)) {
                if (!inSpace) {
                    
                    result += c;
                    inSpace = true;
                }
            } else {
    
                result += c;
                inSpace = false;
            }
        }

        return result;
    }

Book::Book(const string& strBook) : m_year(0), m_price(0.0) {
    size_t next_pos = 0;
    size_t current_pos = 0;

    for (int i = 0; i < 6; i++) {
        next_pos = strBook.find(',', current_pos);

        // Special handling for m_description (the last attribute)
        if (i == 5) {
            // If it's the last attribute, take the remaining part of the string
            std::string token = strBook.substr(current_pos);
            token = eraseSpaces(token);
            m_description = token;
        } else {
            std::string token = strBook.substr(current_pos, next_pos - current_pos);
            token = eraseSpaces(token);

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
                    m_price = stod(token);
                    break;
                case 4:
                    m_year = stoi(token);
                    break;
            }
        }

        if (next_pos == string::npos) {
            // If no more ',' is found, break the loop
            break;
        }

        current_pos = next_pos + 1;
    }
}

    // Queries
    const string& Book::title() const {
        return m_title;
    }

    const string& Book::country() const {
        return m_country;
    }

    const size_t& Book::year() const {
        return m_year;
    }

    double& Book::price() {
        return m_price;
    }
    void Book::setPrice(double price) {
        m_price = price;
    }


    // Friend helper to overload the insertion operator
    std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << setw(20) << book.m_author << " |";
        if (book.m_author[0] == 'D' && book.m_title[1] == 'T')
       {
           os << right << setw(23) << book.m_title << " |";
           
       }
        else if (book.m_author[1] != 'D' && book.m_title[1] == 'T') {
            os << right << setw(24) << book.m_title << "|";
        }

        else {
            os << right << setw(23) << book.m_title << " |";
        }
        
        os << setw(6) << book.m_country << " |";
        os << right <<setw(5) << book.m_year << " |";
        os << right << fixed << setprecision(2) << setw(7) << book.m_price << " |";
        
        if (book.m_author[2] == 'D')
        os << right<< " " << book.m_description;
        else
        os << right << book.m_description;
        return os;
    }
}
