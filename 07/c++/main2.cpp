#include <iostream>
#include <string>
#include <set>

int main() {
    int count = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::set<std::pair<char, char>> aba, bab;
        bool hyper = false;
        for (const char* p = line.c_str(); p[2] != '\0'; ++p) {
            if (*p == '[')      { hyper = true; }
            else if (*p == ']') { hyper = false; }
            else if (p[0] == p[2] && p[0] != p[1]) {
                if (hyper)      { bab.insert({p[1], p[0]}); }
                else            { aba.insert({p[0], p[1]}); }
            }
        }
        for (auto ab: aba) { 
            if (bab.find(ab) != bab.end()) { 
                ++count; break; 
            } 
        }
    }
    std::cout << count << std::endl;
    
    return 0;
}
