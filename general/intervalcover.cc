// William Sjöblom

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cmath>

#define EPS 0.0000001

inline bool eq(double a, double b) {
    return std::abs(a - b) < EPS;
}

struct interval {
    unsigned index;
    double start, end;
};


inline double cover_of(double a0, double a1, double b0, double b1) {
    double cover_start = std::max(a0, b0);
    double cover_end = std::min(a1, b1);
    return cover_end - cover_start;
}


void run(double a, double b, long n, std::vector<interval>& intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const interval& a, const interval& b) {
                  return a.start < b.start;
              });

    // Is the interval of length 0 (0.0001 used as epsilon)?
    if (false && eq(a, b)) {
        printf("0\n\n");
        return;
    }
    
    std::vector<interval> cover;

    for (long _i = 0; _i < n; _i++) {

        long best_index = -1;
        double best_cover = -1;
        
        for (long i = _i; i < n; ++i) {
            interval& current = intervals[i];
            if (current.start > a) break;
            
            double cover = cover_of(current.start, current.end, a, b);
            if (cover > best_cover) {
                best_index = i;
                best_cover = cover;
            }
        }

        if (best_index == -1) break;

        a = intervals[best_index].end;
        
        cover.push_back(intervals[best_index]);
        
        if (cover.back().end >= b) {
            std::cout << cover.size() << std::endl;
            for (auto c : cover)
                std::cout << c.index << " ";
            std::cout << std::endl;
            return;
        }
    }

    std::cout << "impossible" << std::endl;
}

int main() {
    double a, b;
    long n;

    while (std::cin >> a >> b) {
        std::cin >> n;
        std::vector<interval> intervals(n);
        for (unsigned i = 0; i < n; ++i) {
            double start, end;
            scanf("%lf %lf", &start, &end);
            intervals[i] = interval {i, std::min(start, end), std::max(start, end)};
        }

        run(a, b, n, intervals);
    }

    return 0;
}
