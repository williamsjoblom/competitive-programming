// William Sjöblom
#include <cstdio>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

const int INT_MAX = std::numeric_limits<int>::max();

using It = std::string::iterator;
using RIt = std::string::reverse_iterator;


template<typename Iterator>
int swap(std::string& s, Iterator it, Iterator target) {
    int distance = std::distance(it, target);
    
    char c = *it;
    s.erase(it);
    s.insert(target, c);

    return std::abs(distance);
}


It find_first(std::string& s, It first, It last, char c) {
    while (first != last) {
        if (*first == c) return first;
        first++;
    }

    return s.end();
}


It find_last(std::string& s, It last, It first, char c) {
    while (first != last) {
        if (*last == c) return last;
        last--;
    }

    return s.end();
}


int solve(std::string s) {
    int swaps = 0;

    auto left = s.begin();
    auto right = s.end() - 1;

    while (std::distance(left, right) > 0) {
        if (*left != *right) {
            auto inner_left = std::next(left);
            auto inner_right = std::prev(right);
            
            auto first = find_first(s, inner_left, right, *right);
            auto last = find_last(s, inner_right, left, *left);
            
            int first_distance = std::distance(left, first);
            int last_distance = std::distance(right, last);

            if (first == s.end()) first_distance = INT_MAX;
            if (last == s.end()) last_distance = INT_MAX;
            
            if (first_distance < last_distance) {
                swaps += swap(s, first, left);
            } else if (last_distance != INT_MAX && first_distance >= last_distance) {
                swaps += swap(s, last, right);
            } else {
                return -1;
            }
            
        }

        left++;
        right--;
    }

    
    return swaps;
}


int main() {
    int test_count;
    scanf("%d\n", &test_count);
    
    while (test_count--) {
        char s[1000 + 1];
        scanf("%s\n", s);

        int result = solve(s);
        if (result == -1)
            printf("Impossible\n");
        else
            printf("%d\n", result);
    }
}
