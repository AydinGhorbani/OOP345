#include <iomanip>
#include "CustomerOrder.h"

namespace sdds {

    size_t CustomerOrder::m_widthField = 1;

    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

    CustomerOrder::CustomerOrder(const std::string& record) : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);
        m_cntItem = 0;

        while (more) {
            util.setFieldWidth(m_widthField);

            // allocate memory for temporary array
            Item** temp = static_cast<Item**>(realloc(m_lstItem, sizeof(Item*) * (m_cntItem + 1)));
            if (temp == nullptr) {
                // handl realloc failure
                clearMemory();
                throw std::bad_alloc();
            }

            m_lstItem = temp;

            // allocate memory for the new Item and add it to the array
            m_lstItem[m_cntItem] = new Item(util.extractToken(record, next_pos, more));
            m_cntItem++;

            if (m_widthField < util.getFieldWidth()) {
                m_widthField = util.getFieldWidth();
            }
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other) {
        throw std::string("Cannot make copies.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
        *this = std::move(other);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_name = "";
            other.m_product = "";
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        clearMemory();
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    // Track if the order is filled before filling items
    bool orderFilledBefore = isOrderFilled();

    // Track if any items were filled during this call
    bool itemsFilled = false;

    for (size_t i = 0; i < m_cntItem; ++++i) {
        if (!m_lstItem[i]->m_isFilled && station.getItemName() == m_lstItem[i]->m_itemName) {
            if (station.getQuantity() > 0) {
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                station.updateQuantity();
                os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                itemsFilled = true;
            }
            else {
                station.updateQuantity();
                os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }

}



    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; ++i) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName;
            os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }

    void CustomerOrder::setWidthField(size_t width) {
        m_widthField = width;
    }

    void CustomerOrder::clearMemory() {
        for (size_t i = 0; i < m_cntItem; ++i) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }

}
