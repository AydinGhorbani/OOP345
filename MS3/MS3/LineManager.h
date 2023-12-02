#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace sdds {
    class LineManager {
        std::vector<Workstation*> activeLine;
        size_t m_cntCustomerOrder{ 0 };
        Workstation* m_firstStation{ nullptr };
        std::vector<Workstation*> m_stations;
    public:
        LineManager(const std::string& filename, const std::vector<Workstation*>& stations);
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
        void reorderStations();
    };
}
#endif
