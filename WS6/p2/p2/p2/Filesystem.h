/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <string>
#include "Directory.h"

namespace sdds
{
    class Filesystem
    {
        Directory* m_root{};
        Directory* m_current{};
        
        //private additional functions...

        void addSrc(std::string&,const std::string& = "");
        
    public:
        Filesystem(const char*, const std::string& = std::string());

        Filesystem& operator+=(Resource*);
        Directory* change_directory(const std::string& = "");
        Directory* get_current_directory() const;
        ~Filesystem();

        
        Filesystem& operator=(Filesystem&) = delete;
        Filesystem(Filesystem&) = delete;
        
        //the move operations below dont have any decleation as we dont need.
        Filesystem(Filesystem&&) noexcept;
        Filesystem& operator=(Filesystem&&) noexcept;
    };

    void trimString(std::string&);
}

#endif
