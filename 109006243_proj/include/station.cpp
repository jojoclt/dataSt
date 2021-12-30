#include "station.hpp"

#include <iostream>

Station::Station(int sID, int elec, int lady, int road) : sID(sID) {
    bikeCount[0] = elec, bikeCount[1] = lady, bikeCount[2] = road;
    bikeID[0] = fillBike(bikeID[0], sID, elec), bikeID[1] = fillBike(bikeID[1], sID, lady), bikeID[2] = fillBike(bikeID[2], sID, road);
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
Vector<pii>& Station::fillBike(Vector<pii>& arr, int ID, int x) {
    arr.push_back(pii(1, 1));
    std::cout << arr.size();
    //  for (int i = 0; i < x; i++) {
    //      pii t = {ID, i};
    //      arr.push_back(t);
    //  }
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
        pii t = bikeID[type][mid];
        // std::cout << bikeID[type][mid].first << " " << bikeID[type][mid].second << std::endl;
        if (bike < t) {
            r = mid - 1;
        } else
            l = mid + 1;
    }
    std::cout << l;
}

// int main() {
//     Station* station = new Station(0, 2, 3, 4);
//     station->RemoveBike(2);
//     station->printBike(2);
//     station->addBike(2, {-1, 1});
// }