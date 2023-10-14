// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Book.h"
#include "Book.h" // intentional



// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// ws books.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	sdds::Book library[7];
	if (argc == 2) {
        std::ifstream file(argv[1]);
        if (!file.is_open()) {
            std::cerr << "ERROR: Cannot open the file.\n";
            return AppErrors::CannotOpenFile;
        }

        int index = 0;
        std::string line;
        while (index < 7 && std::getline(file, line)) {
            // Check for comments
            if (line[0] != '#') {
                library[index] = sdds::Book(line);
                index++;
            }
        }
        
        file.close();
    }
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}
    
    double usdToCadRate = 1.3;
    double gbpToCadRate = 1.5;
    
    auto fixBookPrice = [usdToCadRate, gbpToCadRate](sdds::Book& book) {
        // Debug output to check conditions
//        std::cout << "Debug: Country = " << book.country() << ", Year = " << book.year() << std::endl;
//        std::cout << "COUNTRY NAME: " << book.country() << std::endl;
        // Define the conversion rates
        if (book.country().find("US") != std::string::npos)
        {
            book.setPrice(usdToCadRate * book.price());
        }
        if (book.country().find("UK") != std::string::npos && book.year() >= 1990 && book.year() <= 1999) {

            book.setPrice(gbpToCadRate * book.price());
        }

    };


        std::cout << "-----------------------------------------\n";
        std::cout << "The library content\n";
        std::cout << "-----------------------------------------\n";
        // TODO: iterate over the library and print each book to the screen
        for (int i = 0; i < 7; i++) {
            std::cout << library[i] << std::endl;
        }
        
        
        std::cout << "-----------------------------------------\n\n";
        
        // TODO: iterate over the library and update the price of each book
        //         using the lambda defined above.
    // Before calling fixBookPrice
//    std::cout << "Before calling fixBookPrice:" << std::endl;
//    for (int i = 0; i < 7; i++) {
//        std::cout << library[i] << std::endl;
//    }

    // Call fixBookPrice
    for (int i = 0; i < 7; i++) {
        fixBookPrice(library[i]);
    }

//    // After calling fixBookPrice
//    std::cout << "After calling fixBookPrice:" << std::endl;
//    for (int i = 0; i < 7; i++) {
//        std::cout << library[i] << std::endl;
//    }
//
        std::cout << "-----------------------------------------\n";
        std::cout << "The library content (updated prices)\n";
        std::cout << "-----------------------------------------\n";
        // TODO: iterate over the library and print each book to the screen
        for (int i = 0; i < 7; i++) {
            std::cout << library[i] << std::endl;
        }
        
        std::cout << "-----------------------------------------\n";
        
        return cout;
}
