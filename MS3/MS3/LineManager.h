/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Repository : https://github.com/AydinGhorbani/OOP345/
 
 Please find every commit (Over 50 throughout the semester) made in this link, including the debugging techniques used to develop this project.
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that I searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include <ostream>
#include <string>
#include "Workstation.h"

namespace sdds {
    class LineManager{
    std::vector<Workstation*> m_activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
    
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};
}

#endif
