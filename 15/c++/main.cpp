#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

struct Disc {
    int index;
    int positions;
    int start;
};

void parse(std::istream& is, std::vector<Disc>& discs) {
    discs.clear();
    
    const std::regex re("Disc #(\\d+) has (\\d+) positions; at time=0, it is at position (\\d+).");
    std::smatch m;
    
    std::string line;
    while (std::getline(is, line)) {
        std::regex_match(line, m, re);
        discs.push_back({std::stoi(m[1]), std::stoi(m[2]), std::stoi(m[3])});
    }
}

void normalize(std::vector<Disc>& discs) {
    for (auto& d: discs) {
        d.start += d.index;
        d.start %= d.positions;
    }
}

void sort(std::vector<Disc>& discs) {
    std::sort(
        discs.begin(), discs.end(), 
        [](const Disc& a, const Disc& b) -> bool { 
            return (a.positions > b.positions) || (a.positions == b.positions && a.index < b.index); 
        });
}

int main() {
    std::vector<Disc> discs;
    parse(std::cin, discs);
    normalize(discs);
    sort(discs);
    
    for (int time = 0; /**/; ++time) {
        bool ok = true;
        for (const auto& d: discs) {
            if ((d.start + time) % d.positions) {
                ok = false;
                break;
            }
        }
        if (ok) {
            std::cout << time << std::endl;
            return 0;
        }
    }
    
    return 0;
}
