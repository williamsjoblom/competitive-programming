#include <cstdio>
#include <cmath>
#include <vector>

struct Clause {
    std::vector<int> literals;

    void dump() {
        if (literals[0] < 0) printf("~");
        printf("X%d", std::abs(literals[0]));
        
        for (int i = 1; i < literals.size(); i++) {
            printf(" v ");
            if (literals[i] < 0) printf("~");
            printf("X%d", std::abs(literals[i]));
        }

        printf("\n");
    }

    bool satisfied(std::vector<bool>& values) {
        bool satisfied = false;
        for (int literal : literals) {
            satisfied |= (literal < 0) ^ values[std::abs(literal) - 1];
        }
        
        return satisfied;
    }
};


/**
 * Scan variable.
 */
int scan_var() {
    int var;
    if(scanf("~X%d", &var)) {
        var = -var;
    } else {
        scanf("X%d", &var);
    }

    return var;
}


/**
 * Scan clause.
 */
Clause scan_clause() {
    Clause c;
    c.literals.push_back(scan_var());

    while (getchar() == ' ') { // Will eventually consume a newline and break loop.
        scanf("v ");
        c.literals.push_back(scan_var());
    }
    
    return c;
}


bool solve0(std::vector<Clause>& clauses, std::vector<bool> values, int i=0) {
    if (i >= values.size()) {
        for (Clause& clause : clauses) {
            if (!clause.satisfied(values)) return false;
        }

        return true;
    }
    
    

    bool first = solve0(clauses, values, i + 1);
    if (first) return true;
    
    std::vector<bool> other = values;
    other[i] = !other[i];
    return solve0(clauses, other, i + 1);
}


bool solve(int var_count, std::vector<Clause>& clauses) {
    std::vector<bool> values(var_count);
    return solve0(clauses, values, 0);
}

/**
 * Entry point.
 */
int main() {
    int test_count; scanf("%d", &test_count);
    while (test_count--) {
        int var_count, clause_count; scanf("%d %d\n", &var_count, &clause_count);
        std::vector<Clause> clauses;
        clauses.reserve(clause_count);
        
        while (clause_count--) {
            Clause c = scan_clause();
            clauses.push_back(c);
        }

        bool satisfiable = solve(var_count, clauses);
        if (satisfiable) printf("satisfiable\n");
        else printf("unsatisfiable\n");
    }

    return 0;
}
