#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

struct cn { 
    char c; int n; 
    bool operator<(const cn& o) const { return (n > o.n) || (n == o.n && c < o.c); }
};

void rotate(std::string& s, int d) {
    for (auto& c: s) {
        if (c != ' ') { c = char('a' + ((int(c - 'a') + d) % 26)); }
    }
}

void decode(const std::string& s) {
    std::vector<cn> chars;
    for (char c = 'a'; c <= 'z'; ++c) { chars.push_back({c, 0}); }
    
    int id = 0;
    int chk = -1;
    std::string name;
    
    for (auto c: s) {
        if (chk >= 0) {
            if (std::isalpha(c)) { 
                if (chars[chk].c != c) { return; }
                ++chk;
            }
        } 
        else if (std::isalpha(c)) { chars[c - 'a'].n++; name += c; } 
        else if (c == '-') { name += ' '; } 
        else if (std::isdigit(c)) { id = 10 * id + (c - '0'); } 
        else if (c == '[') { chk = 0; std::sort(chars.begin(), chars.end()); }
    }
    
    rotate(name, id);
    if (name.find("north") != std::string::npos) {
        std::cout << name << id << std::endl;
    }
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) { decode(line); }
    return 0;
}
