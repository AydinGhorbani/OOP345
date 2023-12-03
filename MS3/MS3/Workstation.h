#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <vector>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {
    class Workstation : public Station {
        static std::vector<CustomerOrder> m_orders; // Declare the member as static

        Workstation* m_pNextStation{ nullptr };

    public:
        Workstation(const std::string& str);

        void runProcess(std::ostream& os);
        bool moveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        virtual void display(std::ostream& os, bool full) const;
        Workstation& operator-=(CustomerOrder&& order);
        Workstation& operator+=(CustomerOrder&& newOrder);
        virtual ~Workstation() = default;
    };
}
#endif
