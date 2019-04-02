// William Sjöblom
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>



/**
 * An edge in the graph.
 */
struct Edge {
    int first, second;
    int weight;
    int index;
};


/****************************************************************
 * Unionfind (from lab1).
 ****************************************************************/

#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

/**
 * Set node.
 */
struct SetNode {
    SetNode* parent;
    int rank;
};


/**
 * Set forest.
 */
std::vector<SetNode*> forest;


/**
 * Get root of set node.
 */
SetNode* root(SetNode* node) {
    while (node->parent != node) {
        node = node->parent;
    }

    return node;
}


/**
 * Initialize set forest.
 */
void init_forest(int size) {
    forest.clear();
    forest.reserve(size);
    for (int i = 0; i < size; i++) {
        SetNode* set = new SetNode;
        set->parent = set;
        set->rank = 0;
        forest.push_back(set);
    }
}


/**
 * Merge the sets containing a and b.
 */
void uni(int a, int b) {
    SetNode* a_root = root(forest[a]);
    SetNode* b_root = root(forest[b]);

    if (a_root == b_root) return;

    if (a_root->rank < b_root->rank) {
        std::swap(a_root, b_root);
    }
    
    b_root->parent = a_root;
    if (a_root->rank == b_root->rank) {
        a_root->rank++;
    }
}


/**
 * Are a and b in the same set?
 */
bool same(int a, int b) {
    SetNode* a_root = root(forest[a]);
    SetNode* b_root = root(forest[b]);

    return a_root == b_root;
}


/****************************************************************
 * MST/Kruskals (partially from islandhopping)
 ****************************************************************/

std::pair<int, std::vector<Edge>> solve(int node_count, std::vector<Edge>& edges) {
    if (node_count <= 1) return std::make_pair(0, std::vector<Edge>{ });
    
    init_forest(node_count);

    //printf("size = %ld\n", edges.size());

    // Set up a priority queue where edges are ordered by weight
    auto comp = [](const Edge& lhs, const Edge& rhs) {
        return lhs.weight > rhs.weight;
    };

    std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> prioritized(comp);

    for (Edge& e : edges) prioritized.push(e);

    
    int cost = 0;
    int count = 0;
    std::vector<Edge> result;

    // Kruskals
    while (!prioritized.empty()) {
        const Edge e = prioritized.top(); prioritized.pop();

        //printf("edge with: %d (%d, %d)\n", e.weight, e.first, e.second);

        if (!same(e.first, e.second)) {
            cost += e.weight;
            uni(e.first, e.second);
            count++;
            result.push_back(e);
        }
    }

    // Make sure every edges vertices are internally sorted.
    for (Edge& e : result) {
        if (e.first > e.second)
            std::swap(e.first, e.second);
    }

    // Sort for lexicographical printing.
    std::sort(result.begin(), result.end(), [](const Edge& a, const Edge& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });
    
    return std::make_pair(cost, result);
}



int main() {

    while (true) {
        int node_count, edge_count;
        scanf("%d %d", &node_count, &edge_count);

        if (node_count == 0 && edge_count == 0) break;
        
        std::vector<Edge> edges;
        edges.reserve(edge_count);

        // Read edges from stdin.
        for (int i = 0; i < edge_count; i++) {
            Edge edge;
            scanf("%d %d %d", &edge.first, &edge.second, &edge.weight);
            edge.index = i;
            edges.push_back(edge);
        }

        auto result = solve(node_count, edges);

        if (result.second.size() != node_count - 1) {
            printf("Impossible\n");
        } else {
            printf("%d\n", result.first);
            for (Edge& e : result.second) {
                if (e.first < e.second)
                    printf("%d %d\n", e.first, e.second);
                else
                    printf("%d %d\n", e.second, e.first);
            }
        }
    }
    
    return 0;
}
