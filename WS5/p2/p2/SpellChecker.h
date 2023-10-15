#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <string>
#include "Collection.h"

namespace sdds {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
    public:
 
        SpellChecker(const char* filename);
        void operator()(std::string& text)const;
        void showStatistics(std::ostream& os) const;
    };
}

#endif 
