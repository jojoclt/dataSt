#include "station.hpp"

#include <iostream>

#include "uid.hpp"

Station::Station(int elec, int lady, int road) {
    bikeCount[0] = elec, bikeCount[1] = lady, bikeCount[2] = road;
    bikeID[0] = fillBike(elec), bikeID[1] = fillBike(lady), bikeID[2] = fillBike(road);
}
Status Station::Rent(int bt, int uID, int time) {
    // Check if bike is available
    if (bikeCount[bt]) {
        userID[uID].Rent(bt, bikeID[bt][0], time);
        RemoveBike(bt);
        return Accept;
    }
    return Reject;
}
void Station::Return(int ID, int time) {
    addBike(userID[ID].type);
    return;
}
int* Station::fillBike(int x) {
    int* arr = new int[x];
    for (int i = 0; i < x; i++) arr[i] = i;
    return arr;
}

void Station::RemoveBike(int bt) {
    bikeCount[bt]--;
    for (int i = 0; i < bikeCount[bt]; i++) {
        bikeID[bt][i] = bikeID[bt][i + 1];
    }
}
void Station::addBike(int bt, int) {
    int l = 0, r = bikeCount[x] - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (bikeID[x][mid])
    }
}