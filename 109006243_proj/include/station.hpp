#ifndef STATION_H
#define STATION_H

#include <iomanip>
#include <iostream>

#include "status.hpp"
#include "user.hpp"
#include "vector.hpp"
static int money = 0;
class Station {
   public:
    // sID bikeID
    Vector<int> bikeID[3];
    Station() : sID(-1) {}
    Station(int sID, int elec, int lady, int road);
    // Station(const Station &s);
    // Station &operator=(const Station &s);
    int getLatestBike(int bt);
    Status Rent(int bt, int ID, int time);
    void Return(int uID, int time);
    void printBike(int bt)
    {
        for (int i = 0; i < bikeID[bt].size(); i++) {
            std::cout << bikeID[bt][i] << " ";
        }
        std::cout << "\n";
    }
    void printStation_1()
    {
        if (sID != -1) {
            std::cout << sID << ":\n";
            std::cout << "electric: ";
            printBike(0);
            std::cout << "lady: ";
            printBike(1);
            std::cout << "road: ";
            printBike(2);
        }
    }

   public:
    int sID;
    int toBike(int sID, int x) { return sID * 100 + x; }
    Vector<int> fillBike(int sID, int x);
    void RemoveBike(int bt);
    void addBike(int bt, int bike);
};
#endif