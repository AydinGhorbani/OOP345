#include <iomanip>
#include "CustomerOrder.h"

namespace sdds {

    // Initialize static member
    size_t CustomerOrder::m_widthField = 1;

    // Default constructor
    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

    // Constructor that parses the record and creates Order
    CustomerOrder::CustomerOrder(const std::string& record) : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);
        m_cntItem = 0;

        // Count the number of items in the record
        while (more) {
            util.extractToken(record, next_pos, more);
            m_cntItem++;
        }

        // Allocate memory for m_lstItem
        m_lstItem = new Item*[m_cntItem];

        // Reset the position for token extraction
        next_pos = 0;

        // Extract the first two tokens separately
        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);

        // Initialize m_lstItem with items from the record
        for (size_t i = 0; i < m_cntItem; ++i) {
            util.setFieldWidth(m_widthField);
            m_lstItem[i] = new Item(util.extractToken(record, next_pos, more));
            if (m_widthField < util.getFieldWidth()) {
                m_widthField = util.getFieldWidth();
            }
        }
    }


    // Copy constructor (deleted)
    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::string("Cannot make copies.");
    }

    // Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    // Move assignment operator
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            clearMemory();

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_name.clear();
            other.m_product.clear();
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    // Destructor
    CustomerOrder::~CustomerOrder() {
        clearMemory();
    }

    // Check if the order is filled
    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

// Check if a specific item is filled
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    for (size_t i = 0; i < m_cntItem; ++i) {
        if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
            return false;
        }
    }
    // Return false if the item is not found
    return true;
}

    // Fill an item in the order using a station
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    for (size_t i = 0; i < m_cntItem; ++++i) {
        if (!m_lstItem[i]->m_isFilled && station.getItemName() == m_lstItem[i]->m_itemName) {
            if (station.getQuantity() > 0) {
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                station.updateQuantity();
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
            else {
                os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }
}


    // Display the order details
void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;
    
    // Find the maximum length of item names in the order
    size_t maxItemNameLength = 0;
    for (size_t i = 0; i < m_cntItem; ++i) {
        if (m_lstItem[i]->m_itemName.length() > maxItemNameLength) {
            maxItemNameLength = m_lstItem[i]->m_itemName.length();
        }
    }

    for (size_t i = 0; i < m_cntItem; ++i) {
        os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
        os << std::setw(static_cast<int>(maxItemNameLength)) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName;
        
        // Add extra spaces for alignment
        os << std::setw(30 - maxItemNameLength) << std::setfill(' ') << "";
        
        os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
    }


//    os << "isOrderFilled(): " << (isOrderFilled() ? "FILLED" : "MISSING") << std::endl;
//    os << std::endl;  // Add a newline for clarity
}
    // Set the width field for display
    void CustomerOrder::setWidthField(size_t width) {
        m_widthField = width;
    }

    // Clear memory allocated for order items
    void CustomerOrder::clearMemory() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

}
