#include "LineManager.h"
#include "Utilities.h"

namespace sdds {
    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations) {
        Utilities util;
        std::ifstream file(filename);

        if (!file)
            throw std::string("Unable to open [") + filename + "] file.";

        std::string record;
        size_t next_pos = 0;
        bool more = true;

        while (std::getline(file, record)) {
            std::string stationName = util.extractToken(record, next_pos, more);

            auto station = std::find_if(stations.begin(), stations.end(), [&](const Workstation* ws) {
                return ws->getItemName() == stationName;
            });

            if (station != stations.end()) {
                if (m_firstStation == nullptr) {
                    m_firstStation = *station;
                }
                else {
                    (*station)->setNextStation(m_firstStation);
                    m_firstStation = *station;
                }
                activeLine.push_back(*station);
            }
        }

        file.close();
        m_stations = stations;
    }

    bool LineManager::run(std::ostream& os) {
        bool filled = true;

        if (!ToBeFilled.empty()) {
            *m_firstStation += std::move(ToBeFilled.back());
            ToBeFilled.pop_back();
        }

        for (auto& station : m_stations) {
            station->runProcess(os);
        }

        Workstation* completedStation = nullptr;
        for (auto& station : m_stations) {
            if (station->moveOrder()) {
                filled = false;
                completedStation = station;
            }
        }

        if (completedStation) {
            CustomerOrder completedOrder;
            if (completedStation->getIfCompleted(completedOrder)) {
                os << "Customer Order : " << completedOrder << " moved from " << completedStation->getItemName() << std::endl;
                --m_cntCustomerOrder;
            }
        }

        return filled;
    }

    void LineManager::display(std::ostream& os) const {
        for (auto& station : activeLine) {
            station->display(os, false);
        }
    }

    void LineManager::reorderStations() {
        std::stable_partition(activeLine.begin(), activeLine.end(), [](Workstation* ws) {
            return !ws->getNextStation();
        });

        m_stations = activeLine;
    }
}
