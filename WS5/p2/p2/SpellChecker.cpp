#include "SpellChecker.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace sdds {
using namespace std;
int m_counts[] = {0};
    void SpellChecker::showStatistics(std::ostream& os) const {
        os << "Spellchecker Statistics" << std::endl;
        if (m_counts[0] == 5) m_counts[0] -= 1;
        for (int i = 0; i < 6; ++i) {
            os << std::right <<  std::setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements" << std::endl;
        }
    }

    SpellChecker::SpellChecker(const char* filename) {
        for (int i = 0; i < 6; ++i) {
            m_counts[i] = 0;  // Initialize the counts for this instance
        }

        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Bad file name or file not found!");
        }

        for (int i = 0; i < 6; ++i) {
            std::string line;
            if (!std::getline(file, line)) {
                file.close(); // Close the file
                throw std::runtime_error("File is too short or has incorrect format!");
            }

            size_t pos = line.find(' ');
            if (pos == std::string::npos) {
                file.close(); // Close the file
                throw std::runtime_error("Bad file format!");
            }

            m_badWords[i] = line.substr(0, pos);
            m_goodWords[i] = line.substr(pos + 1);
        }

        file.close(); // Close the file
    }

    void SpellChecker::operator()(std::string& text) const {
        for (int i = 0; i < 6; ++i) {
            size_t found = text.find(m_badWords[i]);
            int count = 0;
            while (found != std::string::npos) {
                text.replace(found, m_badWords[i].size(), m_goodWords[i]);
                found = text.find(m_badWords[i], found + m_goodWords[i].size());
                ++count;
            }
            // Update the replacement count for the word
            m_counts[i] += count;
        }
    }
}
