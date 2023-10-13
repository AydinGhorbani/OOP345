/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include "Cheese.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>


namespace sdds {

    Cheese::Cheese() : name("NaC           "), weight(0), price(0.0), features("") {}

    Cheese::Cheese(const std::string& str) : name("NaC - Not a Cheese"), weight(0), price(0.0), features("") {
        std::istringstream iss(str);
        std::string token;

        std::getline(iss, token, ',');
        if (!token.empty()) {
            name = token;
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
            // Remove trailing spaces
        }

        std::getline(iss, token, ',');
        if (!token.empty()) {
            weight = std::stoi(token);
        }

        std::getline(iss, token, ',');
        if (!token.empty()) {
            price = std::stod(token);
        }

        std::getline(iss, features);
        features.erase(0, features.find_first_not_of(" \t"));
        features.erase(features.find_last_not_of(" \t") + 1);
        // Remove trailing spaces
    }

    Cheese Cheese::slice(size_t weight) {
        if (weight <= static_cast<size_t>(this->weight)) {
            // create a new Cheese object with the sliced weight
            Cheese slicedCheese(*this);
            slicedCheese.weight = weight;
            this->weight -= weight;
            return slicedCheese;
        }
        else {
            return Cheese();
        }
    }

    //https://stackoverflow.com/questions/40937557/remove-spaces-from-string-before-period-and-comma

    std::ostream& operator<<(std::ostream& os, const Cheese& cheese) {
        
        os << "|";
        os << std::left << std::setw(21) << cheese.name << "|";
        os << std::left << std::setw(5) << cheese.weight << "|";
        os << std::fixed << std::setprecision(2) << std::setw(5) << cheese.price << "|";
        // remove leading and trailing spaces within each feature and remove the comma
        std::string features_without_commas;
        std::istringstream iss(cheese.features);
        std::string feature;
        while (std::getline(iss, feature, ',')) {
            // Trim leading and trailing spaces
            //next three lines is copied directly from stackoverflow.
            feature = std::regex_replace(feature, std::regex("^\\s+|\\s+$"), "");
            features_without_commas += feature + ' ';
        }

        // remove the trailing space
        if (!features_without_commas.empty()) {
            features_without_commas.pop_back();
            // remove last space
        }

        os << std::right << std::setw(33) << features_without_commas << " |";
        os << "\n";
        return os;
        
        //this code also works. spliting the get line fetures into two
        //different strings so we dont have to clear the space between.
        
        //commented code might be slightely slower than the first one
        // because of allocating more stirngs for each irritation of os
        
        // i couldnt make it work though!
        
        
        /*
         std::istringstream iss(cheese.features);
         std::string feature1, feature2, feature3;
         if (std::getline(iss, feature1, ',')) {
             feature1 = feature1.substr(feature1.find_first_not_of(" \t"), feature1.find_last_not_of(" \t") + 1);
         }
         if (std::getline(iss, feature2, ',')) {
             feature2 = feature2.substr(feature2.find_first_not_of(" \t"), feature2.find_last_not_of(" \t") + 1);
         }
         if (std::getline(iss, feature3)) {
             feature3 = feature3.substr(feature3.find_first_not_of(" \t"), feature3.find_last_not_of(" \t") + 1);
         }
         */
        
        //
        
    }

} 

