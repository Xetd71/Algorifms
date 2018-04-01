#include <iostream>
#include <list>

int main()
{
    int n;
    std::cin >> n;
    std::list<int> seq;
    int* arr = new int[n + 1];

    arr[0] = 0;
    for(int i = 1; i < n; ++i) {
        arr[i] = arr[i - 1] + 1;
        if(i % 2 == 0)
            arr[i] = std::min(arr[i / 2] + 1, arr[i]);
        if(i % 3 == 0)
            arr[i] = std::min(arr[i / 3] + 1, arr[i]);
    }

    for(int i = n - 1; i > 1;) {
        if(arr[i - 1] == arr[i] - 1) {
            --i;
            seq.push_front(1);
        } else if(i % 2 == 0 && (arr[i / 2] == arr[i] - 1)) {
            i /= 2;
            seq.push_front(2);
        } else if (i % 3 == 0 && (arr[i / 3] == arr[i] - 1)) {
            i /= 3;
            seq.push_front(3);
        }
    }

    std::cout << arr[n - 1] << std::endl;
    std::list<int>::iterator it = seq.begin();
    for(; it != seq.end(); ++it) {
        std::cout << *it;
    }
    return 0;
}