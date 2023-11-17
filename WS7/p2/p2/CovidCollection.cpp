/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include "CovidCollection.h"

using namespace std;
namespace sdds
{
sdds::CovidCollection::CovidCollection(const char* fileName)
{
    fstream file(fileName);

    if (file)
    {
        while (file.peek() != EOF)
        {
            Covid newCov{};
            string tempYear{};
            string tempCases{};
            string tempDeaths{};
            char temp[26]{};
            char tempNum[6]{};

            file.read(temp, 25);
            newCov.m_country = temp;
            trimString(newCov.m_country);

            file.read(temp, 25);
            newCov.m_city = temp;
            trimString(newCov.m_city);
            
            file.read(temp, 25);
            newCov.m_variant = temp;
            trimString(newCov.m_variant);

            file.read(tempNum, 5);
            tempYear = tempNum;
            trimString(tempYear);
            newCov.m_year = stoi(tempYear);

            file.read(tempNum, 5);
            tempCases = tempNum;
            trimString(tempCases);
            newCov.m_cases = stoul(tempCases);
            
            file >> tempDeaths;
            trimString(tempDeaths);
            newCov.m_deaths = stoul(tempDeaths);
            file.ignore(numeric_limits<std::streamsize>::max(),'\n');
            m_coll.push_back(newCov);
        }
    }
    else
    {
        throw "File could not be reached";
    }
}

bool operator<(const std::string& a, const std::string& b)
{
    return false;
}


void CovidCollection::display(ostream& out, const string& country) const {
    const size_t totalCases = accumulate(m_coll.begin(), m_coll.end(), 0, [](size_t sum, const Covid& cov) {
        return sum + cov.m_cases;
    });
    const size_t totalDeaths = accumulate(m_coll.begin(), m_coll.end(), 0, [](size_t sum, const Covid& cov) {
        return sum + cov.m_deaths;
    });

    if (country == "ALL") {
        for_each(m_coll.begin(), m_coll.end(), [&](const Covid& cov) {
            out << cov << endl;
        });
        out << "|" << setw(80) << setiosflags(ios::right) << "Total cases around the world: " << totalCases << " |\n"
            << "|" << setw(80) << "Total deaths around the world: " << totalDeaths << " |\n" << resetiosflags(ios::right);
    }
    else {
        const size_t localCases = accumulate(m_coll.begin(), m_coll.end(), 0, [country](size_t sum, const Covid& cov) {
            return cov.m_country == country ? sum + cov.m_cases : sum;
        });
        const size_t localDeaths = accumulate(m_coll.begin(), m_coll.end(), 0, [country](size_t sum, const Covid& cov) {
            return cov.m_country == country ? sum + cov.m_deaths : sum;
        });

        stringstream TotCases{};
        stringstream TotDeaths{};
        stringstream TotPercent{};
        out << "Displaying information of country = " << country << "\n";
        for_each(m_coll.begin(), m_coll.end(), [&](const Covid& cov) {
            if (cov.m_country == country)
                out << cov << endl;
        });
        out << setfill('-') << setw(89) << '\n' << setfill(' ');
        TotCases << "Total cases in " << country << ": " << localCases;
        out << "|" << setw(85) << setiosflags(ios::right) << TotCases.str() << " |\n";
        TotDeaths << "Total deaths in " << country << ": " << localDeaths;
        out << "|" << setw(85) << TotDeaths.str() << " |\n";
        TotPercent << country << " has " << setprecision(6) << setiosflags(ios::fixed) << ((double)localCases / totalCases) * 100 << "% of global cases and " << ((double)localDeaths / totalDeaths) * 100 << "% of global deaths";
        out << "|" << setw(85) << TotPercent.str() << " |\n" << resetiosflags(ios::right);
    }
}

    void CovidCollection::updateStatus()
    {
        transform(m_coll.begin(), m_coll.end(), m_coll.begin(), [](const Covid& cov) {
            Covid newCov = cov;
            if (cov.m_deaths > EPIDEMIC_DEATHS)
                newCov.m_severity = "EPIDEMIC";
            else if(cov.m_deaths < EARLY_DEATHS)
                newCov.m_severity = "EARLY";
            else
                newCov.m_severity = "MILD";
            return newCov;
            });
    }

void CovidCollection::sort(const std::string& field) {
    std::sort(m_coll.begin(), m_coll.end(), [field](const Covid& a, const Covid& b) {
        if (field == "city") {
            return std::tie(a.m_city, a.m_deaths) < std::tie(b.m_city, b.m_deaths);
        } else if (field == "variant") {
            return std::tie(a.m_variant, a.m_deaths, a.m_year) < std::tie(b.m_variant, b.m_deaths, b.m_year);
        } else if (field == "year") {
            return std::tie(a.m_year, a.m_deaths) < std::tie(b.m_year, b.m_deaths);
        } else if (field == "cases") {
            return std::tie(a.m_cases, a.m_deaths) < std::tie(b.m_cases, b.m_deaths);
        } else if (field == "deaths") {
            return a.m_deaths < b.m_deaths;
        } else if (field == "severity") {
            return std::tie(a.m_severity, a.m_deaths) < std::tie(b.m_severity, b.m_deaths);
        } else {
            return std::tie(a.m_country, a.m_deaths) < std::tie(b.m_country, b.m_deaths);
        }
    });
}

    bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
    {
        return
            any_of(m_coll.begin(), m_coll.end(), [=](const Covid& cov) {
            return cov.m_variant == variant && cov.m_country == country && cov.m_deaths > deaths;
            });
    }

    std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
    {
        list<Covid> list{};
        copy_if(m_coll.begin(), m_coll.end(), std::back_inserter(list),[=](const Covid& cov) -> bool
            {
                return cov.m_deaths >= deaths;
            });
        return list;
    }


    void CovidCollection::trimString(std::string& source) {
        size_t begin = source.find_first_not_of(" \t\n");
        if (begin == std::string::npos) {
            source.clear();
        } else {
            size_t end = source.find_last_not_of(" \t\n");
            source = source.substr(begin, end - begin + 1);
        }
    }

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
    {
        out << "| " << setw(21) << std::left << theCovid.m_country << " | "
            << setw(15) << theCovid.m_city << " | "
            << setw(20) << theCovid.m_variant << " | " << resetiosflags(ios::left)
            << setw(6);

            if (theCovid.m_year > 0)
                out << theCovid.m_year << " | ";
            else
                out << " " << " | ";

            out << setw(4) << theCovid.m_cases << " | "
                << setw(3) << theCovid.m_deaths << " | "
                << "| " << setw(8) << theCovid.m_severity << " |";

        return out;
    }
}
