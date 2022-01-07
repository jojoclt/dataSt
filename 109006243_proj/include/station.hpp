#ifndef STATION_H
#define STATION_H

#include <iomanip>
#include <iostream>

#include "minheap.hpp"
#include "status.hpp"
#include "user.hpp"
#include "vector.hpp"

class Station {
   public:
    // sID bikeID
    MinHeap bikeID[3];
    Station() : sID(-1) {}
    Station(int sID, int elec, int lady, int road);
    ~Station();
    // Station(const Station &s);
    // Station &operator=(const Station &s);
    int getLatestBike(int bt);
    Status Rent(int bt, int ID, int time, int disc = 1, int wait = 0);
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