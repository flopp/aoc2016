#include <iostream>
#include <regex>
#include <set>
#include <string>

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

int main() {
    Dir d;
    Pos p;
    std::set<Pos> visited{p};
    std::string line; std::getline(std::cin, line);
    const std::regex re("([RL])(\\d+)");
    for (std::sregex_iterator m{line.begin(), line.end(), re}; m != std::sregex_iterator(); ++m) {
        d.rotate(((*m)[1] == "L") ? -1 : +1);
        for (int i = std::stoi((*m)[2]); i > 0; --i) {
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
