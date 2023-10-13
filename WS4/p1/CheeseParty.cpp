/*
//  CheeseParty.cpp
//  ws4
//
//  Created by aydin ghorbani on 2023-10-08.
//

#include "CheeseParty.h"
#include <iostream>
using namespace std;
namespace sdds {

    CheeseParty::CheeseParty() : cheeseArray(nullptr), numCheeses(0) {}

    CheeseParty::~CheeseParty() {
        // Release memory for the dynamic array of pointers
        delete[] cheeseArray;
    }


    CheeseParty& CheeseParty::addCheese(Cheese& cheese) {
        // Check if the cheese is already in the array
        for (size_t i = 0; i < numCheeses; ++i) {
            if (cheeseArray[i] == &cheese) {
                // Cheese is already in the party, do nothing
                return *this;
            }
        }

        // Create a new dynamic array with room for an additional Cheese pointer
        sdds::Cheese** tempArray = new  sdds::Cheese*[numCheeses + 1];

        // Copy existing Cheese pointers to the new array
        for (size_t i = 0; i < numCheeses; ++i) {
            tempArray[i] = cheeseArray[i];
        }

        // Add the address of the Cheese object to the end of the array
        tempArray[numCheeses] = &cheese;  // Assigning a pointer to a const Cheese object

        // Delete the old dynamic array of pointers
        delete[] cheeseArray;

        // Update the cheeseArray pointer and increment numCheeses
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

            // Copy non-zero weight cheeses to the new array
            for (size_t i = 0; i < numCheeses; ++i) {
                if (cheeseArray[i]->getWeight() != 0) {
                    tempArray[newIndex] = cheeseArray[i];
                    ++newIndex;
                }
            }

            // Delete the old dynamic array of pointers
            delete[] cheeseArray;

            // Update the cheeseArray pointer and numCheeses
            cheeseArray = tempArray;
            numCheeses = numNonZeroWeight;
        }

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const CheeseParty& party) {
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

*/
