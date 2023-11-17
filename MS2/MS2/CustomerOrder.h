#ifndef CUSTOMER_ORDER_H
#define CUSTOMER_ORDER_H

#include <iostream>
#include <string>
#include "Station.h"  // Assuming the existence of the Station class
#include "Utilities.h"

namespace sdds {

    class CustomerOrder {
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;

    public:
        // Constructors and Rule of Three
        CustomerOrder();
        CustomerOrder(const std::string& record);
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;
        ~CustomerOrder();

        // Member functions
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;

        // Static member function
        static void setWidthField(size_t width);

    };

}  // namespace sdds

#endif // CUSTOMER_ORDER_H
