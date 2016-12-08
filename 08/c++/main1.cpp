#include <iostream>
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
    
    void rot_row(int y, int dx) {
        for (int i = 0; i < dx; ++i) {
            g[y] = g[y].back() + g[y].substr(0, g[y].size() - 1);
        }
    }
    
    void rot_col(int x, int dy) {
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
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.find("rect") == 0) {
            line = line.substr(5);
            auto p = line.find("x");
            g.rect(std::stoi(line.substr(0, p)), std::stoi(line.substr(p + 1)));
        } else if (line.find("rotate row") == 0) {
            line = line.substr(13);
            auto p = line.find(" by ");
            g.rot_row(std::stoi(line.substr(0, p)), std::stoi(line.substr(p + 4)));
        } else if (line.find("rotate column") == 0) {
            line = line.substr(16);
            auto p = line.find(" by ");
            g.rot_col(std::stoi(line.substr(0, p)), std::stoi(line.substr(p + 4)));
        }
    }    
    std::cout << g << std::endl;
    
    return 0;
}
