#include <vector>
#include <iostream>
#include <utility>

using ll = long long;

std::pair<ll, ll> solve(ll cardinal, ll decimal, bool repeating) {

}

int main() {
    long long cardinal = 0;
    long long decimal;
    bool repeating;

    while (std::cin >> cardinal) {
        decimal = 0; repeating = false;        
        
        char dot; std::cin >> dot;
        if (dot == '.') {
            std::cin >> decimal;
            std::string ellipsis; std::cin >> ellipsis;
            repeating = !ellipsis.empty();
        }

        //std::cout << cardinal << '.' << decimal << (repeating ? "..." : "") << std::endl;
        std::pair<ll, ll> fraction = solve(cardinal, decimal, repeating);
        std::cout << fraction.first << '/' << fraction.second << std::endl;
    }
            
    return 0;
}
