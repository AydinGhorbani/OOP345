/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Repository : https://github.com/AydinGhorbani/OOP345/
 
 plaese find every commit (Over 50 thought the semester) has been made in this link, icluding the debugging techniques used to develop this project.
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
namespace sdds {

    class Station {
        int m_id = 0;
        string m_name;
        string m_desc;
        size_t m_nextSerialNum = 0;
        size_t m_numInStock = 0;
        inline static size_t m_widthField = 0;
        inline static int id_generator = 0;

    public:
        Station(const string& record);
        const string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(ostream& os, bool full) const;
    };

}

#endif
