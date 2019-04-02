// William Sjöblom
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>


/**
 * Rational number.
 */
template<typename T>
class Rational {
public:

    /**
     * Divend.
     */
    T t;

    /**
     * Divisor.
     */
    T n;

    
    /**
     * Constructor.
     */
    Rational(T t, T n) {
        // Simplify the fraction.
        T gcd;
        while ((gcd = std::__gcd(t, n)) != 1) {
            t /= gcd;
            n /= gcd;
        }

        if (n < 0) {
            n = -n;
            t = -t;
        }            
        
        this->t = t;
        this->n = n;
    }

    
    /**
     * Add.
     */
    Rational<T> operator+(const Rational<T>& other) const {
        T _t = t*other.n + other.t*n;
        T _n = n*other.n;

        return { _t, _n };
    }

    
    /**
     * Subtract.
     */
    Rational<T> operator-(const Rational<T>& other) const {
        T _t = t*other.n - other.t*n;
        T _n = n*other.n;

        return { _t, _n };
    }

    
    /**
     * Multiply.
     */
    Rational<T> operator*(const Rational<T>& other) const {
        T _t = t*other.t;
        T _n = n*other.n;

        return { _t, _n };
    }


    /**
     * Divide.
     */
    Rational<T> operator/(const Rational<T>& other) const {
        T _t = t*other.n;
        T _n = n*other.t;

        return { _t, _n };
    }
    
    
    /**
     * To string.
     */
    std::string toS() {
        std::stringstream ss;
        ss << t << " / " << n;
        return ss.str();
    }
};


/**
 * Solve.
 */
template<typename T>
Rational<T> solve(const Rational<T>& lhs, char op, const Rational<T>& rhs) {
    switch (op) {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        return lhs / rhs;
    }
}


/**
 * Entry point.
 */
int main() {
    long test_count; scanf("%ld", &test_count);

    while (test_count--) {
        long t1, n1; scanf("%ld %ld ", &t1, &n1);
        char op; scanf("%c", &op);
        long t2, n2; scanf(" %ld %ld", &t2, &n2);
        
        auto result = solve<long>({ t1, n1 }, op, { t2, n2 });
        printf("%s\n", result.toS().c_str());
    }

    return 0;
}
