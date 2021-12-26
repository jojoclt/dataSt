#ifndef BIKETYPE_H
#define BIKETYPE_H

#include <string>

std::string str_bikeType[] = {"electric", "lady", "road"};

int toBike(std::string b) {
    if (b == "electric") return 0;
    if (b == "lady") return 1;
    if (b == "road") return 2;
}
#endif