/**
 * William Sjöblom
 * Some kind of trie where each node is labeled how many words that got here.
 */
#include <map>
#include <iostream>
#include <string>
#include <cmath>

/**
 * Trie node thingy.
 */
struct Node {
    std::map<char, Node*> transitions;
    int count;
};



int main() {
    int word_count; scanf("%d", &word_count);

    Node* root = new Node();
    root->count = 0;
    
    while (word_count--) {
        std::string word; std::cin >> word;

        Node* node = root;
        for (char c : word) {
            

            if (node->transitions.count(c)) {
                node = node->transitions[c];
            } else {
                Node* added = new Node();
                node->transitions[c] = added;
                node = added;
            }
            node->count++;
        }

        std::cout << node->count - 1 << std::endl;
        
    }
}
