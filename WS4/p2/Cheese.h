/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds {
    class Cheese {
        std::string name;
        int weight;
        double price;
        std::string features;

    public:
        Cheese();
        Cheese(const std::string& str);
        Cheese slice(size_t weight);
        // Add getter functions for name, weight, price, and features
        friend std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
        std::string getName() const {
               return name;
           }
           int getWeight() const {
               return weight;
           }
           double getPrice() const {
               return price;
           }
           std::string getFeatures() const {
               return features;
           }
       friend std::ostream& operator<<(std::ostream& os, const sdds::Cheese& cheese);

    };
}



#endif //SDDS_CHEESE_H
