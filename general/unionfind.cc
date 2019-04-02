// William Sjöblom
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

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


int main() {
    int element_count, op_count;
    scanf("%d %d\n", &element_count, &op_count);

    init_forest(element_count);
    
    while (op_count--) {
        int a, b;
        
        if (scanf("= %d %d\n", &a, &b)) {
            uni(a, b);
        } else if (scanf("? %d %d\n", &a, &b)) {
            if (same(a, b)) printf("yes\n");
            else printf("no\n");
        } else {
            printf("unknown op\n");
        }
    }
    return 0;
}
