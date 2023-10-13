/*
//  CheeseShop.h
//  ws4
//
//  Created by aydin ghorbani on 2023-10-08.
//

#ifndef CheeseShop_h
#define CheeseShop_h

#include <iostream>
#include <string>
#include "Cheese.h" // Include the Cheese class

namespace sdds {
    class CheeseShop {
        std::string shopName;
        Cheese** cheeseArray;
        size_t numCheeses;

    public:
        CheeseShop(const std::string& name = "No Name");
        ~CheeseShop(); // Implement the destructor to release memory
        CheeseShop& addCheese( Cheese& cheese);
        friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
    };

    // Implement member functions for the CheeseShop class
    // Implement the constructor, destructor, and addCheese function
}

// Implement the insertion operator for the CheeseShop class
std::ostream& operator<<(std::ostream& os, const sdds::CheeseShop& shop) {
    // Format and output shop details as specified
    return os;
}

#endif /* CheeseShop_h */
