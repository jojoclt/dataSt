#ifndef STATION_H
#define STATION_H

#include "bike.hpp"
#include "bikeType.hpp"
#include "uid.hpp"

class Station {
   public:
    int elecAmt, ladyAmt, roadAmt;
    int *elecID, *ladyID, *roadID;
    Station();
    Station(int elec, int lady, int road);
    // Station(const Station &s);
    // Station &operator=(const Station &s);
    int getLatestBike(int bt);
    bool Rent(int bt, int uID, int time);
    void Return(int uID, int time);
};
#endif