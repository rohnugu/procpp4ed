// AirlineTicket.h
#ifndef AIRLINETICKET_H
#define AIRLINETICKET_H

#include <string>

class AirlineTicket
{
  public:
    AirlineTicket(); // 생성자 (constructor)
    ~AirlineTicket(); // 소멸자 (destructor)

    double calculatePriceInDollars() const;

    const std::string& getPassengerName() const;
    void setPassengerName(const std::string& name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(int miles);

    bool hasEliteSuperRewardsStatus() const;
    void setHasEliteSuperRewardsStatus(bool status);
  private:
    std::string mPassengerName;
    int mNumberOfMiles;
    bool mHasEliteSuperRewardsStatus;
};

#endif // end of AIRLINETICKET_H