#include <cstdio>
#include <utility>
#include <set>

int start_x, start_y;
// William Sjöblom
int w, h;
char map[50][50];
bool visited[50][50];


/**
 * Read map from stdin.
 */
void scan_map() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            scanf("%c", &map[x][y]);
            
            if (map[x][y] == 'P') {
                start_x = x;
                start_y = y;
            }
        }
        
        scanf("\n");
    }
}


/**
 * Write map to stdout.
 */
void print_map() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
}


/**
 * Returns 'true' if the player feels a draft at the
 * current position.
 */
inline bool senses_draft(int x, int y) {
    return (map[x + 1][y] == 'T' ||
            map[x - 1][y] == 'T' ||
            map[x][y + 1] == 'T' ||
            map[x][y - 1] == 'T');
}



/**
 * 
 */
int solve(int x, int y) {
    if (x < 0 || y < 0 || x >= w || y >= h) return 0;
    if (visited[x][y]) return 0;
    
    visited[x][y] = true;

    if (map[x][y] == '#' ||
        map[x][y] == 'T') return 0;

    int result = 0;
    if (!senses_draft(x, y)) {
        result += solve(x + 1, y);
        result += solve(x - 1, y);
        result += solve(x, y + 1);
        result += solve(x, y - 1);
    }

    if (map[x][y] == 'G') return result + 1;
    return result;
}


int main() {
    scanf("%d %d\n", &w, &h);
    scan_map();

    int result = solve(start_x, start_y);
    printf("%d\n", result);
}
