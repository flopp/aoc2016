#include <iostream>
#include <string>

static const std::string keys{"--1---234-56789-ABC---D--"};

struct Pos {
    int x{0}, y{2};
    void step(char d) { 
        switch (d) {
            case 'U': y = ok(x,y-1) ? (y-1) : y; return;
            case 'D': y = ok(x,y+1) ? (y+1) : y; return;
            case 'L': x = ok(x-1,y) ? (x-1) : x; return;
            case 'R': x = ok(x+1,y) ? (x+1) : x; return;
        }
    }
    bool ok(int x, int y) const { return (x>=0 && x<=4 && y>=0 && y<=4 && keys[x+y*5]!='-'); }
};

int main() {
    Pos p;
    std::string s;
    while (std::getline(std::cin, s)) {
        for (char c: s) { p.step(c); }
        std::cout << keys[p.x+p.y*5];
    }
    std::cout << std::endl;
    return 0;
}
