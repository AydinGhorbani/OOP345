/*
//  CheeseShop.cpp
//  ws4
//
//  Created by aydin ghorbani on 2023-10-08.
//
#include <iostream>
#include <stdio.h>
#include "CheeseShop.h"


namespace sdds {

    CheeseShop::CheeseShop(const std::string& name) : shopName(name), cheeseArray(nullptr), numCheeses(0) {}

    CheeseShop::~CheeseShop() {
        // Release memory for Cheese objects
        for (size_t i = 0; i < numCheeses; ++i) {
            delete cheeseArray[i];
        }
        // Release memory for the dynamic array of pointers
        delete[] cheeseArray;
    }

    CheeseShop& CheeseShop::addCheese(Cheese& cheese) {
        // Create a new dynamic array with room for an additional Cheese pointer
        Cheese** tempArray = new Cheese*[numCheeses + 1];
        
        // Copy existing Cheese pointers to the new array
        for (size_t i = 0; i < numCheeses; ++i) {
            tempArray[i] = cheeseArray[i];
        }
        
        // Add the new Cheese object to the end of the array
        tempArray[numCheeses] = new Cheese(cheese);
        
        // Delete the old dynamic array of pointers
        delete[] cheeseArray;
        
        // Update the cheeseArray pointer and increment numCheeses
        cheeseArray = tempArray;
        ++numCheeses;

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const CheeseShop& shop) {
        os << "--------------------------\n";
        os << shop.shopName << "\n";
        os << "--------------------------\n";

        if (shop.numCheeses == 0) {
            os << "This shop is out of cheese!\n";
        }
        else {
            for (size_t i = 0; i < shop.numCheeses; ++i) {
                os << *shop.cheeseArray[i];
            }
        }

        os << "--------------------------\n";
        return os;
    }

}  // namespace sdds


 */
