#include <iostream>
#include <string>
#include <map>
#include <vector>

int main() {
    std::vector<std::vector<int>> counts;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (counts.empty()) {
            counts.assign(line.size(), std::vector<int>(26, 0));
        }
        for (auto i = 0u; i < line.size(); ++i) {
            counts[i][line[i] - 'a']++;
        }
    }
    
    for (const auto& v: counts) {
        int count = -1;
        char c = '?';
        for (auto i = 0u; i < v.size(); ++i) {
            if (v[i] > 0 && (count < 0 || v[i] < count)) {
                count = v[i];
                c = 'a' + i;
            }
        }
        std::cout << c;
    }
    std::cout << std::endl;
    
    return 0;
}
