//
//  File .h
//  p1
//
//  Created by aydin ghorbani on 2023-11-02.
//

#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <iostream>
#include <fstream>
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
