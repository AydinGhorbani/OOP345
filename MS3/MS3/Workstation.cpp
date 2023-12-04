#include <iostream>
#include <iomanip>
#include <algorithm>  // for std::find
#include "Workstation.h"
#include "Station.h"

namespace sdds {
    // Initialize the static member
    std::vector<CustomerOrder> Workstation::m_orders;

    // Constructor
    Workstation::Workstation(const std::string& str) : Station(str) {}

    // Process the current Workstation
    void Workstation::runProcess(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    // Move order to the next station
bool Workstation::moveOrder() const{
    if (!m_orders.empty() && m_pNextStation) {
        *m_pNextStation += std::move(m_orders.front());
        m_orders.erase(m_orders.begin());  // Equivalent to pop_front() for std::vector
        return true;
    }
    return false;
}


    // Set the next station

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    // Get the next station
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    // Display information about the Workstation
    void Workstation::display(std::ostream& os, bool full) const {
        Station::display(os, full);

        if (!m_orders.empty()) {
            os << " --> " << m_orders.front();
        }

        os << std::endl;
    }


    // Move order to the current workstation
    Workstation& Workstation::operator-=(CustomerOrder&& order) {
        m_orders.push_back(std::move(order));
        return *this;
    }

    // Move order to the next workstation
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        if (static_cast<void*>(this) != static_cast<void*>(&newOrder)){  // Check if not the same object
            m_orders.push_back(std::move(newOrder));
        }
        return *this;
    }
}
