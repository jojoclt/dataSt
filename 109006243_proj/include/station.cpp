#include "station.hpp"

#include <iostream>

#include "user.hpp"

extern User user[100000];
Station::Station(int sID, int elec, int lady, int road) : sID(sID) {
    bikeID[0] = fillBike(sID, elec);
    bikeID[1] = fillBike(sID, lady);
    bikeID[2] = fillBike(sID, road);
}
Station::~Station() {}
Status Station::Rent(int bt, int ID, int time) {
    // Check if bike is available
    if (bikeID[bt].size()) {
        user[ID].Rent(bt, bikeID[bt][0], time, sID);
        RemoveBike(bt);
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
    // Vector<int> arr(x);
    Vector<int> arr;
    for (int i = 0; i < x; i++) {
        arr.push_back(toBike(ID, i));
    }

    return arr;
}

void Station::RemoveBike(int bt) {
    for (int i = 0; i < bikeID[bt].size() - 1; i++) {
        bikeID[bt][i] = bikeID[bt][i + 1];
    }
    bikeID[bt].pop_back();
}
void Station::addBike(int type, int bike) {
    int l = 0, r = bikeID[type].size() - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        // std::cout << bikeID[type][mid].first << " " <<
        // bikeID[type][mid].second << std::endl;
        if (bike < bikeID[type][mid]) {
            r = mid - 1;
        } else
            l = mid + 1;
    }
    // std::cout << l << "y";
    bikeID[type].insert(l, bike);
}

void Station::printBike(int bt) {
    if (!bikeID[bt].size()) std::cout << "0";
    for (int i = 0; i < bikeID[bt].size(); i++) {
        std::cout << bikeID[bt][i] << " ";
    }
    std::cout << "\n";
}
void Station::printStation_1() {
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
// int main()
// {
//     Station* station = new Station(0, 2, 3, 4);
//     //     station->RemoveBike(2);
//     station->printBike(2);
//     //     station->addBike(2, {-1, 1});
// }