#include "File.h"
#include "Flags.h"

namespace sdds {
    File::File(const std::string& name, const std::string& contents) : m_contents(contents) {
        m_name = name;
    }

    void File::update_parent_path(const std::string& parentPath) {
        m_parent_path = parentPath;
    }

    std::string File::name() const {
        return m_name;
    }

    int File::count() const {
        return -1; // Files do not have counts
    }

    std::string File::path() const {
        return m_parent_path + m_name;
    }

    size_t File::size() const {
        return m_contents.size();
    }

    NodeType File::type() const {
        return NodeType::FILE;
    }
}  // namespace sdds
