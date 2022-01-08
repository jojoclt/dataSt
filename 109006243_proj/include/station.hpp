#ifndef STATION_H
#define STATION_H

#include <iomanip>
#include <iostream>

#include "minheap.hpp"
#include "pii.hpp"
#include "status.hpp"
#include "user.hpp"
#include "vector.hpp"

class Station {
   public:
    int costExpected[3];  // transfer for Type
    int size[3];
    int maxTransfer[3];
    MinHeap<pii> waitList[3];  // Plz reverse the minus for MAXHEAP
    MinHeap<int> bikeID[3];
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
    int stockAtTime[1442][3] = {};
    int sID;
    int toBike(int sID, int x) { return sID * 100 + x; }
    Vector<int> fillBike(int sID, int x);
    void addBike(int bt, int bike);
};
#endif