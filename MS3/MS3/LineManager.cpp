#include "LineManager.h"
#include <fstream>
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
        // Load connections between workstations from file
        m_stations = stations;
        std::ifstream file(filename);
        if (!file)
            throw std::string("Unable to open [") + filename + "] file.";

        std::string record;
        while (std::getline(file, record)) {
            Utilities utils;
            size_t pos = 0;
            bool more = true;
            std::string station1 = utils.extractToken(record, pos, more);
            std::string station2;

            if (more)
                station2 = utils.extractToken(record, pos, more);

            Workstation* ws1 = nullptr;
            Workstation* ws2 = nullptr;

            for (auto* station : stations) {
                if (station->getItemName() == station1)
                    ws1 = station;

                if (more && station->getItemName() == station2)
                    ws2 = station;
            }

            if (ws1 && ws2)
                ws1->setNextStation(ws2);
        }

        // Find the first station
        for (auto* station : stations) {
            if (!station->getNextStation()) {
                m_firstStation = station;
                break;
            }
        }

        // Copy all stations to activeLine
        activeLine = stations;

        file.close();
    }
bool LineManager::run(std::ostream& os) {
    os << "Line Manager Iteration: " << m_cntCustomerOrder + 1 << std::endl;

    if (!m_firstStation || m_cntCustomerOrder >= activeLine.size())
        return true;  // All orders processed

    os << "Processing order for station: " << m_firstStation->getItemName() << std::endl;

    // Add these lines for debugging
    os << "Station Quantity Before Processing: " << m_firstStation->getQuantity() << std::endl;
    os << "Order Item Name: " << g_pending.front().getItemName() << std::endl;

    m_firstStation->operator-=(std::move(g_pending.front()));

    // Add this line for debugging
    os << "Station Quantity After Processing: " << m_firstStation->getQuantity() << std::endl;

    auto it = std::find(activeLine.begin(), activeLine.end(), m_firstStation);
    if (it != activeLine.end()) {
        size_t index = std::distance(activeLine.begin(), it);
        m_firstStation = (index + 1 < activeLine.size()) ? activeLine[index + 1] : nullptr;
    }

    m_cntCustomerOrder++;
    return false;  // Continue processing orders
}

    void LineManager::display(std::ostream& os) const {
        for (const Workstation* station : m_stations) {
            station->display(std::cout, true);
        }
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> temp;

        // Find the first station
        for (auto* station : activeLine) {
            if (!station->getNextStation()) {
                temp.push_back(station);
                break;
            }
        }

        // Reorder the stations
        while (temp.size() < activeLine.size()) {
            for (auto* station : activeLine) {
                if (station->getNextStation() == temp.back()) {
                    temp.push_back(station);
                    break;
                }
            }
        }

        activeLine = temp;
    }
}
