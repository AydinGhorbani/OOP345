#include "LineManager.h"
#include <fstream>
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
        // Load connections between workstations from file
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
        for (auto* station : stations)
            activeLine.push_back(station);

        file.close();
    }

    bool LineManager::run(std::ostream& os) {
        os << "Line Manager Iteration: " << m_cntCustomerOrder + 1 << std::endl;

        if (!m_firstStation || m_cntCustomerOrder >= activeLine.size())
            return true;  // All orders processed

        *(m_firstStation) -= std::move(g_pending.front());
        g_pending.pop_front();

        // Find the next station
        size_t i = 0;
        for (; i < activeLine.size() - 1; ++i) {
            if (activeLine[i] == m_firstStation)
                break;
        }

        m_firstStation = activeLine[i + 1];

        m_cntCustomerOrder++;
        return false;  // Continue processing orders
    }

    void LineManager::display(std::ostream& os) const {
        for (const auto* station : activeLine)
            station->display(os, false);
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
