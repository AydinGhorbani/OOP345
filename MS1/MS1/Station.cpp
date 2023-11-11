//
//  Station.cpp
//  MS1
//
//  Created by aydin ghorbani on 2023-11-08.
//
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

        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
        m_quantity = std::stoul(util.extractToken(record, next_pos, more));
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
        os << m_widthField<< std::endl;
        os <<std::setw(3) << std::right << std::setfill('0') << m_id << std::setfill(' ')<< " | ";
        os << std::left << std::setw(m_widthField - 16) << m_itemName << "| " << std::setw(6) << m_serialNumber << "|";

        if (full) {
            os << std::setfill(' ') << std::setw(4) << std::right <<m_quantity<< " | " << m_description;
        }

        os << std::endl;
    }
}
