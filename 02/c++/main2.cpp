#include <iostream>
#include <string>

static const std::string keys{"--1---234-56789-ABC---D--"};
struct Pos {
    int x{0}, y{2};
    void step(char d) { 
        switch (d) {
            case 'U': y = bad(x,y-1) ? y : (y-1); return;
            case 'D': y = bad(x,y+1) ? y : (y+1); return;
            case 'L': x = bad(x-1,y) ? x : (x-1); return;
            case 'R': x = bad(x+1,y) ? x : (x+1); return;
        }
    }
    bool bad(int x, int y) { return (x<0 || x>4 || y<0 || y>4 || keys[x+y*5]=='-'); }
};
std::ostream& operator<<(std::ostream& os, const Pos& p) {
    os << keys[p.x+p.y*5];
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
