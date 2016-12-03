#include <iostream>

int main() {
    int a, b, c, count = 0;
    for (;;) {
        if (!(std::cin >> a >> b >> c)) break;
        count += ((a < b+c) && (b < a+c) && (c < a+b));
    }
    std::cout << count << std::endl;
    return 0;
}
