#include <iostream>

int main() {
    int a, b, c, count = 0;
    for (;;) {
        if (!(std::cin >> a >> b >> c)) break;
        if ((a < b+c) && (b < a+c) && (c < a+b)) ++count;
    }
    std::cout << count << std::endl;
    return 0;
}
