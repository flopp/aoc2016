#include <iostream>
#include <regex>
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
    void forward(const Dir& d, int len) { x += len * d.dx; y += len * d.dy; }
};

int main() {
    Dir d;
    Pos p;        
    std::string line; std::getline(std::cin, line);
    const std::regex re("([RL])(\\d+)");
    for (std::sregex_iterator m{line.begin(), line.end(), re}; m != std::sregex_iterator(); ++m) {
        d.rotate(((*m)[1] == "L") ? -1 : +1);
        p.forward(d, std::stoi((*m)[2]));
    }
    std::cout << (std::abs(p.x) + std::abs(p.y)) << std::endl;
    return 0;
}
