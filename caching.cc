#include <cstdio>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <queue>
#include <climits>

struct Access {
    int object;
    long next;
    long index;

    const bool operator<(const Access& other) const {
        return next < other.next;
    }
};

int main() {
    int cache_size, object_count, access_count;
    scanf("%d %d %d", &cache_size, &object_count, &access_count);

    std::vector<int> reads;
    while(access_count--) {
        int object; scanf("%d", &object);
        reads.push_back(object);
    }
    
    std::vector<long> next_access;
    next_access.assign(object_count, LONG_MAX);
    
    std::vector<Access> accesses(reads.size());
    for (long i = reads.size() - 1; i >= 0; --i) {
        int object = reads[i];
        accesses[i] = {object, next_access[object], i};
        next_access[object] = i;
    }

    // Priority queue with the least relevant access in front.
    std::priority_queue<Access> least_relevant;
    std::vector<bool> cache;
    cache.assign(object_count, false);
    
    int cache_reads = 0;
    int cache_usage = 0;
    for (Access& a : accesses) {
        // Skip object if it's already cached.
        if (cache[a.object]) {
            least_relevant.push(a);
            // After the above push we have two 'Access' in the priority
            // queue pointing to the same object. But that's ok since the first
            // of them will point to a point in time further back than the current
            // 'a' (and all of the following accesses in the list).
            continue;
        }

        if (cache_usage < cache_size) {
            cache_reads++;
            cache_usage++;
            
            cache[a.object] = true;
            least_relevant.push(a);
        } else {
            // Remove the least relevant object from the cache.
            int to_replace = least_relevant.top().object; least_relevant.pop();
            cache[to_replace] = false;
            
            // Push the new element to the cache.
            cache[a.object] = true;
            cache_reads++;
            least_relevant.push(a);
        }
    }

    printf("%d\n", cache_reads);
}
