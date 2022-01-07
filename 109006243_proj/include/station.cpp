#include "station.hpp"

#include <iostream>

#include "user.hpp"

extern User user[100000];

Station::Station(int sID, int elec, int lady, int road) : sID(sID) {
    bikeID[0].heap = fillBike(sID, elec);
    bikeID[1].heap = fillBike(sID, lady);
    bikeID[2].heap = fillBike(sID, road);
}
Station::~Station() {}
Status Station::Rent(int bt, int ID, int time, int disc, int wait) {
    // Check if bike is available
    if (bikeID[bt].size()) {
        user[ID].Rent(bt, bikeID[bt].top(), time, sID, disc, wait);
        bikeID[bt].pop();
        return Accept;
    }
    return Reject;
}
bool Station::Return(int ID, int time) {
    if (!user[ID].isRent) return false;
    addBike(user[ID].type, user[ID].bikeNo);
    user[ID].Return(time, sID);
    return true;
}
Vector<int> Station::fillBike(int ID, int x) {
    Vector<int> arr(100);
    for (int i = 0; i < x; i++) {
        // already heap in bottom up fashion
        arr.push_back(toBike(ID, i));
    }

    return arr;
}

void Station::addBike(int type, int bike) { bikeID[type].push(bike); }

void Station::printBike(int bt, std::ostream& os) {
    while (!bikeID[bt].empty()) {
        os << bikeID[bt].top() << " ";
        bikeID[bt].pop();
    }
    os << "\n";
}
void Station::printStation_1(std::ostream& os) {
    if (sID != -1) {
        os << sID << ":\n";
        os << "electric: ";
        printBike(0, os);
        os << "lady: ";
        printBike(1, os);
        os << "road: ";
        printBike(2, os);
    }
}
// int main() {
//     Station* station = new Station(0, 2, 3, 4);
//     while (!station->bikeID[2].empty()) {
//         std::cout << station->bikeID[2].top() << "\n";
//         station->bikeID[2].pop();
//     }
// }