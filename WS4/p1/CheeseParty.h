/*
//  CheeseParty.h
//  ws4
//
//  Created by aydin ghorbani on 2023-10-08.
//

#ifndef CheeseParty_h
#define CheeseParty_h

#include <iostream>
#include <string>
#include "Cheese.h" // Include the Cheese class

namespace sdds {
    class CheeseParty {
        Cheese** cheeseArray;
        size_t numCheeses;

    public:
        CheeseParty();
        ~CheeseParty(); // Implement the destructor to release memory
        CheeseParty& addCheese(Cheese& cheese);
        CheeseParty& removeCheese();
        friend std::ostream& operator<<(std::ostream& os, const CheeseParty& party);
    };

    // Implement member functions for the CheeseParty class
    // Implement the constructor, destructor, addCheese, and removeCheese functions
}
// Implement the insertion operator for the CheeseParty class
std::ostream& operator<<(std::ostream& os, const sdds::CheeseParty& party) {
    // Format and output party details as specified
    return os;
}


#endif /* CheeseParty_h */



/*
