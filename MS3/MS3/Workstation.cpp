#include "Workstation.h"

namespace sdds {
    std::deque<CustomerOrder> g_pending;
    std::vector<CustomerOrder> g_completed;
    std::vector<CustomerOrder> g_incomplete;

    void Workstation::runProcess(std::ostream& os) {
        if (!m_orders.empty() && !m_orders.front().isItemFilled(getItemName())) {
            m_orders.front().fillItem(*this, os);
            if (m_orders.front().isOrderFilled()) {
                g_completed.push_back(std::move(m_orders.front()));
                m_orders.pop_front();
            }
            else {
                g_incomplete.push_back(std::move(m_orders.front()));
                m_orders.pop_front();
            }
        }
    }

    bool Workstation::moveOrder() {
        if (!m_orders.empty() && m_orders.front().isItemFilled(getItemName())) {
            *m_pNextStation += std::move(m_orders.front());
            m_orders.pop_front();
            return true;
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    const Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os, bool full) const {
        Station::display(os, full);
        if (!m_orders.empty() && full) {
            os << " --> " << m_orders.front().getItemName();
        }
        os << std::endl;
    }

    Workstation& Workstation::operator-=(CustomerOrder&& order) {
        m_orders.push_back(std::move(order));
        return *this;
    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}
