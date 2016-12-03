#include <iostream>

bool tria(int a, int b, int c) { return (a < b+c) && (b < a+c) && (c < a+b); }

int main() {
    int a0, b0, c0,   a1, b1, c1,   a2, b2, c2,   count = 0;
    for (;;) {
        if (!(std::cin >> a0 >> a1 >> a2 >> b0 >> b1 >> b2 >> c0 >> c1 >> c2)) break;
        count += tria(a0, b0, c0) + tria(a1, b1, c1) + tria(a2, b2, c2);
    }
    std::cout << count << std::endl;
    return 0;
}
