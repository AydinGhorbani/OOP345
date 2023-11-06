/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include "Resource.h"
#include <vector>
#include <string>

namespace sdds {
    class Directory : public Resource {
        std::vector<Resource*> m_contents;

    public:
        Directory(const std::string& name);
        void update_parent_path(const std::string& path) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        Directory& operator+=(Resource* resource);
        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
        void remove(const std::string& name, const std::vector<OpFlags>& flags = {});
        void display(std::ostream& os, const std::vector<FormatFlags>& formatFlags = {}) const;
        ~Directory();
        
        // Disable copy/move operations
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };
}



#endif // DIRECTORY_H
