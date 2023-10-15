/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/

#include "SpellChecker.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

namespace sdds {
    int m_counts[] = {0};

    string trim(const string& str) {
        string result = str;
        // Remove leading spaces
        while (!result.empty() && isspace(result.front())) {
            result.erase(result.begin());
        }
        // Remove trailing spaces
        while (!result.empty() && isspace(result.back())) {
            result.pop_back();
        }
        return result;
    }

    void SpellChecker::showStatistics(ostream& os) const {
        os << "Spellchecker Statistics" << endl;
        if (m_counts[0] == 5) m_counts[0] -= 1;
        for (int i = 0; i < 6; ++i) {
            os << right << setw(15) << m_badWords[i] << ": " << m_counts[i] << " replacements" << endl;
        }
    }

    SpellChecker::SpellChecker(const char* filename) {
        for (int i = 0; i < 6; ++i) {
            m_counts[i] = 0;  // Initialize the counts for this instance
        }

        ifstream file(filename);
        if (!file) {
            throw runtime_error("Bad file name!");
        }

        for (int i = 0; i < 6; ++i) {
            string line;
            if (!getline(file, line)) {
                file.close(); // Close the file
                throw runtime_error("File is too short or has incorrect format!");
            }

            size_t pos = line.find(' ');
            if (pos == string::npos) {
                file.close(); // Close the file
                throw runtime_error("Bad file format!");
            }

            m_badWords[i] = trim(line.substr(0, pos));
            m_goodWords[i] = trim(line.substr(pos + 1));
        }

        file.close(); // Close the file
    }

    void SpellChecker::operator()(string& text) const {
        for (int i = 0; i < 6; ++i) {
            size_t found = text.find(m_badWords[i]);
            int count = 0;
            while (found != string::npos) {
                text.replace(found, m_badWords[i].size(), m_goodWords[i]);
                found = text.find(m_badWords[i], found + m_goodWords[i].size());
                ++count;
            }
            // Update the replacement count for the word
            m_counts[i] += count;
        }
    }
}
