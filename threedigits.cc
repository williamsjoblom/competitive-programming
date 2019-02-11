// William Sjöblom
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

#define EVEN(x) (x) ^ 1

inline void foo(int& x, int& removed_twos, int& removed_fives) {
    while (x % 2 == 0) {
        x /= 2;
        removed_twos++;
    }

    while (x % 5 == 0) {
        x /= 5;
        removed_fives++;
    }
}

int main() {
    /**
     * 1! = 1
     * 2! = 2
     * 3! = 6
     * 4! = 24
     * 5! = 120
     * 6! = 720
     * 7! = 5040
     * 8! = 40320
     * 9! = 362880
     * 10! = 3628800
     * 11! = 39916800
     * 12! = 479001600
     * 1000000! = ??
     */
    
    int n; scanf("%d", &n);

    long long result = 1;

    // 10^n has 2 and 5 as prime factors for any n.
    // If we discard an equal number of 5's and 2's it will
    // not alter the result.
    // There will always be more 2's than 5's.

    int removed_fives = 0;
    int removed_twos = 0;
    
    for (int i = 1; i <= n; i++) {
        int _i = i;

        foo(_i, removed_twos, removed_fives);
        
        result *= _i;
        result %= 1000;
    }

    int missing_twos = removed_twos - removed_fives;
    //printf("missing 5's = %d\n, twos = %d, fives = %d\n", missing_twos, removed_twos, removed_fives);
    while (missing_twos--) {
        result *= 2;
        result %= 1000;
    }

    // 7! is the first factorial where the result is 3 digits or longer
    // and thus need zero padding.
    if (n < 7) {
        printf("%lld\n", result);        
    } else {
        printf("%03lld\n", result);
    }
    
    return 0;
}
