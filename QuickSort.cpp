#include <iostream>

using namespace std;
int n = 100;
int A[] = {56, 13, 70, 61, 1, 31, 51, 16, 38, 57, 72, 95, 83, 47, 9, 8, 71, 7, 98, 71, 15, 90, 84, 32, 50, 1, 13, 5, 28, 59, 9, 58, 90, 55, 52, 20, 30, 29, 89, 86, 79, 13, 40, 48, 66, 26, 47, 1, 46, 51, 8, 73, 72, 24, 89, 40, 29, 25, 18, 0, 39, 28, 56, 58, 27, 78, 18, 11, 19, 14, 5, 0, 40, 80, 18, 16, 12, 83, 20, 8, 6, 11, 1, 83, 8, 64, 4, 23, 54, 3, 5, 6, 21, 88, 79, 86, 6, 54, 76, 7};
int t[105];
void quickSort(int l, int r) {
    if (l < r) {
        int i = l, j = r + 1, pivot = A[l];
        do {
            do i++;
            while (A[i] < pivot);

            do j--;
            while (A[j] > pivot);

            if (i < j) swap(A[i], A[j]);
        } while (i < j);
        swap(A[l], A[j]);
        quickSort(l, j - 1);
        quickSort(j + 1, r);
    }
}
int main() {
    quickSort(0, n - 1);
    for (auto i : A) cout << i << " ";
}