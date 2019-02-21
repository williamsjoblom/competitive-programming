#include <cstdio>
#include <vector>
#include <algorithm>

int memo[101][8];
int pref[100][8]; // Preferences.
int n_priests;

void dump_state(int state) {
    char l = state & 0b100 ? 'Y' : 'N';
    char m = state & 0b010 ? 'Y' : 'N';
    char r = state & 0b001 ? 'Y' : 'N';

    printf("%c%c%c\n", l, m, r);
}

int solve(int priest, int state) {
    if (priest >= n_priests) return state;
    if (memo[priest][state] != -1) return memo[priest][state];

    int exit_state = std::min<int>(
        {solve(priest + 1, state ^ 1), solve(priest + 1, state ^ 2), solve(priest + 1, state ^ 4)},
        [priest](int lhs, int rhs) {
            return pref[priest][lhs] < pref[priest][rhs];
        });

    //printf("best exit_state: "); dump_state(exit_state);
    
    memo[priest][state] = exit_state;
    return exit_state;
}


int main() {
    int n_votes; scanf("%d", &n_votes);
    
    while (n_votes--) {
        // Prepare memo.
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 8; j++)
                memo[i][j] = -1;
        }
        
        scanf("%d", &n_priests);
        
        for (int p = 0; p < n_priests; p++) {
            scanf("%d %d %d %d %d %d %d %d",
                  &pref[p][0], &pref[p][1], &pref[p][2], &pref[p][3],
                  &pref[p][4], &pref[p][5], &pref[p][6], &pref[p][7]);
            
            //printf("first = %d, last = %d\n", p.pref.front(), p.pref.back());
        }


        int result = solve(0, 0);
        dump_state(result);
    }
}
