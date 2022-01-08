#include "station.hpp"

#include <iostream>

#include "user.hpp"

extern User user[100000];

Station::Station(int sID, int elec, int lady, int road) : sID(sID) {
    maxTransfer[0] = elec, maxTransfer[1] = lady, maxTransfer[2] = road;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++) costExpected[i][j] = 0;
    size[0] = elec, size[1] = lady, size[2] = road;
    bikeID[0].heap = fillBike(sID, elec);
    bikeID[1].heap = fillBike(sID, lady);
    bikeID[2].heap = fillBike(sID, road);
}
Station::~Station() {}
Status Station::Rent(int bt, int ID, int timeIn, int disc, int wait) {
    // Check if bike is available
    if (!bikeID[bt].empty()) {
        user[ID].Rent(bt, bikeID[bt].top(), timeIn, sID, disc, wait);
        bikeID[bt].pop();
        maxTransfer[bt] = std::min(maxTransfer[bt], bikeID[bt].size());
        return Accept;
    } else
        user[ID].type = bt, user[ID].sOut = sID, user[ID].timeSt = timeIn;
    return Reject;
}
bool Station::Return(int ID, int time) {
    if (!user[ID].isRent) {
        user[ID].sIn = sID, user[ID].timeEnd = time;
        return false;
    }
    addBike(user[ID].type, user[ID].bikeNo);
    money += user[ID].Return(time, sID);
    maxTransfer[user[ID].type] =
        std::min(maxTransfer[user[ID].type], bikeID[user[ID].type].size());
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