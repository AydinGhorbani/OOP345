#include <algorithm>
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
}
