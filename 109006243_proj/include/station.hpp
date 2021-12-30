#ifndef STATION_H
#define STATION_H

#include <iomanip>
#include <iostream>

#include "pii.hpp"
#include "status.hpp"
#include "user.hpp"
#include "vector.hpp"
static int money = 0;
class Station {
   public:
    int bikeCount[3];
    // sID bikeID
    Vector<pii> bikeID[3];
    Station() {}
    Station(int sID, int elec, int lady, int road);
    // Station(const Station &s);
    // Station &operator=(const Station &s);
    int getLatestBike(int bt);
    Status Rent(int bt, int ID, int time);
    void Return(int uID, int time);
    void printBike(int bt) {
        for (int i = 0; i < bikeCount[bt]; i++) {
            std::cout << bikeID[bt][i].first << std::setfill('0') << std::setw(2) << bikeID[bt][i].second << " ";
        }
        std::cout << "\n";
    }

   public:
    int sID;
    Vector<pii>& fillBike(Vector<pii>& arr, int sID, int x);
    void RemoveBike(int bt);
    void addBike(int bt, pii bike);
};
#endif