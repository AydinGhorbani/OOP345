/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 Repository : https://github.com/AydinGhorbani/OOP345/
 
 Please find every commit (Over 50 throughout the semester) made in this link, including the debugging techniques used to develop this project.
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that I searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include <ostream>
#include <string>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {

    enum class OrderStatus {
        OrderFilled,
        ItemFilled,
        InsufficientQuantity
    };

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_nextWorkStation = nullptr;

    public:
        Workstation(const std::string&);

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        //debugging statments over all updates
        OrderStatus evaluateOrderStatus();
        void moveOrderToNextStation();
        void moveOrderToIncompleteQueue();
        
        // Copy operations are deleted
        Workstation(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation& operator=(Workstation&&) = delete;


    };
}

#endif
