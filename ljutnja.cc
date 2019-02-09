#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <numeric>

#define min(a, b) ((a) < (b)) ? (a) : (b)

int main() {
    unsigned long m, n;
    scanf("%lu %lu", &m, &n);

    unsigned long long demand = 0;
    std::vector<unsigned long> wishes(n);
    for (unsigned long long i = 0; i < n; ++i) {
        unsigned long c;
        scanf("%lu", &c);
        wishes[i] = c;
        demand += c;
    }

    std::sort(wishes.begin(), wishes.end(), std::less<unsigned long long>());

    unsigned long unaccounted_for = demand - m;

    // Divide the unaccounted for candies evenly between all children.
    unsigned long result = 0;
    for (unsigned long i = 0; i < n; ++i) {
        unsigned long wish_remainder = min(wishes[i], unaccounted_for / (n - i));
        result += wish_remainder * wish_remainder;
        unaccounted_for -= wish_remainder;
    }
    
    printf("%lu\n", result);
    return 0;
}

