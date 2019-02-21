#include <cstdio>
#include <vector>

enum Player {
    NILS = 0,
    MIKAEL = 1
};

inline Player turn(int move) {
    return static_cast<Player>(move % 2);
}

const int max_turns = 60; // Max 60 turns (500 * 0.9^60 ~= 1)
const int max_weapons = 6;
int nils_memo[max_turns / 2 + 1];
int mikael_memo[max_turns / 2 + 1];

inline int get_memo(int move) {
    Player player = turn(move);
    if (player == NILS)
        return nils_memo[move / 2];
    if (player == MIKAEL)
        return mikael_memo[move / 2];
    
    return -1;
}

inline void set_memo(int move, int value) {
    Player player = turn(move);
    if (player == NILS)
        nils_memo[move / 2] = value;
    if (player == MIKAEL)
        mikael_memo[move / 2] = value;
}

/**
 * Solve, returns the number of attacks.
 */
int solve(std::vector<double>& weapons, double size, int move=0, int weapon=0) {
    if (get_memo(move) != -1) return get_memo(move);

    if (move != 0) size *= weapons[weapon];
    if (size <= 1) return move;
    
    Player player = turn(move);
    int best = -1;
    int best_weapon = -1;
    for (int w = 0; w < weapons.size(); w++) {
        int result = solve(weapons, size, move + 1, w);
        if (best == -1 || turn(result) == player) {
            best = result;
            best_weapon = w;
        }
    }

    set_memo(move + 1, best);
    
    return best;
}

int main() {
    int n_tests; // 1 <= n_tests <= 10
    scanf("%d", &n_tests);
    
    while (n_tests--) {
        for (int i = 0; i < max_turns / 2 + 1; i++) {
            for (int j = 0; j < max_weapons; j++) {
                nils_memo[i] = -1;
                mikael_memo[i] = -1;                
            }
        }
        
        int n_weapons; // 1 <= n_weapons <= 6
        double size; // 1 < size < 500
        scanf("%lf %d", &size, &n_weapons);
        
        std::vector<double> weapons;
        while (n_weapons--) {
            double weapon; scanf("%lf", &weapon);
            weapons.push_back(weapon);
        }

        int result = solve(weapons, size);
        if (turn(result + 1) == NILS) printf("Nils\n");
        else printf("Mikael\n");
    }
}
