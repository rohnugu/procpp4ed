// main_AirlineTicket.cpp
// gcc -std=c++17 -o airlineex AirlineTicket.cpp airlineex.cpp -lstdc++
#include "AirlineTicket.h"
#include <memory> // for make_unique
#include <iostream>

int main()
{
    AirlineTicket myTicket; // Stack-based AirlineTicket
    myTicket.setPassengerName("Sherman T. Socketwrench");
    myTicket.setNumberOfMiles(700);
    double cost = myTicket.calculatePriceInDollars();
    std::cout << "This ticket will cost $" << cost << std::endl;

    // Heap-based AirlineTicket with smart pointer
    auto myTicket2 = std::make_unique<AirlineTicket>();
    myTicket2->setPassengerName("Laudimore M. Hallidue");
    myTicket2->setNumberOfMiles(2000);
    myTicket2->setHasEliteSuperRewardsStatus(true);
    double cost2 = myTicket2->calculatePriceInDollars();
    std::cout << "This other ticket will cost $" << cost2 << std::endl;
    // No need to delete myTicket2, happens automatically

    // Heap-based AirlineTicket without smart pointer (not recommended)
    AirlineTicket* myTicket3 = new AirlineTicket();
    // ... Use ticket 3
    delete myTicket3; // delete the heap object!

    return 0;
}
