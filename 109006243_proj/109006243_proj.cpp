#include <fstream>
#include <iostream>
#include <string>

#include "./include/input.hpp"
#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/status.hpp"

#define MAXN 505
using namespace std;

int DEBUG = 0;
int DEBUG2 = 1;
/*
g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
./109006243_proj
*/
int tempStock[MAXN][3];
Station station[MAXN];

string path = "./test_case/DS_testcase/open_basic3";
// string path = "./test_case";
int main() {
    if (!DEBUG) {
        money = 0;
        ifstream input;
        ofstream output;

        inputMap(input, path);
        inputStation(input, path);
        inputFee(input, path);

        input.open(path + "/user.txt");
        output.open("part1_response.txt");
        while (input) {
            string t;
            input >> t;
            output << t << " ";
            int ID, userID, time;
            string type;
            if (t == "rent") {
                // stationIdRent bikeType userId(5digit) timeRent
                input >> ID >> type >> userID >> time;
                tempStock[ID][toBike(type)]--;
                Status x = station[ID].Rent(toBike(type), userID, time);
                output << ID << " " << type << " " << std::setfill('0')
                       << std::setw(5) << userID << " " << time << outputRes(x);
            } else if (t == "return") {
                // stationIdReturn userId timeReturn0-1440
                input >> ID >> userID >> time;
                output << ID << " " << std::setfill('0') << std::setw(5)
                       << userID << " " << time << "\n";
                bool x = station[ID].Return(userID, time);
            }
        }
        output.close();
        output.open("part1_status.txt");
        for (int i = 0; i < MAXN; i++) station[i].printStation_1(output);
        output << money;
        output.close();
    }
    // for part 2
    if (!DEBUG2) {
        money = 0;
        ifstream input;
        ofstream output;

        inputStation(input, path);

        input.open(path + "/user.txt");
        output.open("part2_response.txt");
        while (input) {
            string t;
            input >> t;
            output << t << " ";
            int ID, userID, time;
            string type;
            if (t == "rent") {
                // stationIdRent bikeType userId(5digit) timeRent
                input >> ID >> type >> userID >> time;
                Status x = station[ID].Rent(toBike(type), userID, time);
                if (x != Reject) {
                    output << ID << " " << type << " " << std::setfill('0')
                           << std::setw(5) << userID << " " << time
                           << outputRes(x);
                } else {
                    // 1. discount
                    // TODO actually to know what to offer need to know the
                    // start and the end transfer or discount wait is hard offer
                    // discount on ppl accept is hard
                }
            } else if (t == "return") {
                // stationIdReturn userId timeReturn0-1440
                input >> ID >> userID >> time;
                output << ID << " " << std::setfill('0') << std::setw(5)
                       << userID << " " << time << "\n";
                bool x = station[ID].Return(userID, time);
            }
        }
        output.close();
        output.open("part2_status.txt");
        for (int i = 0; i < MAXN; i++) station[i].printStation_1(output);
        output << money;
        output.close();
    }
}
