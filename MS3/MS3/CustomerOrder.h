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

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

namespace sdds {
    struct Item {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };
    class CustomerOrder {

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem = nullptr;
        static inline size_t m_widthField = 1;
    public:
        CustomerOrder();
        CustomerOrder(const std::string&);
        CustomerOrder(const CustomerOrder&);
        CustomerOrder& operator=(const CustomerOrder&);
        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder& operator=(CustomerOrder&&) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };

} // sdds

#endif //SDDS_CUSTOMERORDER_H
