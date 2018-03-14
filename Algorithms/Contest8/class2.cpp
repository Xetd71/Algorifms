#include <string>
#include <iostream>

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    int a[n + 1];
    int b[n + 1];

    a[0] = 0;
    b[0] = 1;
    for(int i = 1; i <= n; ++i) {
        int stepA = a[i - 1], stepB = b[i - 1];
        switch(s[i - 1]) {
            case 'L':
                stepA +=1;
                break;
            case 'R':
                stepB += 1;
                break;
            default:
                stepA += 1;
                stepB += 1;
                break;
        }
        a[i] = std::min(stepA, stepB + 1);
        b[i] = std::min(stepB, a[i] + 1);
    }

    std::cout << b[n];
    return 0;
}