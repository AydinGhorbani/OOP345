/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Date       : 11/11/23
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

//         //Debug output
//        std::cout << "Record: " << record << std::endl;

        m_itemName = util.extractToken(record, next_pos, more);

//        // Debug output
//        std::cout << "Item Name: " << m_itemName << std::endl;

        // Attempt to convert the serial number to size_t
        try {
            m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting serial number for item '" << m_itemName << "': " << e.what() << std::endl;
            return; // Exit the constructor if there's an error
        }

        // Debug output
//        std::cout << "Serial Number: " << m_serialNumber << std::endl;

        // Attempt to convert the quantity to size_t
        try {
            m_quantity = std::stoul(util.extractToken(record, next_pos, more));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error converting quantity for item '" << m_itemName << "': " << e.what() << std::endl;
            return; // Exit the constructor if there's an error
        }

//        // Debug output
//        std::cout << "Quantity: " << m_quantity << std::endl;

        m_description = util.extractToken(record, next_pos, more);

        if (m_widthField < util.getFieldWidth())
            m_widthField = util.getFieldWidth();

        m_id = static_cast<int>(++id_generator);
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            m_quantity--;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::right << std::setfill('0') << m_id << std::setfill(' ') << " | ";
        os << std::left << std::setw(m_widthField - 16) << m_itemName << "| " << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";

        if (full) {
            os << std::setfill(' ') << std::setw(4) << std::right << m_quantity << " | " << m_description;
        }

        os << std::endl;
    }
}
