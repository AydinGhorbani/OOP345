// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     // intentional
#include "SpellChecker.h"
#include "SpellChecker.h"   // intentional
#include "Book.h"
#include "Book.h"           // intentional
#include "Movie.h"
#include "Movie.h"          // intentional

// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
    #error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
    #error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
    #error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
    #error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

//enum AppErrors
//{
//    CannotOpenFile = 1, // An input file cannot be opened
//    BadArgumentCount = 2, // The application didn't receive anough parameters
//};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
    const sdds::Book& theBook)
{
    std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection,
    const sdds::Movie& theMovie)
{
    std::cout << "Movie \"" << theMovie.title()
        << "\" added to collection \"" << theCollection.name()
        << "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
    std::cout << "Command Line:\n";
    std::cout << "--------------------------\n";
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    std::cout << "--------------------------\n\n";

    // get the books
    sdds::Collection<sdds::Book> library("Bestsellers");
    if (argc == 5) {
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "ERROR: Cannot open file " << argv[1] << std::endl;
 //           return AppErrors::CannotOpenFile;
        }

        std::string line;
         do{
            std::getline(file, line);
            if (line[0] != '#') {
                sdds::Book book(line);
                library += book;
            }
         } while (library.size() <4);

        library.setObserver(bookAddedObserver);

        while (std::getline(file, line)) {
            if (line[0] != '#') {
                sdds::Book book(line);
                library += book;
            }
        }

    }
    else
    {
        std::cerr << "ERROR: Incorrect number of arguments.\n";
//        std::exit(AppErrors::BadArgumentCount);
    }

    const double usdToCadRate = 1.3;
    const double gbpToCadRate = 1.5;
    
    auto fixBookPrice = [usdToCadRate, gbpToCadRate](sdds::Book& book) {
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
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    // TODO (from part #1): iterate over the library and update the price of each book
    //         using the lambda defined above.
    
    for (size_t i = 0; i < library.size(); ++i) {
        fixBookPrice(const_cast<sdds::Book&>(library[i]));
    }
    
    std::cout << "-----------------------------------------\n";
    std::cout << "The library content (updated prices)\n";
    std::cout << "-----------------------------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n\n";

    sdds::Collection<sdds::Movie> theCollection("Action Movies");

    // Process the file
    sdds::Movie movies[5];
    if (argc > 2) {
        std::ifstream movieFile(argv[2]);
        if (movieFile) {
            std::string line;
            size_t count = 0;
            while (count < 5 && std::getline(movieFile, line)) {
                if (line[0] != '#') {
                    sdds::Movie movie(line);
                    movies[count++] = movie;
                }
            }
        }
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "Testing addition and callback function\n";
    std::cout << "-----------------------------------------\n";
    if (argc > 2) {
        // Add a few movies to collection; no observer is set
        ((theCollection += movies[0]) += movies[1]) += movies[2];
        theCollection += movies[1];
        // add more movies; now we get a callback from the collection
        theCollection.setObserver(movieAddedObserver);
        theCollection += movies[3];
        theCollection += movies[3];
        theCollection += movies[4];
    }
    else {
        std::cout << "** No movies in the Collection\n";
    }
    std::cout << "-----------------------------------------\n\n";
    
    std::cout << "-----------------------------------------\n";
    std::cout << "Testing exceptions and operator[]\n";
    std::cout << "-----------------------------------------\n";


        // TODO: The following loop can generate generate an exception
        //         write code to handle the exception
        //       If an exception occurs print a message in the following format
        //** EXCEPTION: ERROR_MESSAGE<endl>
        //         where ERROR_MESSAGE is extracted from the exception object.
        try {
            for (auto i = 0u; i < 10; ++i)
            std::cout << theCollection[i];
        }
        catch (const std::out_of_range& ex) {
            std::cout << "** EXCEPTION: " << ex.what() << std::endl;
        }

    std::cout << "-----------------------------------------\n\n";


    std::cout << "-----------------------------------------\n";
    std::cout << "Testing the functor\n";
    std::cout << "-----------------------------------------\n";
    for (auto i = 3; i < argc; ++i) {
        try {
            sdds::SpellChecker sp(argv[i]);
            for (size_t j = 0; j < library.size(); ++j)
                library[j].fixSpelling(sp);
            sp.showStatistics(std::cout);

            for (size_t j = 0; j < theCollection.size(); ++j)
                theCollection[j].fixSpelling(sp);
            sp.showStatistics(std::cout);
        }
        catch (const std::exception& ex) {
            std::cout << "** EXCEPTION: " << ex.what() << std::endl;
        }
    }
    if (argc < 3) {
        std::cout << "** Spellchecker is empty\n";
        std::cout << "-----------------------------------------\n";
    }
    std::cout << "\n";

    std::cout << "=========================================\n";
    std::cout << "Wrapping up this workshop\n";
    std::cout << "--------------- Movies ------------------\n";
    std::cout << theCollection;
    std::cout << "--------------- Books -------------------\n";
    std::cout << library;
    std::cout << "-----------------------------------------\n";
    std::cout << "Testing operator[] (the other overload)\n";
    std::cout << "-----------------------------------------\n";
    sdds::Movie* aMovie = theCollection["Terminator 2"];
    if (aMovie == nullptr)
        std::cout << "** Movie Terminator 2 not in collection.\n";
    std::cout <<"In this collection:\n";
    std::cout << std::setw(28)<< "" <<"Dark Phoenix | 2019 | Jean Grey begins to develop incredible Dark powers that corrupt and turn her into a Dark Phoenix.\n";
    std::cout << "-----------------------------------------\n";

    return cout;
}
