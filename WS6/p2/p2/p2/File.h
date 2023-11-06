/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <string>
#include "Flags.h"
#include "Resource.h"

namespace sdds {
    class File : public Resource {
        std::string m_contents;

    public:
        File(const std::string& name, const std::string& contents = "");
        void update_parent_path(const std::string& parentPath);
        std::string name() const;
        int count() const;
        std::string path() const;
        size_t size() const;
        NodeType type() const;
    };
}


#endif /* SDDS_FILE_H */
