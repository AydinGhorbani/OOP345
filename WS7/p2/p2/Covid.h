/*
****************************************
Full Name  : Aydin Ghorbani
Student ID#: 124170226
Email      : aghorbani8@myseneca.ca

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
The parts that I searched or got help to do are mentioned.
****************************************
*/
#ifndef SDDS_COVID_H
#define SDDS_COVID_H

#include <string>

namespace sdds {
    struct Covid
    {
        int m_year{};
        std::string m_country;
        std::string m_city;
        std::string m_variant;
        size_t m_cases{};
        size_t m_deaths{};
        std::string m_severity{ "General" };
    };
}

#endif // SDDS_COVID_H
