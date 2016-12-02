#include <iostream>
#include <set>
#include <string>
#include <vector>
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
    void forward(const Dir& d) { x += d.dx; y += d.dy; }
    bool operator<(const Pos& o) const {
        return (x < o.x) || ((x == o.x) && (y < o.y));
    }
};

struct Step {
    int turn;
    int len;
    explicit Step(const std::string& s) {
        turn = (s[0] == 'L') ? -1 : +1;
        len = std::stoi(s.substr(1));
    }
};


int main() {
    Dir d;
    Pos p;
    std::set<Pos> visited{p};
    std::string line; std::getline(std::cin, line);
    for (auto s: split(line, ',')) {
        Step step{trim(s)};
        d.rotate(step.turn);
        for (int i = 0; i < step.len; ++i) {
            p.forward(d);
            if (visited.find(p) != visited.end()) {
                std::cout << (std::abs(p.x) + std::abs(p.y)) << std::endl;             
                return 0;
            }
            visited.insert(p);
        }
    }
    
    return 0;
}
