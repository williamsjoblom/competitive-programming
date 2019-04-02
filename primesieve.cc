// William Sjöblom
#include <cstdio>
#include <vector>


/**
 * Erathostens prime sieve.
 */
class Sieve {
public:
    std::vector<bool> not_prime;

    long total_prime_count;
    
    /**
     * Constructor.
     *
     * Iteratively marks all composite numbers storing the total number of
     * primes until 'max' (inclusive).
     */
    Sieve(long max) {
        not_prime.resize(max, false);
        not_prime[0] = true;
        
        total_prime_count = 0;
        for (long i = 2; i <= max; i++) {
            if (not_prime[i - 1]) continue;

            total_prime_count++;
            for (long j = i*2; j <= max; j += i) {
                not_prime[j - 1] = true;
            }
        }
    }

    
    /**
     * Return if 'x' (<= 'max') is a prime.
     */
    bool is_prime(long x) {
        return !not_prime[x - 1];
    }
};


/**
 * Entry point.
 */
int main() {
    long max;
    int query_count;

    scanf("%ld %d", &max, &query_count);

    Sieve sieve(max);

    printf("%ld\n", sieve.total_prime_count);
    
    while (query_count--) {
        long x; scanf("%ld", &x);
        printf("%d\n", sieve.is_prime(x));
    }
}
