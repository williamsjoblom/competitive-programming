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
 * Return root node of set.
 */
SetNode* uni(int a, int b) {
    SetNode* a_root = root(forest[a]);
    SetNode* b_root = root(forest[b]);

    if (a_root == b_root) return a_root;

    if (a_root->rank < b_root->rank) {
        std::swap(a_root, b_root);
    }
    
    b_root->parent = a_root;
    if (a_root->rank == b_root->rank) {
        a_root->rank++;
    }

    return a_root;
}


/**
 * Are a and b in the same set?
 */
bool same(int a, int b) {
    SetNode* a_root = root(forest[a]);
    SetNode* b_root = root(forest[b]);

    return a_root == b_root;
}


bool same(SetNode* a, SetNode* b) {
    SetNode* a_root = root(a);
    SetNode* b_root = root(b);

    return a_root == b_root;
}

#include <assert.h>

int main() {
    int house_count, op_count;
    scanf("%d %d\n", &house_count, &op_count);

    init_forest(house_count);


    int first_a = 0;
    while (op_count--) {        
        int a, b;

        scanf("%d %d", &a, &b);

        if (!first_a) first_a = a;
        
        uni(a - 1, b - 1);
    }

    SetNode* internet_root = forest[0];
    if (!internet_root) printf("no root\n");
    
    bool connected = true;
    for (int i = 0; i < house_count; i++) {
        SetNode* current = forest[i];
        if (!same(current, internet_root)) {
            printf("%d\n", i + 1);
            //connected &= false;
            connected = false;
        }
    }

    if (connected) {
        printf("Connected\n");
    }
    
    return 0;
}
