#ifndef STATION_H
#define STATION_H

#include "bike.hpp"
#include "status.hpp"
#include "uid.hpp"

class Station {
   public:
    int bikeCount[3];
    int *bikeID[3];
    Station() {}
    Station(int elec, int lady, int road);
    // Station(const Station &s);
    // Station &operator=(const Station &s);
    int getLatestBike(int bt);
    Status Rent(int bt, int uID, int time);
    void Return(int uID, int time);

   private:
    int *fillBike(int x);
    void RemoveBike(int bt);
    void addBike(int bt);
};
#endif