
#include <iostream>
#include <iomanip>
#include "RideRequest.h"
using namespace std;
double g_taxrate = 0;
double g_discount = 0;
namespace sdds {
int RideRequest::s_currentDay = 1;
bool enter = false;
// Default constructor
RideRequest::RideRequest() {
    m_customerName[0] = '\0';
    m_rideDescription[0] = '\0';
    m_price = 0.0;
    m_discount = false;
    m_counter = 0;
}

void RideRequest::read(std::istream& is) {
    // Read customer name, ride description, price, and discount status from input stream
    is.getline(m_customerName, MAX_NAME_LENGTH + 1, ',');
    is.getline(m_rideDescription, MAX_DESCRIPTION_LENGTH + 1, ',');
    is >> m_price;
    m_counter++;
    is.ignore(); 
    char discountStatus = {};
    is >> discountStatus;
    m_discount = (discountStatus == 'Y');
    
}
void RideRequest::setCurrentDay(int day) {
    s_currentDay = day;
}


// Display function
bool RideRequest::display() const {
    
    const int COUNTER_WIDTH = 2;
    const int NAME_WIDTH = 10;
    const int DESCRIPTION_WIDTH = 25;
    const int DISCOUNT_WIDTH = 13;
    const int PRICE_WIDTH = 12;
    double priceWithTax = 0;
    cout << left << setw(COUNTER_WIDTH)<< m_counter << ". ";
    
    if (m_customerName[0] != '\0') {
        cout << left << setw(NAME_WIDTH) << m_customerName;
        cout << "|" << left << setw(DESCRIPTION_WIDTH) << m_rideDescription;
        cout << "|" << fixed << setw(PRICE_WIDTH) << setprecision(2);
        priceWithTax = m_price * (1 + g_taxrate);
        cout << priceWithTax <<"|";
    }
    else {
        // Print "No Ride Request" when there is no ride request
        cout << "No Ride Request" << endl;
        return false;
    }
    if (enter && m_discount){
        cout << setw(13) << right << (m_price *(1.14) / 1.20);
        enter = false;
    }
    if (!enter && m_discount){
        cout << setw(13) << right << (m_price *(1.13) / 1.15);
        enter = true;
    }

    
    else {
        cout << right << setw(DISCOUNT_WIDTH) << " ";
    }
    cout << endl;
    return true;
    
}


}




