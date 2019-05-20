#include <map>
#include <string>
#include <iostream>

struct Node {
    std::map<char, Node*> trans;
    bool end;
};


bool add_string(Node* node, std::string s, int i, bool followed=false) {
    if (node->end || (followed && i == s.size())) {
        //std::cout << "Found end" << std::endl;
        return false;
    }
    
    if (i == s.size()) {
        //std::cout << "set end" << std::endl;
        node->end = true;
        return true;
    }

    if (node->trans.count(s[i])) {
        //std::cout << "following " << s[i] << std::endl;
        return add_string(node->trans[s[i]], s, i+1, true);
    } else {
        //std::cout << "new " << s[i] << std::endl;
        Node* n = new Node();
        node->trans[s[i]] = n;

        return add_string(n, s, i+1);
    }
    
    return true;
}


int main() {    
    int test_count; std::cin >> test_count;

    std::string dummy;
    
    while (test_count--) {
        Node* root = new Node {{}, false};
        
        int n; std::cin >> n;
        
        bool result = true;
        
        while (n--) {
            std::string nr;
            std::cin >> nr;

            if (!add_string(root, nr, 0)) {
                //std::cout << "set result to false" << std::endl;
                result = false;
            }
        }

        if (result) std::cout << "YES" << std::endl;
        else std::cout << "NO" << std::endl;
    }
    
}
