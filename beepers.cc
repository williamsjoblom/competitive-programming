// William Sjöblom
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        else return x < other.x;
    }
};


inline int cost(Point& a, Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


/**
 * Better solved by DP but brute force should do the trick under 8 secs.
 */
int solve(std::vector<Point>& beepers, Point start) {
    // Sort in ascending order so that next_permutation will return false
    // at the last possible permutation.
    std::sort(beepers.begin(), beepers.end());

    int best_distance = std::numeric_limits<int>::max();
    
    while (true) {
        int distance = 0;
        
        Point last = start;
        for (Point& p : beepers) {
            distance += cost(last, p);
            last = p;
        }

        distance += cost(last, start);
        
        best_distance = std::min(distance, best_distance);
        
        if (!std::next_permutation(beepers.begin(), beepers.end()))
            break;
    }

    return best_distance;
}



int main() {
    int test_count; scanf("%d", &test_count);

    while (test_count--) {
        int width, height; scanf("%d %d", &width, &height);
        Point start; scanf("%d %d", &start.x, &start.y);
        int beeper_count; scanf("%d", &beeper_count);

        std::vector<Point> beepers;
        beepers.reserve(beeper_count);
        
        while (beeper_count--) {
            Point b; scanf("%d %d", &b.x, &b.y);
            beepers.push_back(b);
        }

        int result = solve(beepers, start);
        printf("%d\n", result);
    }
}
