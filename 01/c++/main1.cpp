#include <iostream>
#include <string>
#include "utils.h"

struct Dir {
    int dx{0}, dy{1};
    void rotate(int turn) {
        std::swap(dx, dy);
        if (turn < 0) {dx *= -1;} else {dy *= -1;}
    }
};

struct Pos {
    int x{0}, y{0};
    void forward(const Dir& d, int len) { x += len * d.dx; y += len * d.dy; }
};

struct Step {
    int turn, len;
    explicit Step(const std::string& s) {
        turn = (s[0] == 'L') ? -1 : +1;
        len = std::stoi(s.substr(1));
    }
};

int main() {
    Dir d;
    Pos p;        
    std::string line; std::getline(std::cin, line);
    for (auto s: split(line, ',')) {
        Step step{trim(s)};
        d.rotate(step.turn);
        p.forward(d, step.len);
    }
    std::cout << (std::abs(p.x) + std::abs(p.y)) << std::endl;
    return 0;
}
