#include "pricing.hpp"

#include <iostream>
#define MAXN 505
int money = 0;
int **map;
int waitFee, rateofTransfer;
float reduceRate;
pii bikeRate[3];
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

pii getShortestTransfer(int from, int type) {}