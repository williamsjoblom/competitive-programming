#include <cstdio>
#include <iostream>

int main() {
    int k;
    while (std::cin >> k) {
        while (k) {
            // 7 valid numbers.
            switch (k % 7) {
            case 0: putchar('0'); break;
            case 1: putchar('1'); break;
            case 2: putchar('2'); break;
            case 3: putchar('5'); break;
            case 4: putchar('9'); break;
            case 5: putchar('8'); break;
            case 6: putchar('6'); break;
            }

            k /= 7;
        }
        putchar('\n');
    }
}
