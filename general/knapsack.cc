// William Sjöblom

#include <bits/stdc++.h>

struct Item {
    int value;
    int weight;
};

struct Entry {
    int value;
    int i;
    Entry* previous;
};


std::vector<int> solve(double capacity, std::vector<Item>& items) {
    // max[i][j]: the max value that can be attained
    // by the first 'i' elements with weight >= j.
    
    //static int memo[items.size() + 1][capacity + 1];
    static Entry memo[2001][2001]; // Using the given max values for N and C.
    for (int j = 0; j <= capacity; ++j) {
        // Zero out the first row.
        memo[0][j] = {0, -1, nullptr};
    }

    for (int i = 1; i <= items.size(); ++i) {
        for (int j = 0; j <= capacity; ++j) {
            Item& item = items[i - 1];
            Entry& current = memo[i][j];
            
            if (item.weight > j) {
                // The item is clearly too heavy. (no item added)
                Entry& last = memo[i - 1][j];
                
                current.value = last.value;
                current.previous = &last;
                current.i = -1;
            } else if (memo[i - 1][j - item.weight].value + item.value > memo[i - 1][j].value) {
                // Adding this item to the best previous knapsack that fits it yeilds
                // a better value than reusing the previously best knapsack.
                Entry& last = memo[i - 1][j - item.weight];
                
                current.i = i - 1;
                current.previous = &last;
                current.value = last.value + item.value;
            } else {
                // The best knapsack for the i - 1 first items is still the best bet.
                Entry& last = memo[i - 1][j];
                
                current.value = last.value;
                current.previous = &last;
                current.i = -1;
            }
        }
    }

    std::vector<int> indices { };
    
    Entry* best = &memo[items.size()][static_cast<int>(capacity)];
    while (best != nullptr) {
        if (best->i != -1)
            indices.push_back(best->i);
        best = best->previous;
    }
    
    return indices;
}


int main() {
    double capacity; // <= 2000
    int n;
    while (std::cin >> capacity >> n) {

        std::vector<Item> items(n);
        for (int i = 0; i < n; ++i) {
            Item item;
            scanf("%d %d", &item.value, &item.weight);
            items[i] = item;
        }

        // Since the item weights are integers we can safely floor 'capacity'.
        std::vector<int> indices = solve(capacity, items);
        printf("%lu\n", indices.size());
        if (!indices.empty()) {
            for (int i : indices) printf("%d ", i);
            printf("\n");
        }
    }
    
    return 0;
}
