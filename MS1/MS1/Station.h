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

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

namespace sdds {
    class Station {
        int m_id;
        std::string m_itemName;
        std::string m_description;
        size_t m_serialNumber;
        size_t m_quantity;

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string& record);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}

#endif /*SDDS_STATION_H*/
