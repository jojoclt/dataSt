#include <fstream>
#include <iostream>
#include <string>

#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/uid.hpp"

using namespace std;

// g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
Station station[105];

int toBike(string b) {
    if (b == "electric") return 0;
    if (b == "lady") return 1;
    if (b == "road") return 2;
    return 0;
}
int main() {
    ifstream input;

    input.open("./test_case/map.txt");
    if (!input.is_open()) cout << "<<MAP NOT OPENED>>", exit(0);

    initMap();
    while (input) {
        int s1, s2, dist;
        input >> s1 >> s2 >> dist;
        map[s1][s2] = map[s2][s1] = dist;
    }
    calcDist();
    input.close();

    input.open("./test_case/station.txt");
    if (!input.is_open()) cout << "<<STATION NOT OPENED>>", exit(0);

    while (input) {
        int ID, elecAmt, ladyAmt, roadAmt;
        input >> ID >> elecAmt >> ladyAmt >> roadAmt;
        station[ID] = Station(elecAmt, ladyAmt, roadAmt);
    }
    input.close();

    input.open("./test_case/fee.txt");
    if (!input.is_open()) cout << "<<FEE NOT OPENED>>", exit(0);

    while (input) {
        string type;
        Price rate;
        for (int i = 0; i < 3; i++) {
            input >> type >> rate.slow >> rate.fast;
            bikeRate[toBike(type)] = rate;
        }
        input >> waitFee >> reduceRate >> rateofTransfer;
    }
    input.close();

    input.open("./test_case/user.txt");
    if (!input.is_open()) cout << "<<USER NOT OPENED>>", exit(0);

    while (input) {
        string t;
        input >> t;
        int ID, userID, time;
        string type;
        if (t == "rent") {
            // stationIdRent bikeType userId(5digit) timeRent
            input >> ID >> type >> userID >> time;
            station[ID].Rent(toBike(type), userID, time);
        } else if (t == "return") {
            // stationIdReturn userId timeReturn0-1440
            input >> ID >> userID >> time;
            station[ID].Return(userID, time);
            // USER MUST HAVE BIKE VAR
        }
    }
}