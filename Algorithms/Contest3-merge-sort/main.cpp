#include <algorithm>
#include <iostream>

int main() {
    int arr[] = {0, 4, 8, 8, 9, 5, 6, 8, 8, 9};
    int left = 0, middle = 4, right = 9;
    int p1 = left, p2 = middle + 1, pm = p2;
    while(arr[p1++] < arr[p2]);
    --p1;
    std::swap(arr[p1++], arr[p2++]);
    while(p2 <= right) {
        if(arr[p2] <= arr[pm]) {
            std::swap(arr[p1++], arr[p2++]);
        } else {
            std::swap(arr[p1++], arr[pm++]);
        }
    }
    for(int i = 0; i < 10; ++i) {
        std::cout << arr[i] << ' ';
    }
}