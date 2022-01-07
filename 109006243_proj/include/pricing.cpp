#include "pricing.hpp"

#include <iostream>
#define MAXN 505
int money = 0;
int map[MAXN][MAXN];
int waitFee, reduceRate, rateofTransfer;
pii bikeRate[3];
void initMap() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++) map[i][j] = 123456;
    for (int i = 0; i < MAXN; i++) map[i][i] = 0;
}

void calcDist() {
    for (int k = 0; k < MAXN; k++)
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
}