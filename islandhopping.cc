#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>
#include <queue>

/****************************************************************
 * Unionfind.
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
 * MST/Kruskals
 ****************************************************************/

struct Point {
    double first, second;
    int index;
};

using Edge = std::pair<Point, Point>;

double distance(const Point& p1, const Point& p2) {
    double dx = p2.first - p1.first, dy = p2.second - p1.second;
    double result = sqrt(dx*dx + dy*dy);
    
    return result;
}

double length(const Edge& e) {
    return distance(e.first, e.second);
}

double solve(std::vector<Point>& endpoints) {
    init_forest(endpoints.size());

    auto comp = [](const Edge& lhs, const Edge& rhs) {
            return length(lhs) > length(rhs);
    };

    std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> edges(comp);
    
    for (int i = 0; i < endpoints.size(); i++) {
        for (int j = 0; j < endpoints.size(); j++) {
            if (i == j) continue;
            edges.push(Edge(endpoints[i], endpoints[j]));
        }
    }

    double cost = 0;
    int count = 0;
    
    while (count < endpoints.size() - 1) {
        const Edge& e = edges.top(); edges.pop();

        //printf("edge with: %lf (%d, %d)\n", length(e), e.first.index, e.second.index);
        

        if (!same(e.first.index, e.second.index)) {
            cost += length(e);
            uni(e.first.index, e.second.index);
            count++;
        }
    }
    
    return cost;
}


int main() {
    int test_count; scanf("%d", &test_count);

    while (test_count--) {
        int island_count; scanf("%d", &island_count);

        std::vector<Point> endpoints;
        endpoints.reserve(island_count);
        
        for (int i = 0; i < island_count; i++) {
            Point endpoint;
            scanf("%lf %lf", &endpoint.first, &endpoint.second);
            endpoint.index = i;
            
            endpoints.push_back(endpoint);
        }
        
        double cost = solve(endpoints);
        //printf("%f\n", cost);
        std::cout << std::setprecision(15) << cost << std::endl;
    }
    
    return 0;
}
