
#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>
extern double g_taxrate;
extern double g_discount;
namespace sdds {
    //static double g_taxrate = 0;
    //static double g_discount = 0;
    class RideRequest {

        static const int MAX_NAME_LENGTH = 10;
        static const int MAX_DESCRIPTION_LENGTH = 25;
        static int s_currentDay;
        char m_customerName[MAX_NAME_LENGTH + 1]{};
        char m_rideDescription[MAX_DESCRIPTION_LENGTH + 1]{};
        double m_price = 0;
        bool m_discount = true;
        int m_counter = 0;

    public:
        static void setCurrentDay(int day);
        RideRequest(); // Default constructor
        void read(std::istream& is);
        bool display() const;
    };

}

#endif //SDDS_RIDEREQUEST_H
