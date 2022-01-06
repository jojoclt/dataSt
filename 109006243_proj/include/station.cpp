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
Status Station::Rent(int bt, int ID, int time) {
    // Check if bike is available
    if (bikeID[bt].size()) {
        user[ID].Rent(bt, bikeID[bt].extractMax(), time, sID);
        return Accept;
    }
    return Reject;
}
void Station::Return(int ID, int time) {
    if (user[ID].type == -1) return;
    addBike(user[ID].type, user[ID].bikeNo);
    user[ID].Return(time, sID);
    return;
}
Vector<int> Station::fillBike(int ID, int x) {
    Vector<int> arr(100);
    for (int i = x - 1; i >= 0; i--) {
        // already heap in bottom up fashion
        arr.push_back(toBike(ID, i));
    }

    return arr;
}

void Station::addBike(int type, int bike) {
    bikeID[type].insert(bike);
}

void Station::printBike(int bt, std::ostream& os) {
    Vector<int> a(50);
    while (bikeID[bt].size()) a.push_back(bikeID[bt].extractMax());
    for (int i = a.size() - 1; i >= 0; i--) os << a[i] << " ";
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
// int main()
// {
//     Station* station = new Station(0, 2, 3, 4);
//     //     station->RemoveBike(2);
//     station->printBike(2);
//     //     station->addBike(2, {-1, 1});
// }