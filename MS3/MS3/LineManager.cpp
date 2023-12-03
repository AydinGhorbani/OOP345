#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {

LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::string("Unable to open [") + filename + "] file.";
    }

    std::string record;
    Utilities util;
    size_t next_pos = 0;
    size_t pos = 0;
    bool more = true;

    // Read each record from the file
    while (std::getline(file, record)) {
        auto firstField = util.extractToken(record, next_pos, more);
        try {
            // Extract the first field from the record
            auto firstField = util.extractToken(record, next_pos, more);

            // Find the corresponding workstation in the vector
            auto it = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                // Compare case-insensitively
                return station->getItemName().compare(firstField) == 0;
            });

            // If workstation found, set it as the next station for the current workstation
            if (it != stations.end()) {
                if (m_firstStation == nullptr) {
                    m_firstStation = *it;
                } else {
                    (*it)->setNextStation(m_stations[pos - 1]);
                }

                // Add the workstation to the active line
                activeLine.push_back(*it);
                // Add the workstation to the vector of all stations
                m_stations.push_back(*it);
            } else {
                // Handle error: Station not found
                std::cerr << "Warning: Station [" << firstField << "] not found. Skipping." << std::endl;
            }

            ++pos;
        }  catch (const std::out_of_range& e) {
            // Print more information about the exception
            std::cerr << "Error: Out of range exception caught. What: " << e.what() << std::endl;

            // Print the record causing the issue
            std::cerr << "Error: Record causing the issue: [" << record << "]" << std::endl;

            // Print the position causing the issue
            std::cerr << "Error: Position causing the issue: " << next_pos << std::endl;

            // Optionally, you can re-throw the exception if needed
            throw;
        }

    }

    m_cntCustomerOrder = 0;
}

bool LineManager::run(std::ostream& os) {
    os << "Line Manager Iteration..." << std::endl;

    if (!activeLine.empty()) {
        for (auto& station : activeLine) {
            station->runProcess(os);
        }

        Workstation* completedStation = nullptr;
        for (auto& station : activeLine) {
            if (station->moveOrder()) {
                completedStation = station;
                break;  // break out of the loop once a station with a completed order is found
            }
        }

        if (completedStation) {
            CustomerOrder completedOrder;
            os << "   > " << completedStation->getItemName() << " has an order to be filled." << std::endl;
            --m_cntCustomerOrder;
        }

        // Reorder stations based on the order of activeLine
        reorderStations();
    }

    os << std::endl;

    return m_cntCustomerOrder > 0;
}

void LineManager::display(std::ostream& os) const {
    for (auto& station : activeLine) {
        station->display(os, false);
    }
}

void LineManager::reorderStations() {
    std::vector<Workstation*> temp;
    for (auto& station : activeLine) {
        temp.push_back(station);
    }
    activeLine = temp;
}

}  // namespace sdds
