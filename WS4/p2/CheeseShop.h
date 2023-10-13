/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <string>
#include "Cheese.h"

namespace sdds {

    class CheeseShop {
        std::string shopName;
        Cheese** cheeseArray;
        size_t numCheeses;

    public:
        CheeseShop(const std::string& name);
        ~CheeseShop();
        CheeseShop(const CheeseShop& src);
        CheeseShop& operator=(const CheeseShop& src);
        CheeseShop(CheeseShop&& src) noexcept;
        CheeseShop& operator=(CheeseShop&& src) noexcept;
        CheeseShop& addCheese(Cheese& cheese);
        friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
    };
}

#endif //CheeseShop_h
