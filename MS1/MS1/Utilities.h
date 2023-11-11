//
//  Utilities.h
//  MS1
//
//  Created by aydin ghorbani on 2023-11-08.
//

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
    class Utilities {
        size_t m_widthField;
        static char m_delimiter;

    public:
        Utilities();
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    };
}

#endif /*SDDS_UTILITIES_H*/
