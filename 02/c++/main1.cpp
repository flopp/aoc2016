#include <iostream>
#include <string>

struct Pos {
    int x{1}, y{1};
    void step(char d) { 
        switch (d) {
            case 'U': y = (y > 0) ? (y - 1) : y; return;
            case 'D': y = (y < 2) ? (y + 1) : y; return;
            case 'L': x = (x > 0) ? (x - 1) : x; return;
            case 'R': x = (x < 2) ? (x + 1) : x; return;
        }
    }
};

int main() {
    Pos p;
    std::string s;
    while (std::getline(std::cin, s)) {
        for (char c: s) { p.step(c); }
        std::cout << (1 + p.x + (p.y * 3));
    }
    std::cout << std::endl;
    return 0;
}
