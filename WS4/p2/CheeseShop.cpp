/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include <iostream>
#include <stdio.h>
#include "CheeseShop.h"

namespace sdds {

    CheeseShop::CheeseShop(const std::string& name) : shopName(name), cheeseArray(nullptr), numCheeses(0) {}

    CheeseShop::~CheeseShop() {
        for (size_t i = 0; i < numCheeses; ++i) {
            delete cheeseArray[i];
        }
        delete[] cheeseArray;
    }
    //roule of 5, nothing fancy happening here!

    CheeseShop::CheeseShop(const CheeseShop& src) : shopName(src.shopName), numCheeses(src.numCheeses) {
        cheeseArray = new Cheese*[numCheeses];
        for (size_t i = 0; i < numCheeses; ++i) {
            cheeseArray[i] = new Cheese(*(src.cheeseArray[i]));
        }
    }

    CheeseShop& CheeseShop::operator=(const CheeseShop& src) {
        if (this != &src) {
            shopName = src.shopName;
            numCheeses = src.numCheeses;
            
            // deallocating existing memory
            for (size_t i = 0; i < numCheeses; ++i) {
                delete cheeseArray[i];
            }
            delete[] cheeseArray;
            
            // allocate new memory
            cheeseArray = new Cheese*[numCheeses];
            for (size_t i = 0; i < numCheeses; ++i) {
                cheeseArray[i] = new Cheese(*(src.cheeseArray[i]));
            }
        }
        return *this;
    }

    CheeseShop::CheeseShop(CheeseShop&& src) noexcept : shopName(std::move(src.shopName)), cheeseArray(src.cheeseArray), numCheeses(src.numCheeses) {
        src.cheeseArray = nullptr;
        src.numCheeses = 0;
    }

    CheeseShop& CheeseShop::operator=(CheeseShop&& src) noexcept {
        if (this != &src) {
            for (size_t i = 0; i < numCheeses; ++i) {
                delete cheeseArray[i];
            }
            delete[] cheeseArray;

            // move data from src
            shopName = std::move(src.shopName);
            cheeseArray = src.cheeseArray;
            numCheeses = src.numCheeses;

            src.cheeseArray = nullptr;
            src.numCheeses = 0;
        }
        return *this;
    }

    CheeseShop& CheeseShop::addCheese(Cheese& cheese) {
        // creating a new dynamic array with room for an additional cheese pointer
        Cheese** tempArray = new Cheese*[numCheeses + 1];
        
        for (size_t i = 0; i < numCheeses; ++i) {
            tempArray[i] = cheeseArray[i];
        }

        tempArray[numCheeses] = new Cheese(cheese);

        delete[] cheeseArray;
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
