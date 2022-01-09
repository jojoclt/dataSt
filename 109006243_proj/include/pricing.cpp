#include "pricing.hpp"

#include <iostream>

#include "station.hpp"
#include "vector.hpp"
#define MAXN 505
int money = 0;
int **map;
int waitFee, rateofTransfer;
float reduceRate;
pii bikeRate[3];
Vector<pii> transferList[2];
extern Station *station;
void initMap(int c) {
    map = new int *[c + 1];
    for (int i = 0; i <= c; i++) map[i] = new int[c + 1];
    for (int i = 0; i <= c; i++)
        for (int j = 0; j <= c; j++) map[i][j] = 123456;
    for (int i = 0; i <= c; i++) map[i][i] = 0;
}

void calcDist() {
    for (int k = 0; k <= maxStation; k++)
        for (int i = 0; i <= maxStation; i++)
            for (int j = 0; j <= maxStation; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
}

void maxTransferOp() {
    for (int bt = 0; bt < 3; bt++) {
        int c = getTransferMaxStation(bt);
        while (c != -1) {
            int need = station[c].waitList[bt].size();
            // already get station then search for its shortest transfer with
            pii t = getShortestTransfer(c, bt, need);
            if (t.second == -1) break;
            if (t.first * rateofTransfer < station[c].costExpected[bt]) {
                // sth about min(need, t.second)
                Transfer(t.second, c, bt, need);
                money -= t.first * rateofTransfer;
                station[t.second].maxTransfer[bt] -= need;
                // add transfer list type
                // moveon
                station[c].costExpected[bt] = 0;
            }
            // min of required bike
            c = getTransferMaxStation(bt);
        }
    }
}
void Transfer(int from, int to, int type, int need) {
    transferList[0].push_back({from, to});
    transferList[1].push_back({type, need});
}
// for maxRevenue Transfer
int getTransferMaxStation(int bt) {
    int c = 0;
    int temp = -1;
    for (int i = 0; i <= maxStation; i++) {
        if (c < station[i].costExpected[bt] && station[i].waitList[bt].size()) {
            c = station[i].costExpected[bt];
            temp = i;
        }
    }
    return temp;
}
pii getShortestTransfer(int from, int bt, int minTran) {
    bool isExist = false;
    pii ans = pii(1000000, -1);  // dist, station
    // pii temp = pii(1000000, -1);
    for (int i = 0; i <= maxStation; i++) {
        if (i == from) continue;
        // shortest and exist minTran
        if (ans.first > map[from][i] && station[i].maxTransfer[bt] >= minTran) {
            isExist = true;
            ans = pii(map[from][i], i);
        }
        // // shortest non-existent
        // else if (ans.first > map[from][i]) {
        //     temp = pii(map[from][i], i);
        // }
    }
    return ans;
    // return temp;
}