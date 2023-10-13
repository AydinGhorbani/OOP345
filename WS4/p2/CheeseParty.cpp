/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */

#include "CheeseParty.h"
#include <iostream>
using namespace std;
namespace sdds {

    CheeseParty::CheeseParty() : cheeseArray(nullptr), numCheeses(0) {}

    CheeseParty::~CheeseParty() {
        delete[] cheeseArray;
    }

    CheeseParty::CheeseParty(const CheeseParty& src) : numCheeses(src.numCheeses) {
        cheeseArray = new Cheese*[numCheeses];
        for (size_t i = 0; i < numCheeses; ++i) {
            cheeseArray[i] = src.cheeseArray[i];
        }
    }

    CheeseParty& CheeseParty::operator=(const CheeseParty& src) {
        if (this != &src) {
            numCheeses = src.numCheeses;
            delete[] cheeseArray;
            // no need nullptr.
            cheeseArray = new Cheese*[numCheeses];
            for (size_t i = 0; i < numCheeses; ++i) {
                cheeseArray[i] = src.cheeseArray[i];
            }
        }
        return *this;
    }

    CheeseParty::CheeseParty(CheeseParty&& src) noexcept : cheeseArray(src.cheeseArray), numCheeses(src.numCheeses) {
        src.cheeseArray = nullptr;
        src.numCheeses = 0;
    }

    CheeseParty& CheeseParty::operator=(CheeseParty&& src) noexcept {
        if (this != &src) {
            delete[] cheeseArray;

            // move data from src
            cheeseArray = src.cheeseArray;
            numCheeses = src.numCheeses;

            // Reset src
            src.cheeseArray = nullptr;
            src.numCheeses = 0;
        }
        return *this;
    }


    CheeseParty& CheeseParty::addCheese(Cheese& cheese) {
        for (size_t i = 0; i < numCheeses; ++i) {
            if (cheeseArray[i] == &cheese) {
                return *this;
            }
        }

        sdds::Cheese** tempArray = new  sdds::Cheese*[numCheeses + 1];

        for (size_t i = 0; i < numCheeses; ++i) {
            tempArray[i] = cheeseArray[i];
        }

        tempArray[numCheeses] = &cheese;
        delete[] cheeseArray;
            cheeseArray = tempArray;
        
        ++numCheeses;

        return *this;
    }


    CheeseParty& CheeseParty::removeCheese() {
        size_t numNonZeroWeight = 0;

        // Count the number of non-zero weight cheeses
        for (size_t i = 0; i < numCheeses; ++i) {
            if (cheeseArray[i]->getWeight() != 0) {
                ++numNonZeroWeight;
            }
        }

        if (numNonZeroWeight < numCheeses) {
            // Create a new dynamic array to store non-zero weight cheeses
            Cheese** tempArray = new Cheese*[numNonZeroWeight];
            size_t newIndex = 0;

            for (size_t i = 0; i < numCheeses; ++i) {
                if (cheeseArray[i]->getWeight() != 0) {
                    tempArray[newIndex] = cheeseArray[i];
                    ++newIndex;
                }
            }
            delete[] cheeseArray;
            cheeseArray = tempArray;
            numCheeses = numNonZeroWeight;
        }

        return *this;
    }

std::ostream& operator<<(std::ostream& os, const CheeseParty& party) {
    os << "--------------------------\n";
    os << "Cheese Party\n";
    os << "--------------------------\n";

    if (party.numCheeses == 0) {
        os << "This party is just getting started!\n";
    }
    else {
        for (size_t i = 0; i < party.numCheeses; ++i) {
            os << *party.cheeseArray[i];
        }
    }

    os << "--------------------------\n";
    return os;
}

}  // namespace sdds


