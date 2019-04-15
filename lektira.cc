// William Sjöblom
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string origin; std::cin >> origin;

    std::string best = "~";
    
    for (int i = 1; i < origin.size(); i++) {
        for (int j = 1; j < i; j++) {
            std::string transf = origin;

            std::reverse(transf.begin(), transf.begin() + j);
            std::reverse(transf.begin() + j, transf.begin() + i);
            std::reverse(transf.begin() + i, transf.end());

            if (transf < best) best = transf;
        }
    }

    std::cout << best << std::endl;
}
