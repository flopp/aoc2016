#include <iostream>
#include <string>

struct Pos {
    int x{1}, y{1};
    void step(char d) { 
        switch (d) {
            case 'U': y = (y == 0) ? y : (y - 1); return;
            case 'D': y = (y == 2) ? y : (y + 1); return;
            case 'L': x = (x == 0) ? x : (x - 1); return;
            case 'R': x = (x == 2) ? x : (x + 1); return;
        }
    }
};
std::ostream& operator<<(std::ostream& os, const Pos& p) {
    os << (1 + p.x + (p.y * 3));
    return os;
}

int main() {
    Pos p;
    std::string s;
    while (std::getline(std::cin, s)) {
        for (char c: s) { p.step(c); }
        std::cout << p;
    }
    std::cout << std::endl;
    return 0;
}
