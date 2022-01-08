#include <fstream>
#include <iostream>
#include <string>

#include "./include/input.hpp"
#include "./include/pricing.hpp"
#include "./include/station.hpp"
#include "./include/status.hpp"
#include "./include/user.hpp"

#define MAXN 505
using namespace std;

int DEBUG = 1;
int DEBUG2 = 1;
int DEBUG3 = 1;
extern User user[100000];
/*
g++ -g *.cpp ./include/*.cpp -o 109006243_proj -std=c++11
./109006243_proj
*/
Station station[MAXN];
void stockAtTime();
void outputUserTest();
string path = "./test_case/DS_testcase/open_basic3";
// string path = "./test_case";
int main() {
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
            Status x = station[ID].Rent(toBike(type), userID, time);
            output << ID << " " << type << " " << std::setfill('0')
                   << std::setw(5) << userID << " " << time << outputRes(x);
            if (x == Accept) station[ID].stockAtTime[time][toBike(type)]--;
        } else if (t == "return") {
            // stationIdReturn userId timeReturn0-1440
            input >> ID >> userID >> time;
            output << ID << " " << std::setfill('0') << std::setw(5) << userID
                   << " " << time << "\n";
            bool x = station[ID].Return(userID, time);
            if (x == true) station[ID].stockAtTime[time][user[userID].type]++;
        }
    }
    output.close();

    if (DEBUG) stockAtTime();

    output.open("part1_status.txt");
    for (int i = 0; i < MAXN; i++) station[i].printStation_1(output);
    output << money;
    output.close();

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
    if (DEBUG) outputUserTest();
}
void stockAtTime() {
    int t[3];
    ofstream out;
    out.open("stockTime.txt");
    for (int i = 0; i < MAXN; i++) {
        if (station[i].sID != -1) {
            for (int j = 0; j < 3; j++) {
                for (int k = 1; k <= 1441; k++) {
                    station[i].stockAtTime[k][j] +=
                        station[i].stockAtTime[k - 1][j];
                    station[i].stockAtTime[k - 1][j] += station[i].size[j];
                }
            }
            for (int j = 0; j <= 1440; j++) {
                if (j && t[0] == station[i].stockAtTime[j][0] &&
                    t[1] == station[i].stockAtTime[j][1] &&
                    t[2] == station[i].stockAtTime[j][2])
                    continue;
                out << i << "@" << j << ": ";
                for (int k = 0; k < 3; k++) {
                    t[k] = station[i].stockAtTime[j][k];
                    out << t[k] << " ";
                }
                out << "\n";
            }
        }
    }
}

void outputUserTest() {
    ofstream out;
    out.open("TEST.txt");
    for (int i = 0; i < 100000; i++) {
        if (user[i].type != -1) {
            out << "User: " << i << " " << toName(user[i].type)
                << " Time: " << user[i].timeSt << "-" << user[i].timeEnd
                << " sOut-sIn: " << user[i].sOut << "->" << user[i].sIn << "\n";
        }
    }
    out.close();
}