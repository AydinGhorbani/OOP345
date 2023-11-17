/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <string>
#include <vector>
#include <list>
#include "Covid.h"


namespace sdds
{
    const size_t EPIDEMIC_DEATHS = 300;
    const size_t EARLY_DEATHS = 50;

    class CovidCollection
    {
        std::vector<Covid> m_coll{};

        void trimString(std::string& source);
    public:
        CovidCollection() = default;
        CovidCollection(const char* fileName);
        //part 2
        void display(std::ostream& out, const std::string& country = "ALL") const;
        void sort(const std::string& field = "country");
        bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
        std::list<Covid> getListForDeaths(unsigned int deaths) const;
        void updateStatus();
    };
    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif


