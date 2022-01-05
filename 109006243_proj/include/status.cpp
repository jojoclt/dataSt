#include "status.hpp"
std::string outputRes(Status c) {
    if (c == Accept) return "\naccept\n";
    if (c == Reject) return "\nreject\n";
    if (c == Discount) return "XXDDDDD Discount need TP!";
    return "NOOO!!!";
}