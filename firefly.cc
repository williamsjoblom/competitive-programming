#include <cstdio>
#include <vector>

// Fenwick?
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

const bool debug = false;

struct Obstacle {
    int height;
    bool up;
};

/**
 * Tree.
 */
long u_tree[500001];
long d_tree[500001];



/**
 * Sum.
 */
inline long sum_up(int index) {
    long sum = 0;
    while (index > 0) {
        sum += u_tree[index];
        index -= (index & -index);
    }
    
    return sum;
}


/**
 * Add.
 */
inline void add_up(int height, long delta, int n) {
    height++;
    
    while (height <= n) {
        u_tree[height] += delta;
        height += (height & -height);
    }
}



/**
 * Sum.
 */
inline long sum_down(int height) {
    long sum = 0;
    while (height > 0) {
        sum += d_tree[height];
        height -= (height & -height);
    }
    
    return sum;
}


/**
 * Add.
 */
inline void add_down(int height, long delta, int n) {
    height++;
    
    while (height <= n) {
        d_tree[height] += delta;
        height += (height & -height);
    }
}


inline int collisions_at_height(int h, int max_height, int length, int mhds) {
    int downies = mhds - sum_down(max_height - h);
    int uppies = (length / 2) - sum_up(h + 1); 
    return uppies + downies;
}


// May need something fenwicky??
int main() {
    int len, height; // len always even.
    scanf("%d %d", &len, &height);

    std::vector<int> at_height(height);
    //std::vector<int> obstacles;
    for (int i = 0; i < len; i += 2) {
        int a, b; scanf("%d %d", &a, &b);

        add_up(a, 1, height);
        add_down(b, 1, height);
    }


    // int min_collisions = len;
    // // int n = 0;
    // for (int h = 0; h < height; h++) {
    //     int collisions = collisions_at_height(h, height, len);
        

        
    // }

    
    int mhds = sum_down(height);
    
    int min_collisions = len;
    int n = 0;
    for (int h = 0; h < height; h++) {
        int collisions = collisions_at_height(h, height, len, mhds); //at_height[h];
        if (debug) printf("@%d = %d\n", h, collisions);
        if (collisions < min_collisions) {
            min_collisions = collisions_at_height(h, height, len, mhds);
            n = 1;
        } else if (collisions == min_collisions) {
            n++;
        }
    }

    //
    
    printf("%d %d\n", min_collisions, n);
}
