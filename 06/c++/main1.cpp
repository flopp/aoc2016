#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> c;
    int w = 0;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (c.empty()) { w = line.size(); c.assign(26 * w, 0); }
        
        for (int i = 0; i < w; ++i) {
            c[26 * i + (line[i] - 'a')]++;
        }
    }

    line.resize(w);
    for (int i = 0; i < w; ++i) {
        int max_c = -1;
        for (int j = 0; j < 26; ++j) {
            if (c[26 * i + j] > max_c) {
                max_c = c[26 * i + j];
                line[i] = 'a' + j;
            }
        }
    }
    std::cout << line << std::endl;
    
    return 0;
}
