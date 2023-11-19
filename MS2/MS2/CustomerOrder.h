/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Date       : 11/18/23
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef CUSTOMER_ORDER_H
#define CUSTOMER_ORDER_H

#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

    class CustomerOrder {
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };

        std::string m_name {};
        std::string m_product {};
        size_t m_cntItem = 0;
        Item** m_lstItem {};
        static size_t m_widthField;

    public:
        // Constructors and Rule of Three
        CustomerOrder();
        CustomerOrder(const CustomerOrder& other);
        CustomerOrder(const std::string& record);
        CustomerOrder& operator=(const CustomerOrder& other);
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;
        ~CustomerOrder();
        
        // Member functions
        void clearMemory();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;

        static void setWidthField(size_t width);
    };

}

#endif
