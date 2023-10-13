/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>
#include <string>
#include "Cheese.h" // Include the Cheese class



namespace sdds {

    class CheeseParty {
        Cheese** cheeseArray;
        size_t numCheeses;

    public:
        CheeseParty();
        ~CheeseParty();
        CheeseParty(const CheeseParty& src);
        CheeseParty& operator=(const CheeseParty& src);
        CheeseParty(CheeseParty&& src) noexcept;
        CheeseParty& operator=(CheeseParty&& src) noexcept;
        CheeseParty& addCheese(Cheese& cheese);
        CheeseParty& removeCheese();
        friend std::ostream& operator<<(std::ostream& os, const CheeseParty& party);
    };
}


#endif //SDDS_CHEESEPARTY_H




