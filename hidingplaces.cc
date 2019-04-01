#include <cstdio>
#include <algorithm>
#include <limits>
#include <utility>
#include <vector>
#include <iostream>


/**
 * Number of turns to reach a given position
 */
int turns[8][8];


void solve(int x, int y, int turn=0) {
    if (x < 0 || x >= 8 ||
        y < 0 || y >= 8) {
        return;
    }

    // Should be sufficient.
    if (turn >= 7) {
        //printf("e ret 2\n");
        return;
    }

    if (turn < turns[x][y]) {
        turns[x][y] = turn;
        
        solve(x + 2, y + 1, turn + 1);
        solve(x + 2, y - 1, turn + 1);
        solve(x - 2, y + 1, turn + 1);
        solve(x - 2, y - 1, turn + 1);
        solve(x + 1, y + 2, turn + 1);
        solve(x + 1, y - 2, turn + 1);
        solve(x - 1, y + 2, turn + 1);
        solve(x - 1, y - 2, turn + 1);
    }
}



int main() {
    int test_count; scanf("%d\n", &test_count);

    while (test_count--) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++)
                turns[x][y] = std::numeric_limits<int>::max();
        }
            
        
        char x, y; std::cin >> x >> y;
        x -= 'a'; y -= '1';
        
        solve(x, y, 0);

        int max = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                max = std::max(max, turns[x][y]);
                //printf("%d ", turns[x][y]);
            }
            //printf("\n");
        }


        std::vector< std::pair<char, char> > result;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (turns[x][y] == max) {
                    result.push_back(std::make_pair<char, char>(x + 'a', y + '1'));
                }
            }
        }

        std::sort(result.begin(), result.end(), [](std::pair<char, char> lhs,
                                                   std::pair<char, char> rhs) {
                if (lhs.second == rhs.second)
                    return lhs.first < rhs.first;
                return lhs.second > rhs.second;
            });

        
        printf("%d ", max);
        for (auto& pos : result) {
            printf("%c%c ", pos.first, pos.second);
        }
        printf("\n");
    }
    
    return 0;
}
