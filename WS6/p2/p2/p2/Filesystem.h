//
//  Filesystem.h
//  p2
//
//  Created by aydin ghorbani on 2023-11-04.
//

#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include "Directory.h"
#include "Resource.h"
#include <string>

namespace sdds {
    class Filesystem {
    private:
        Directory* m_root;
        Directory* m_current;
        
        std::string tokenizeAndTrim(const std::string& str);
        Directory* createDirectoryTree(const std::string& path);
    public:
        Filesystem(const std::string& filename, const std::string& rootDirectoryName = "");
        ~Filesystem();
        Filesystem& operator+=(Resource* resource);
        Directory* change_directory(const std::string& dirName = "");
        Directory* get_current_directory() const;
        
        
        
        Filesystem& operator=(const Filesystem*) = delete;
        Filesystem(const Filesystem&) = delete;
        Filesystem(const Filesystem&&) = delete;
        Filesystem& operator=(const Filesystem&&) = delete;

    };
}



#endif //SDDS_FILESYSTEM_H
