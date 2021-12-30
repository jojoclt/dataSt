#include "station.hpp"

#include <iostream>

Station::Station(int sID, int elec, int lady, int road) : sID(sID) {
    bikeCount[0] = elec, bikeCount[1] = lady, bikeCount[2] = road;
    bikeID[0] = fillBike(sID, elec), bikeID[1] = fillBike(sID, lady), bikeID[2] = fillBike(sID, road);
}
Status Station::Rent(int bt, int ID, int time) {
    // Check if bike is available
    if (bikeCount[bt]) {
        user[ID].Rent(bt, bikeID[bt][0], time);
        RemoveBike(bt);
        return Accept;
    }
    return Reject;
}
void Station::Return(int ID, int time) {
    // TODO
    addBike(user[ID].type, user[ID].bikeNo);
    user[ID].Return();
    return;
}
pii* Station::fillBike(int ID, int x) {
    pii* arr = new pii[x];
    for (int i = 0; i < x; i++) arr[i] = {ID, i};
    return arr;
}

void Station::RemoveBike(int bt) {
    bikeCount[bt]--;
    for (int i = 0; i < bikeCount[bt]; i++) {
        bikeID[bt][i] = bikeID[bt][i + 1];
    }
}
void Station::addBike(int type, pii bike) {
    int l = 0, r = bikeCount[type] - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        std::cout << bikeID[type][mid].first << " " << bikeID[type][mid].second << std::endl;
        if (bike < bikeID[type][mid]) {
            r = mid - 1;
        } else
            l = mid + 1;
    }
    std::cout << l;
}

int main() {
    Station* station = new Station(0, 2, 3, 4);
    station->RemoveBike(2);
    station->printBike(2);
    station->addBike(2, {-1, 1});
}