#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct cn { 
    char c; int n; 
    bool operator<(const cn& o) const { return (n > o.n) || (n == o.n && c < o.c); }
};

int decode(const std::string& s) {
    std::vector<cn> chars;
    for (char c = 'a'; c <= 'z'; ++c) { chars.push_back({c, 0}); }
    
    int id = 0;
    int chk = -1;
    for (auto c: s) {
        if (chk >= 0) {
            if (std::isalpha(c)) { 
                if (chars[chk].c != c) { return 0; }
                ++chk;
            }
        } 
        else if (std::isalpha(c)) { chars[c - 'a'].n++; }
        else if (std::isdigit(c)) { id = 10 * id + (c - '0'); }
        else if (c == '[') { chk = 0; std::sort(chars.begin(), chars.end()); }
    }
    return id;
}

int main() {
    int result = 0;
    std::string line;
    while (std::getline(std::cin, line)) { result += decode(line); }
    std::cout << result << std::endl;
    return 0;
}
