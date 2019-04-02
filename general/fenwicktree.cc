// William Sjöblom

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * Tree.
 */
long tree[5000001];


/**
 * Sum.
 */
inline long sum(int index) {
    long sum = 0;
    while (index > 0) {
        sum += tree[index];
        index -= (index & -index);
    }
    
    return sum;
}


/**
 * Add.
 */
inline void add(int index, long delta, int n) {
    index++;
    
    while (index <= n) {
        tree[index] += delta;
        index += (index & -index);
    }
}


/**
 * Entry point.
 */
int main() {
    long array_length; // 1 <= array_length <= 5 000 000
    long operation_count; // 0 <= operation_count <= 5 000 000

    scanf("%ld %ld\n", &array_length, &operation_count);    
    
    for (int i = 0; i < operation_count; ++i) {
        int index;
        long delta;

        if (scanf("? %d\n", &index)) {
            printf("%ld\n", sum(index));
        } else if (scanf("+ %d %ld\n", &index, &delta)) {
            add(index, delta, array_length);
        }
    }  
}
