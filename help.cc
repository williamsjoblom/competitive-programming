// William Sjöblom

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <sstream>
#include <iterator>

using Pattern = std::vector<std::string>;


inline bool is_placeholder(std::string s) {
    return s.front() == '<';
}


void subst_trivial(Pattern& a_, Pattern& b_) {
start:;
    auto a_it = a_.begin();
    auto b_it = b_.begin();

    while (a_it != a_.end() && b_it != b_.end()) {
        std::string a = *a_it, b = *b_it;

        if (is_placeholder(a) && !is_placeholder(b)) {
            std::replace(a_.begin(), a_.end(), a, b);
            goto start;
        } else if (!is_placeholder(a) && is_placeholder(b)) {
            std::replace(b_.begin(), b_.end(), b, a);
            goto start;
        }
        
        ++a_it; ++b_it;
    }

    a_it = a_.begin();
    b_it = b_.begin();

    while (a_it != a_.end() && b_it != b_.end()) {
        std::string a = *a_it, b = *b_it;

        if (is_placeholder(a) && is_placeholder(b)) {
            std::string new_word = "x";
            std::replace(a_.begin(), a_.end(), a, new_word);
            std::replace(b_.begin(), b_.end(), b, new_word);
            goto start;
        }
        
        ++a_it; ++b_it;
    }
}


// void subst(Pattern& a_, Pattern& b_) {
//     auto a_it = a_.begin();
//     auto b_it = b_.begin();
    
//     while (a_it != a_.end() && b_it != b_.end()) {
//         std::string a = *a_it, b = *b_it;

//         if (is_placeholder(a) && is_placeholder(b)) {
//             std::string new_word = "x";
//             std::replace(a_.begin(), a_.end(), a, new_word);
//             std::replace(b_.begin(), b_.end(), b, new_word);
//             return subst(a_, b_);
//         }
        
//         ++a_it; ++b_it;
//     }
// }


Pattern tokenize(std::string s) {
    std::istringstream iss(s);
    return Pattern(std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>());
}


int main() {
    std::ios::sync_with_stdio(false);

    std::string count;
    std::getline(std::cin, count);
    int test_count = std::atoi(count.c_str());
        
    for (int i = 0; i < test_count; ++i) {

        std::string a, b;
        std::getline(std::cin, a);
        std::getline(std::cin, b);

        Pattern pa = tokenize(a);
        Pattern pb = tokenize(b);
        
        subst_trivial(pa, pb);
        //subst(pa, pb);
        
        if (pa != pb) {
            std::cout << "-" << std::endl;
        } else {
            for (std::string w : pa) {
                std::cout << w << " ";
            }
            
            std::cout << std::endl;
        }
    }
}
