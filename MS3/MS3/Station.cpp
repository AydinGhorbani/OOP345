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
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {

    // I got help for this part
    Station::Station(const string& record) {
        Utilities utils;
        size_t next_pos = 0;
        bool more = true;
        m_id = ++id_generator;

        m_name = utils.extractToken(record, next_pos, more);
        m_nextSerialNum = more ? stoi(utils.extractToken(record, next_pos, more)) : 0;
        m_numInStock = more ? stoi(utils.extractToken(record, next_pos, more)) : 0;
        m_widthField = std::max(m_widthField, utils.getFieldWidth());
        m_desc = more ? utils.extractToken(record, next_pos, more) : "";
        m_name = trim(m_name);
    }

    const string& Station::getItemName() const {
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_nextSerialNum++;
    }

    size_t Station::getQuantity() const {
        return m_numInStock;
    }

    void Station::updateQuantity() {
        if (m_numInStock > 0) {
            m_numInStock--;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_name
           << "| " << std::right << std::setw(6) << std::setfill('0') << m_nextSerialNum << " | ";
        if (full) {
            os << std::setfill(' ') << std::setw(4) << std::right << m_numInStock << " | " << m_desc;
        }
        os << std::endl;
    }
}  
