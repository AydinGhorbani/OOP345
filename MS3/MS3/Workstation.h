#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
    extern std::deque<CustomerOrder> g_pending;
    extern std::vector<CustomerOrder> g_completed;
    extern std::vector<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{ nullptr };

    public:
        Workstation(const std::string& str) : Station(str) {}

        void runProcess(std::ostream& os);
        bool moveOrder();
        void setNextStation(Workstation* station);
        const Workstation* getNextStation() const;
        virtual void display(std::ostream& os, bool full) const;
        Workstation& operator-=(CustomerOrder&& order);
        Workstation& operator+=(CustomerOrder&& newOrder);

    };
}
#endif
