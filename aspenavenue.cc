#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>

/****************************************************************
 * Naive solution. Fails the first test case.
 ****************************************************************/

void solve1(int tree_count, int length, int width, std::vector<double>& positions) {
    std::sort(positions.begin(), positions.end());

    double total_distance = 0; 
    
    double interval = static_cast<double>(length) / ((tree_count - 2) / 2);
    double current = 0;
    for (int i = 0; i < tree_count; i += 2) {
        double tree1 = positions[i];
        double tree2 = positions[i + 1];
        double distance1 = std::abs(tree1 - current);
        double distance2 = std::abs(tree2 - current);

        // tree1 is closest to planting point.
        // move tree2 across the road.
        if (distance1 < distance2) {
            total_distance += distance1;
            total_distance += std::sqrt(distance2*distance2 + width*width);
        } else {
            total_distance += distance2;
            total_distance += std::sqrt(distance1*distance1 + width*width);
        }

        current += interval;
    }

    printf("%.10lf\n", total_distance);

}

/****************************************************************
 * Another solution.
 ****************************************************************/

#include <list>

void solve2(int tree_count, int length, int width, std::vector<double>& _positions) {
    std::sort(_positions.begin(), _positions.end());
    double interval = static_cast<double>(length) / ((tree_count - 2) / 2);

    std::list<double> positions;
    std::copy(_positions.begin(), _positions.end(), positions.begin());

    auto begin = positions.begin(), end = positions.end();
    double first = 0, last = length;
    for (int i = 0; i < tree_count / 2; ++i) {
        if (i == tree_count / 2 - 1) {
            
        } else {
            ++begin;
            --end;

            
            positions.pop_back();
            positions.pop_front();

            
            
            positions.pop_back();
            positions.pop_front();
        }
    }
    
    //printf("%lf\n", total_distance);

}

/**
 * All trees are dropped along the left side.
 *
 * Arranging them in pairs on one side then moving one from each pair across the road
 * work fine.
 */
int main() {
    int tree_count;
    scanf("%d", &tree_count);

    int length, width;
    scanf("%d %d", &length, &width);

    // All along the left side.
    std::vector<double> positions(tree_count);
    for (int i = 0; i < tree_count; ++i) {
        scanf("%lf", &positions[i]);
    }

    solve1(tree_count, length, width, positions);
    
    return 0;
}
