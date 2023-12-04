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
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;
namespace sdds {

CustomerOrder::CustomerOrder() {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const string& str) : CustomerOrder() {
    Utilities util;
    size_t next_pos = 0, posOfItems;
    bool more = true;
    m_name = trim(util.extractToken(str, next_pos, more));
    m_product = util.extractToken(str, next_pos, more);
    m_cntItem = 0;
    posOfItems = next_pos;

    while (more) {
        util.extractToken(str, next_pos, more);
        m_cntItem++;
    }

    m_lstItem = new Item*[m_cntItem];
    next_pos = posOfItems;
    more = true;
    for (size_t i = 0; i < m_cntItem; i++)
        m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));

    m_product = trim(m_product);
    m_widthField = std::max(m_widthField, util.getFieldWidth());
}


    //Move constructor
    CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept {
        *this = std::move(obj);
    }


    //Move assignment
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept{
        if (this != &obj) {
            if (m_lstItem) {
                for (size_t i = 0; i < m_cntItem; i++) {
                    delete m_lstItem[i];
                }
                delete[] m_lstItem;
            }
            m_name = obj.m_name;
            m_product = obj.m_product;
            m_cntItem = obj.m_cntItem;
            m_lstItem = obj.m_lstItem;

            obj.m_name = "";
            obj.m_product = "";
            obj.m_cntItem = 0u;
            obj.m_lstItem = nullptr;
        }
        return *this;
    }

    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++)
            if (!m_lstItem[i]->m_isFilled)
                return false;

        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++)
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                return false;
        
        return true;
    }

    // I got help for this part
    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        bool found = false;
        for (size_t i = 0; i < m_cntItem && !found; i++) {
            if (trim(m_lstItem[i]->m_itemName) == trim(station.getItemName()) && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << trim(m_product) << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    found = true;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }


    // I got help for this part
    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << std::left << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
               << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << "- "
               << ((m_lstItem[i]->m_isFilled) ? "FILLED" : "TO BE FILLED") << std::endl;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }


} // sdds
