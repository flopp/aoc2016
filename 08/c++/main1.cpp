#include <iostream>
#include <regex>
#include <string>
#include <vector>

struct Grid {
    Grid(int w, int h) : g{h, std::string(w, '.')} {}
    
    void rect(int w, int h) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                g[y][x] = '#';
            }
        }
    }
    
    void rrow(int y, int dx) {
        for (int i = 0; i < dx; ++i) {
            g[y] = g[y].back() + g[y].substr(0, g[y].size() - 1);
        }
    }
    
    void rcol(int x, int dy) {
        for (int i = 0; i < dy; ++i) {
            const char c = g.back()[x];
            for (int y = g.size() - 1; y >= 1; --y) {
                g[y][x] = g[y-1][x];
            }
            g[0][x] = c;
        }
    }
    
    std::vector<std::string> g;
};

std::ostream& operator<<(std::ostream& os, const Grid& g) {
    int n = 0;
    for (const auto& row: g.g) {
        for (const auto& c: row) {
            n += (c == '#');
            os << c;
        }
        os << '\n';
    }
    os << "count: " << n;
    return os;
}


int main(int /*argc*/, char** argv) {
    Grid g(std::stoi(argv[1]), std::stoi(argv[2]));
    
    const std::vector<std::pair<std::regex, void (Grid::*)(int, int)>> re_fs{
        {std::regex{"rect (\\d+)x(\\d+)"},               &Grid::rect},
        {std::regex{"rotate row y=(\\d+) by (\\d+)"},    &Grid::rrow},
        {std::regex{"rotate column x=(\\d+) by (\\d+)"}, &Grid::rcol}};
    
    std::string line;
    while (std::getline(std::cin, line)) {
        for (auto re_f: re_fs) {
            std::smatch m;
            if (std::regex_match(line, m, re_f.first)) {
                (g.*(re_f.second))(std::stoi(m[1]), std::stoi(m[2]));
                break;
            }
        }
    }
    std::cout << g << std::endl;
    
    return 0;
}
