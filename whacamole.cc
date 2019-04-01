// William Sjöblom
#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <iostream>
#include <numeric>
#include <cmath>
#include <string>
#include <iomanip>

struct Mole {
    int x, y;
    int t;
};

const int MAX_TIME = 10;
const int MAX_WIDTH = 20;
const int MAX_DISTANCE = 5;

struct Move {
    int dx, dy;
    float distance;

    Move(int dx, int dy) : dx(dx),
                           dy(dy),
                           distance(sqrtf(dx*dx + dy*dy)) { }

    void dump() {
        std::cout << "|(" << dx << ", " << dy << ")| = " << distance;
    }
};

/**
 * has_mole[t][x][y] is true if and only if (x, y) has a mole at time 't'.
 */
bool has_mole[MAX_TIME][MAX_WIDTH + 2*MAX_DISTANCE][MAX_WIDTH + 2*MAX_DISTANCE];

/**
 * hit_moles[t][x][y] is the maximum number of hit moles if the player
 * moved the hammer to (x, y) during the last time unit.
 */
int hit_moles[MAX_TIME + 1][MAX_WIDTH + 2*MAX_DISTANCE][MAX_WIDTH + 2*MAX_DISTANCE];



void dump_hit_matrix(int t, int width, int max_distance) {
    const int start = MAX_DISTANCE - max_distance;
    const int stop = start + width + 2*max_distance;

    printf("t = %d:\n", t);
    for (int x = start; x < stop; x++) {
        for (int y = start; y < stop; y++) {
            printf("%01d ", hit_moles[t][x][y]);
        }
        printf("\n");
    }
}

void dump_matrices(int t, int width, int max_distance) {
    const int start = MAX_DISTANCE - max_distance;
    const int stop = start + width + 2*max_distance;

    printf("t = %d:\n", t);
    for (int y = start; y < stop; y++) {
        for (int x = start; x < stop; x++) {
            printf("%01d ", hit_moles[t][x][y]);
        }

        printf(" | ");
        
        for (int x = start; x < stop; x++) {
            printf("%01d ", has_mole[t][x][y]);
        }
        
        printf("\n");
    }

}

/**
 * True if there is a mole at position (x, y) at time 't'.
 */
inline bool mole(int t, int x, int y) {
    return has_mole[t][MAX_DISTANCE + x][MAX_DISTANCE + y];
}


/**
 * Assign a mole at position (x, y) at time 't'.
 */
inline void set_mole(int t, int x, int y) {
    has_mole[t][MAX_DISTANCE + x][MAX_DISTANCE + y] = true;
}


/**
 * Maximum numbers of moles hit if the starting position at time 't'
 * is (x, y).
 */
inline int mole_count(int t, int x, int y) {
    return hit_moles[t][MAX_DISTANCE + x][MAX_DISTANCE + y];
}


/**
 * Set the mole count at (x, y) at time 't' to 'v' if the new value
 * is greater than the previous.
 */
inline void update_mole_count(int t, int x, int y, int v) {
    int& count = hit_moles[t][MAX_DISTANCE + x][MAX_DISTANCE + y];
    count = std::max(count, v);
}


/**
 * Populate hit_moles where (x, y) is the position at the start of 
 * timestep 't'.
 */
inline void solve0(int t, int x, int y, int max_distance, std::vector<Move>& moves) {
    // Zero move.
    if (mole(t, x, y)) {
        update_mole_count(t + 1, x, y, mole_count(t, x, y) + 1);
    } else {
        update_mole_count(t + 1, x, y, mole_count(t, x, y));
    }

    bool v = x == 0 && y == 0 && false;

    for (const Move& m : moves) {
        int new_x = x + m.dx;
        int new_y = y + m.dy;

        int hits_in_dir = mole_count(t, x, y);
        if (mole(t, x, y))
             hits_in_dir++;
        
        float distance = m.distance;
        while (distance <= max_distance) {
            if (mole(t, new_x, new_y))
                hits_in_dir++;

            update_mole_count(t + 1, new_x, new_y, hits_in_dir);

            if (v) printf("%d ", hits_in_dir);

            new_x += m.dx;
            new_y += m.dy;
            distance += m.distance;
        }
    }
}


int solve(int width, int max_distance,
          std::vector<Mole>& moles, std::vector<Move>& moves) {
    
    // Don't forget to zero out matrices between test cases!
    
    // Initialize 'has_mole' matrix.
    for (auto& mole : moles) {
        set_mole(mole.t, mole.x, mole.y);
    }

    // Does not need to be recalculated at each test case
    // but should not cause a significant performance hit.

    const int start = -max_distance + 1;
    const int stop = width + max_distance;

    for (int t = 0; t < MAX_TIME; t++) {
        for (int x = start; x < stop; x++) {
            for (int y = start; y < stop; y++) {
                solve0(t, x, y, max_distance, moves);
            }
        }
    }


    int result = 0;
    for (int x = 0; x < MAX_WIDTH + 2*MAX_DISTANCE; x++) {
        for (int y = 0; y < MAX_WIDTH + 2*MAX_DISTANCE; y++) {
            result = std::max(hit_moles[10][x][y], result);
        }
    }

    return result;
}


int main() {    
    std::vector<Move> moves;
    
    int sq_max_distance = MAX_DISTANCE*MAX_DISTANCE;
    for (int x = 0; x*x <= sq_max_distance; x++) {
        for (int y = 0; y*y + x*x <= sq_max_distance; y++) {
            // Skip all overlapping (and zero moves since __gcd(0, 0) = 0 != 1).
            if (std::__gcd(x, y) != 1) continue;

            moves.push_back({x, y});
            
            if (x > 0) moves.push_back({-x, y});
            if (y > 0) moves.push_back({x, -y});
            if (x > 0 && y > 0) moves.push_back({-x, -y});
        }
    }

    
    while (true) {
        int width, max_distance, mole_count;
        scanf("%d %d %d", &width, &max_distance, &mole_count);

        if (width == 0 &&
            max_distance == 0 &&
            mole_count == 0) break;

        std::vector<Mole> moles;
        moles.reserve(mole_count);
        
        while (mole_count--) {
            Mole m;
            scanf("%d %d %d", &m.x, &m.y, &m.t);
            m.t--; // Make time a zero index.
            moles.push_back(m);
        }
        
        int result = solve(width, max_distance,
                           moles, moves);
        
        printf("%d\n", result);

        for (int t = 0; t < MAX_TIME + 1; t++) {
            for (int x = 0; x < MAX_WIDTH + 2*MAX_DISTANCE; x++) {
                for (int y = 0; y < MAX_WIDTH + 2*MAX_DISTANCE; y++) {
                    if (t < 10)
                        has_mole[t][x][y] = false;

                    hit_moles[t][x][y] = 0;
                }
            }
        }
    }

    return 0;
}
