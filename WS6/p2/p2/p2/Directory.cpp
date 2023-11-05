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
        // Check for existing resources with the same name
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

void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        Resource* resource = find(name);

        if (!resource) {
            throw std::invalid_argument(name + " does not exist in " + m_name);
        }

        if (resource->type() == NodeType::DIR) {
            if (std::find(flags.begin(), flags.end(), OpFlags::RECURSIVE) == flags.end()) {
                throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
        }

        m_contents.erase(std::remove(m_contents.begin(), m_contents.end(), resource), m_contents.end());
        delete resource;
    }

void Directory::display(std::ostream& os, const std::vector<FormatFlags>& formatFlags) const {
        os << "Total size: " << size() << " bytes" << std::endl;
        for (const auto& resource : m_contents) {
            os << (resource->type() == NodeType::DIR ? "D" : "F") << " | " << std::left << std::setw(15) << resource->name();
            if (std::find(formatFlags.begin(), formatFlags.end(), FormatFlags::LONG) != formatFlags.end()) {
                os << " | " << std::setw(2) << resource->count() << " | " << std::setw(10) << resource->size() << " bytes";
            }
            os << std::endl;
        }
    }
}
