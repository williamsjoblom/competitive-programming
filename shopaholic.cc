#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>

const bool debug = false;

int main() {
    int item_count; scanf("%d", &item_count);
    std::vector<long long> prices;
    while (item_count--) {
        long long price; scanf("%lld", &price);
        prices.push_back(price);
    }

    long long discount = 0;

    std::sort(prices.begin(), prices.end(), std::greater<int>());
    if (debug) {
        for (long long price : prices) {
            printf("%lld ", price);
        }
        printf("\n");
    }

    
    for (unsigned i = 2; i < prices.size(); i += 3) {
        discount += prices[i];
    }
    
    printf("%lld\n", discount);
}
