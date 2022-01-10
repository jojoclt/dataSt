#ifndef STATION_H
#define STATION_H

#include <iomanip>
#include <iostream>

#include "minheap.hpp"
#include "pricing.hpp"
#include "status.hpp"
#include "user.hpp"
#include "vector.hpp"

class Station {
   public:
    int costExpected[3] = {};  // transfer for Type and discount
    int size[3];
    int maxTransfer[3] = {};
    int transferedTime[3];
    int waitCount[3] = {};
    MinHeap<int> bikeID[3];
    Station() : sID(-1) {}
    Station(int sID, int elec, int lady, int road);
    ~Station();

    int getLatestBike(int bt);
    Status Rent(int bt, int ID, int time, bool disc = false, int wait = 0);
    bool Return(int uID, int time);
    void printBike(int bt, std::ostream& os);
    void printStation_1(std::ostream& os);

   public:
    int sID;
    int toBike(int sID, int x) { return sID * 100 + x; }
    Vector<int> fillBike(int sID, int x);
    void addBike(int bt, int bike);
};
#endif