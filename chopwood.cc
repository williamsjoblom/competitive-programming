// William Sjöblom

#include <cstdio>
#include <vector>
#include <set>
#include <unordered_set>
#include <numeric>
#include <map>

std::vector<int> solve(std::vector<int>& connecting) {
    //printf("%d size=%lu\n", connecting.back(), connecting.size());
    std::vector<int> references(connecting.size() + 2, 0);
    std::set<int> leaves;
    for (int i = 1; i <= connecting.size(); i++) {
        leaves.insert(i);
    }
    
    for (int node : connecting) {
        leaves.erase(node);
        references[node]++;
    }

    // for (int node = 1; node < references.size(); node++) {
    //      printf("ref(%d) = %d\n", node, references[node]);
    // }

    std::vector<int> result;
    for (int node : connecting) {
        if (leaves.empty()) return {};

        // std::set is internally sorted thus std::set::begin() will return its smallest element.
        int leaf = *leaves.begin();
        if (!references[node]) return {};
        
        //printf("cutting leaf %d\n", *it);
        
        result.push_back(leaf);
        leaves.erase(leaf);
        if (--references[node] == 0) {
            leaves.insert(node);
        }
    }

    return result;
}

int main() {
    int n; scanf("%d", &n);

    std::vector<int> connecting;
    connecting.reserve(n);
    for (int i = 0; i < n; i++) {
        int v; scanf("%d", &v);
        connecting.push_back(v);
    }

    std::vector<int> result = solve(connecting);
    if (result.empty()) {
        printf("Error\n");
    } else {
        for (int leaf : result)
            printf("%d\n", leaf);
    }

    return 0;
}
