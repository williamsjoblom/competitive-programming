// William Sj;blom

#include <cstdio>
#include <tuple>
#include <exception>


/**
 * Forward declarations.
 */
template<typename T>
class Mod;

template<typename T>
std::tuple<T, T, T> egcd(T a, T b);

template<typename T>
Mod<T> inverse(Mod<T> v);


/**
 * Class for modular arithmetic.
 */
template<typename T>
class Mod {
    
public:
    /**
     * Actual value.
     */
    T value;
    
    /**
     * Modulo operand.
     */
    T mod;

public:

    /**
     * Construtor.
     */
    Mod(T value, T mod) : mod(mod) {
        this->value = value % mod;

        if (value < 0)
            this->value += mod;
    }


    /**
     * Add.
     */
    Mod<T> operator+(Mod<T> other) const {
        return Mod<T>(value + other.value, mod);
    }

    
    /**
     * Subtract.
     */
    Mod<T> operator-(Mod<T> other) const {
        return Mod<T>(value - other.value, mod);
    }

    
    /**
     * Multiply.
     */
    Mod<T> operator*(Mod<T> other) const {
        return Mod<T>(value * other.value, mod);
    }

    
    /**
     * Divide.
     */
    Mod<T> operator/(Mod<T> other) const {
        return *this * inverse(other);
    }

    
    /**
     * Cast to value type.
     */
    operator T() {
        return value;
    }
};


/**
 * Extended euclidian algorithm.
 *
 * Returns tuple (gcd(a, b), x, y) fulfilling ax + by = gcd(a, b).
 */
template<typename T>
std::tuple<T, T, T> egcd(T a, T b) {
    if (a == 0) return std::tuple<T, T, T> {b, 0, 1};

    auto r = egcd(b % a, a);
    T g = std::get<0>(r);
    T y = std::get<1>(r);
    T x = std::get<2>(r);
    
    return std::tuple<T, T, T> { g, x - (b / a) * y, y };
}


/**
 * Modulo multiplicative inverse.
 *
 * Throws exeption the modular inverse does not exist.
 */
template<typename T>
Mod<T> inverse(Mod<T> v) {
    auto r = egcd(v.value, v.mod);
    
    T g = std::get<0>(r);
    T x = std::get<1>(r);

    if (g != 1) throw std::exception();

    return Mod<T>(x,  v.mod);
}


/**
 * Solve.
 */
long solve(long n, long lhs, char op, long rhs) try {
    Mod<long> _lhs(lhs, n), _rhs(rhs, n);
    
    switch (op) {
    case '+':
        return Mod<long>(_lhs + _rhs, n);
    case '-':
        return Mod<long>(_lhs - rhs, n);
    case '*':
        return Mod<long>(_lhs * _rhs, n);
    case '/':
        return Mod<long>(_lhs / _rhs, n);
    }

    return -1;
} catch (std::exception& e) {
    return -1;
}


/**
 * Entry point.
 */
int main() {

    while (true) {
        long n;
        int test_count;
        scanf("%ld %d", &n, &test_count);

        if (n == 0 && test_count == 0) break;

        while (test_count--) {
            long lhs;
            char op;
            long rhs;

            scanf("%ld %c %ld", &lhs, &op, &rhs);
            long result = solve(n, lhs, op, rhs);
            printf("%ld\n", result);
        }
        
    }

    return 0;
}
