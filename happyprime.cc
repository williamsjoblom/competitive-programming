// William Sjöblom
#include <cstdio>
#include <unordered_set>

/**
 * Calculate the sum of all digits squared.
 */
inline int digit_square_sum(int value) {
    int result = 0;
    while (value > 0) {
        int a = value % 10;
        result += a*a;
        value /= 10;
    }

    return result;
}


/**
 * Is this a happy value?
 */
bool happy(int value) {
    std::unordered_set<int> visited;
    while (value > 1 && !visited.count(value)) {
        visited.insert(value);
        value = digit_square_sum(value);
    }

    return value == 1;
}


/**
 * Is this a prime value?
 * (AKS primality test)
 */
bool prime(int value) {
    if (value <= 1) return false;
    if (value == 2 || value == 3) return true;
    if (value % 2 == 0 || value % 3 == 0) return false;

    for (int i = 5; i*i <= value; i += 6) {
        if (value % (i + 2) == 0 || value % i == 0) return false;
    }

    return true;
}


/**
 * Entry point.
 */
int main() {
    int test_count; scanf("%d", &test_count);
    while (test_count--) {
        int data_set, value; scanf("%d %d", &data_set, &value);

        if (prime(value) && happy(value))
            printf("%d %d YES\n", data_set, value);
        else
            printf("%d %d NO\n", data_set, value);
    }
}
