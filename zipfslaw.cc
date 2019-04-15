// William Sjöblom
#include <iostream>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>

inline void downcase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void eat_crap(std::string::iterator& begin, std::string::iterator end) {
    while (begin != end && !isalpha(*begin))
        begin++;
}

void eat_token(std::string::iterator& begin, std::string::iterator end) {
    while (begin != end && isalpha(*begin))
        begin++;
}


/**
 * Strip punctuation.
 */
bool tokenize(std::string& s, std::vector<std::string>& tokens) {
    std::string::iterator it = s.begin();
    std::string::iterator start;
    
    while (it != s.end()) {
        eat_crap(it, s.end());

        if (it != s.end()) {
            start = it;
            eat_token(it, s.end());
            std::string token(start, it);
            downcase(token);

            //std::cout << token << std::endl;
            
            if (token == "endoftext") {
                return false;
            }

            tokens.push_back(token);
        }
    }

    return true;
}

void solve(int n) {
    //std::cout << n << std::endl;
    std::unordered_map<std::string, int> histogram;
    
    std::vector<std::string> tokens;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (!tokenize(line, tokens)) break;
    }

    for (std::string& token : tokens) {
        histogram[token]++;
    }

    histogram["endoftext"] = -1;

    // for (auto token : tokens) {
    //     std::cout << token << std::endl;
    // }
    
    std::vector<std::string> results;

    int words = 0;
    for (auto& [s, occ] : histogram) {
        if (occ == n) {
            results.push_back(s);
            words++;
        }
    }

    if (!words) {
        std::cout << "There is no such word." << std::endl;
    }

    std::sort(results.begin(), results.end());

    for (auto& result : results) {
        std::cout << result << std::endl;
    }
}

int main() {
    int n;
    while (std::cin >> n) {
        solve(n);
    }
}
