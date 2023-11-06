#include <vector>
#include <string>
#include <fstream>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"


namespace sdds
{
    void Filesystem::addSrc(std::string& path, const std::string& content)
    {
        bool flag  = false;
        Directory* current = m_root;
        do
        {
            flag = path.find("/") == std::string::npos;
            if (!flag )
            {
                std::string dirName = path.substr(0, path.find("/") + 1);
                Directory* newDir = nullptr;
                path = path.substr(path.find("/") + 1);
                newDir = dynamic_cast<Directory*>(m_root->find(dirName));
                if (!newDir)
                {
                    newDir = new Directory(dirName);
                    *current += newDir;
                }
                current = newDir;
            }
            else if(content.length() && !m_root->find(path))
            {
                *current += new File(path.c_str(), content.c_str());
            }
        } while (!flag );
    }
    Filesystem::Filesystem(const char* fileName, const std::string& rootName)
    {
        m_root = new Directory(rootName);
        m_current = m_root;

        std::fstream file(fileName);
        if (file)
        {
            std::string line{};
            do
            {
                bool isFile{};
                getline(file, line);
                isFile = line.find('|') != std::string::npos;
                if (isFile)
                {   //toknized trimming
                    std::string path = line.substr(0, line.find('|'));
                    trimString(path);
                    std::string contents = line.substr(line.find('|') + 1);
                    trimString(contents);
                    addSrc(path, contents);
                }
                else
                {
                    trimString(line);
                    addSrc(line);
                }

            } while (file);
        }
        else
        {
            delete m_root;
            throw "ERROR READING FILE";
        }
    }

    Filesystem& Filesystem::operator+=(Resource* res)
    {
        *m_current += res;
        return *this;
    }
    Directory* Filesystem::change_directory(const std::string& dirName)
    {
        if (dirName.length())
        {
            Resource* targetDir = m_root->find(dirName, std::vector<OpFlags>{OpFlags::RECURSIVE});
            if (targetDir && targetDir->type() == NodeType::DIR)
            {
                m_current = dynamic_cast<Directory*>(targetDir);
            }
            else
            {
                throw std::invalid_argument("Cannot change directory! " + dirName + " not found!");
            }
        }
        else
        {
            m_current = m_root;
        }
        return m_current;
    }

    Directory* Filesystem::get_current_directory() const
    {
        return m_current;
    }

    void trimString(std::string& source)
    {
        size_t begin = source.find_first_not_of(" ");
        size_t end = source.find_last_not_of(" ");
        std::string res{};
        if (begin != std::string::npos && end != std::string::npos)
        {
            res = source.substr(begin, end - begin + 1);
        }
        else
        {
            res = "";
        }
        source = res;
    }

    Filesystem::~Filesystem()
    {
        delete m_root;
        m_current = nullptr;
    }
}
