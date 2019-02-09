// William Sjöblom

#include <vector>
#include <string>
#include <stack>
#include <set>
#include <cstdio>
#include <map>
#include <algorithm>
#include <iterator>

struct Set;

static std::vector<Set> sets { };
static std::map<Set, size_t> lookup { };

struct Set {
    std::set<size_t> children;

    size_t key() {
        auto it = lookup.find(*this);
        if (it != lookup.end()) return it->second;
        
        sets.push_back(*this);
        lookup[*this] = sets.size() - 1;
        return sets.size() - 1;
    }

    const bool operator<(const Set& other) const {
        return children < other.children;
    }
};


Set& find(size_t key) {
    return sets[key];
}


using Stack = std::stack<size_t>;


/**
 * Push empty set.
 */
void push(Stack& stack) {
    Set empty;
    stack.push(empty.key());
}


/**
 * Duplicate the top-most set.
 */
void dup(Stack& stack) {
    stack.push(stack.top());
}


/**
 * Push the union of the two top-most sets.
 */
void uni(Stack& stack) {
    Set& a = find(stack.top()); stack.pop();
    Set& b = find(stack.top()); stack.pop();

    Set result;
    std::set_union(a.children.begin(), a.children.end(),
                   b.children.begin(), b.children.end(),
                   std::inserter(result.children, result.children.end()));
    stack.push(result.key());
}


void intersect(Stack& stack) {
    Set& a = find(stack.top()); stack.pop();
    Set& b = find(stack.top()); stack.pop();

    Set result;
    std::set_intersection(a.children.begin(), a.children.end(),
                          b.children.begin(), b.children.end(),
                          std::inserter(result.children, result.children.end()));
    stack.push(result.key());
}


void add(Stack& stack) {
    Set& a = find(stack.top()); stack.pop();
    Set b = find(stack.top()); stack.pop();

    b.children.insert(a.key());
    
    stack.push(b.key());
}


int main() {
    int test_cases;
    scanf("%d", &test_cases);

    while (test_cases--) {
        sets.clear();
        lookup.clear();
        
        int op_count;
        scanf("%d", &op_count);

        Stack stack;

        while (op_count--) {
            char s[10];
            scanf("%10s", s);

            std::string op { s };
            if (op == "PUSH") push(stack);
            else if (op == "DUP") dup(stack);
            else if (op == "UNION") uni(stack);
            else if (op == "INTERSECT") intersect(stack);
            else if (op == "ADD") add(stack);
            else printf("UNKNOWN COMMAND: %s\n", s);

            Set& top = find(stack.top());
            printf("%lu\n", top.children.size());
        }

        
        printf("***\n");
    }
}
