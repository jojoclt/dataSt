#include <iostream>
using namespace std;
int temp[105];
int n = 100;
int A[] = {56, 13, 70, 61, 1, 31, 51, 16, 38, 57, 72, 95, 83, 47, 9, 8, 71, 7, 98, 71, 15, 90, 84, 32, 50, 1, 13, 5, 28, 59, 9, 58, 90, 55, 52, 20, 30, 29, 89, 86, 79, 13, 40, 48, 66, 26, 47, 1, 46, 51, 8, 73, 72, 24, 89, 40, 29, 25, 18, 0, 39, 28, 56, 58, 27, 78, 18, 11, 19, 14, 5, 0, 40, 80, 18, 16, 12, 83, 20, 8, 6, 11, 1, 83, 8, 64, 4, 23, 54, 3, 5, 6, 21, 88, 79, 86, 6, 54, 76, 7};

void radix(int exp) {
    int count[10] = {};
    for (auto c : A) {
        count[(c / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        temp[count[(A[i] / exp) % 10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
    }
    copy(temp, temp + n, A);
}
int main() {
    int m = -1;
    for (auto i : A)
        if (m < i) m = i;
    for (int exp = 1; m / exp > 0; exp *= 10) {
        radix(exp);
        for (auto i : A) cout << i << " ";
        cout << endl;
    }
}