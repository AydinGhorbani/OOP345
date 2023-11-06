/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#include <algorithm>
#include <iomanip>
#include "Directory.h"

namespace sdds {
    Directory::Directory(const std::string& name) {
        m_name = name;
    }

    void Directory::update_parent_path(const std::string& path) {
        m_parent_path = path;
        for (Resource* resource : m_contents) {
            resource->update_parent_path(path + m_name);
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        return m_parent_path + m_name;
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const {
        size_t totalSize = 0;
        for (const Resource* resource : m_contents) {
            totalSize += resource->size();
        }
        return totalSize;
    }

    Directory& Directory::operator+=(Resource* resource) {
        
        Resource* existingResource = find(resource->name());

        if (existingResource) {
            throw std::invalid_argument("Resource with the same name already exists in this directory.");
        }

        m_contents.push_back(resource);
        resource->update_parent_path(path());
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        for (Resource* resource : m_contents) {
            if (resource->name() == name) {
                return resource;
            }
        }

        // If the RECURSIVE flag is set attempt to find the resource in subdirectories
        if (std::find(flags.begin(), flags.end(), sdds::OpFlags::RECURSIVE) != flags.end()){
            for (Resource* resource : m_contents) {
                if (resource->type() == NodeType::DIR) {
                    Directory* subDirectory = dynamic_cast<Directory*>(resource);
                    if (subDirectory) {
                        Resource* foundResource = subDirectory->find(name, flags);
                        if (foundResource) {
                            return foundResource;
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    Directory::~Directory() {
        for (Resource* resource : m_contents) {
            delete resource;
        }
    }
void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags)
{
    bool recursive = std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) != flags.end();
    
    Resource* result = find(name, flags);
    if (!result)
    {
        throw std::invalid_argument(name + " does not exist in " + m_parent_path);
    }
    
    size_t resultIndex = std::distance(m_contents.begin(), std::find(m_contents.begin(), m_contents.end(), result));
    
    if (result->type() == NodeType::DIR && !recursive)
    {
        throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
    }
    
    delete result;
    m_contents.erase(m_contents.begin() + resultIndex);
}

void Directory::display(std::ostream& os, const std::vector<FormatFlags>& flags) const
{
    bool longFlag = std::find(flags.begin(), flags.end(), FormatFlags::LONG) != flags.end();
    
    os << "Total size: " << std::setw(2) << size() << " bytes\n";
    
    for (const auto& res : m_contents)
    {
        os << (res->type() == NodeType::FILE ? "F | " : "D | ");
        os << std::setw(15) << std::left << res->name() << " |";
        
        if (longFlag)
        {
            os << "  " << std::setw(2) << (res->type() == NodeType::DIR ? std::to_string(res->count()) : "") << "|";
            os << std::setw(5) << std::right << res->size() << " bytes | " << std::endl;
        }
        else
        {
            os << std::endl;
        }
    }
}

}
