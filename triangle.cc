#include <iostream>
#include <vector>
#include <cmath>

int solve(int it) {
    int n = 1;
    
    double a = 3;
    for (int i = 0; i < it; i++) {
        a *= 3;
        a /= 2;

        if (a / 10 >= 1) {
            a /= 10;
            n++;
        }
    }
    
    return n;
}

int main() {
    int test = 0;

    int it;
    while (std::cin >> it) {
        test++;
        std::cout << "Case " << test << ": " << solve(it) << std::endl;
    }
}
