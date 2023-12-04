#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream input(file);
        if (!input.is_open()) {
            throw std::string("Unable to open [") + file + "] file.";
        }

        // Read all records from the file into a vector of strings
        std::vector<std::string> records;
        std::copy(std::istream_iterator<std::string>(input), std::istream_iterator<std::string>(), std::back_inserter(records));

        Utilities util;
        m_stations = stations;

        // Iterate through each record using for_each and lambda
        std::for_each(records.begin(), records.end(), [&](const std::string& record) {
            size_t pos = 0;
            bool more = true;

            // Extract the first and next workstation names using Utilities
            std::string firstWorkstation = util.extractToken(record, pos, more);
            std::string nextWorkstation = util.extractToken(record, pos, more);

            // Find the corresponding workstation in the vector
            auto itFirst = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                return util.trim(station->getItemName()) == util.trim(firstWorkstation);
            });

            auto itNext = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                return util.trim(station->getItemName()) == util.trim(nextWorkstation);
            });

            // If both workstations are found, set the next workstation for the current workstation
            if (itFirst != stations.end() && itNext != stations.end()) {
                if (m_firstStation == nullptr) {
                    m_firstStation = *itFirst;
                }
                (*itFirst)->setNextStation(*itNext);
            } else {
                // Handle error: Workstation not found
                std::cerr << "Warning: Workstation [" << firstWorkstation << "] or [" << nextWorkstation << "] not found. Skipping." << std::endl;
            }
        });

        // Calculate the total number of orders in the g_pending queue
    m_cntCustomerOrder = std::count_if(m_stations.begin(), m_stations.end(), [](const Workstation* station) {
        // Use moveOrder() to check if there are pending orders
        return station->moveOrder();
    });
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
