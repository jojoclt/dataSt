#include <fstream>
#include <iostream>
#include <string>

#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/status.hpp"

using namespace std;

int DEBUG = 0;
/*
g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
./109006243_proj
*/
Station station[101];
extern int money;
extern int map[105][105];
extern int waitFee, reduceRate, rateofTransfer;
extern pii bikeRate[3];
int toBike(string b) {
    if (b == "electric") return 0;
    if (b == "lady") return 1;
    if (b == "road") return 2;
    return 0;
}
int main() {
    if (!DEBUG) {
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
            station[ID] = Station(ID, elecAmt, ladyAmt, roadAmt);
        }
        input.close();

        input.open("./test_case/fee.txt");
        if (!input.is_open()) cout << "<<FEE NOT OPENED>>", exit(0);

        while (input) {
            string type;
            pii rate;
            for (int i = 0; i < 3; i++) {
                input >> type >> rate.first >> rate.second;
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
                Status x = station[ID].Rent(toBike(type), userID, time);
                if (x == Reject)
                    cout << "REJECT\n";
                else
                    cout << "ACCEPT\n";
            } else if (t == "return") {
                // stationIdReturn userId timeReturn0-1440
                input >> ID >> userID >> time;
                station[ID].Return(userID, time);
                // USER MUST HAVE BIKE VAR
            }
        }
    } else {
        // type1 and2 response
        // station[0] = Station(0, 2, 3, 4);
        // // cout << station[0].bikeCount[2];
        // station[0].addBike(2, pii(3, 22));
        // station[0].printBike(2);
        // // cout << "X";
    }
    // station[1] = Station(1, 2, 3, 4);
    for (int i = 0; i <= 100; i++) station[i].printStation_1();
    std::cout << money;
}
