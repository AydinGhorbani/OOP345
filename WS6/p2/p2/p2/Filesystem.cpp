//
//  Filesystem.cpp
//  p2
//
//  Created by aydin ghorbani on 2023-11-04.
//

// Filesystem.cpp
#include "Filesystem.h"
#include "File.h"
#include "Flags.h"
#include <fstream>
#include <sstream>
#include <vector>

namespace sdds {
Filesystem::Filesystem(const std::string& filename, const std::string& rootDirectoryName) {
    m_root = new Directory(rootDirectoryName);
    m_current = m_root;

    std::ifstream file(filename);
    if (!file) {
        throw std::invalid_argument("Filesystem not created with an invalid filename.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string resourcePath = tokenizeAndTrim(line);
        std::string resourceContents;

        size_t pipePos = resourcePath.find('|');
        if (pipePos != std::string::npos) {
            resourceContents = tokenizeAndTrim(resourcePath.substr(pipePos + 1));
            resourcePath = tokenizeAndTrim(resourcePath.substr(0, pipePos));
        }

        if (!resourcePath.empty()) {
            createDirectoryTree(resourcePath);
            if (!resourceContents.empty()) {
                *m_current += new File(resourcePath, resourceContents);
            }
        }
    }
}

Filesystem::~Filesystem() {
    delete m_root;
}

Filesystem& Filesystem::operator+=(Resource* resource) {
    *m_current += resource;
    return *this;
}

Directory* Filesystem::change_directory(const std::string& dirName) {
    Directory* newDir = dynamic_cast<Directory*>(m_current->find(dirName));

    if (!newDir) {
        throw std::invalid_argument("Directory not found: " + dirName);
    }

    m_current = newDir;
    return m_current;
}


Directory* Filesystem::get_current_directory() const {
    return m_current;
}


std::string Filesystem::tokenizeAndTrim(const std::string& str) {
    size_t firstNonSpace = str.find_first_not_of(" ");
    size_t lastNonSpace = str.find_last_not_of(" ");

    if (firstNonSpace == std::string::npos) {
        return "";
    }

    return str.substr(firstNonSpace, lastNonSpace - firstNonSpace + '/');
}


Directory* Filesystem::createDirectoryTree(const std::string& path) {
    std::istringstream ss(path);
    std::string directoryName;
    Directory* currentDir = m_root;

    while (std::getline(ss, directoryName, '/')) {
        Directory* subDir = dynamic_cast<Directory*>(currentDir->find(directoryName));
        if (!subDir) {
            subDir = new Directory(directoryName);
            *currentDir += subDir;
        }
        currentDir = subDir;
    }
    return currentDir;
}

}
