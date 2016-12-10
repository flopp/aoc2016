#include <cassert>
#include <iostream>
#include <regex>
#include <stack>
#include <string>

static const int empty = 1000000;

struct Bot {
    Bot(int i): index{i} {}
        
    void setHiLo(int h, int l) {
        hi = h;
        lo = l;
    }
    
    void clear() { 
        v0 = empty; 
        v1 = empty; 
    }
    
    bool take(int v) {
        if (v0 == empty) { 
            v0 = v;
        } else if (v1 == empty) { 
            v1 = v;  
            if (v0 > v1) { std::swap(v0, v1); } 
        }
        return (v1 != empty);
    }
    
    int index{empty}, 
        lo{empty}, hi{empty}, 
        v0{empty}, v1{empty};
};

std::ostream& operator<<(std::ostream& os, const Bot& b) {
    std::cout << "bot " << b.index << "   " << b.lo << " " << b.hi << "   " << b.v0 << " " << b.v1;
    return os;
}

Bot& getBot(std::vector<Bot>& bots, int index) {
    while (static_cast<int>(bots.size()) <= index) { 
        bots.push_back(Bot{static_cast<int>(bots.size())}); 
    }
    return bots[index];
}
int& getOut(std::vector<int>& outs, int index) {
    while (static_cast<int>(outs.size()) <= index) { 
        outs.push_back(empty); 
    }
    return outs[index];
}

int main(int argv, char** argc) {
    int t0 = std::stoi(argc[1]);
    int t1 = std::stoi(argc[2]);
    if (t0 > t1) std::swap(t0, t1);
        
    std::vector<int> outs;
    std::vector<Bot> bots;
    std::stack<int> full;
    
    static const std::regex re1{"bot (\\d+) gives low to (.+) (\\d+) and high to (.+) (\\d+)"};
    static const std::regex re2{"value (\\d+) goes to bot (\\d+)"};
    std::smatch m;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (std::regex_search(line, m, re1)) {
            int b = std::stoi(m[1]);
            int b_lo = std::stoi(m[3]);
            int b_hi = std::stoi(m[5]);
            if (m[2] == "bot") {
                getBot(bots, b_lo);
            } else {
                getOut(outs, b_lo);
                b_lo = -b_lo - 1;
            }
            if (m[4] == "bot") {
                getBot(bots, b_hi);
            } else {
                getOut(outs, b_hi);
                b_hi = -b_hi - 1;
            }
            getBot(bots, b).setHiLo(b_lo, b_hi);
        } else if (std::regex_search(line, m, re2)) {
            int v = std::stoi(m[1]);
            int b = std::stoi(m[2]);
            if (getBot(bots, b).take(v)) { full.push(b); }
        }
    }
    
    while (!full.empty()) {
        int b = full.top();
        full.pop();
        auto& bot = bots[b];
        if (bot.v0 == t0 && bot.v1 == t1) {
            std::cout << bot << std::endl;
        }
        assert(bot.lo != empty || bot.hi != empty);
        if (bot.lo >= 0) {
            if (bots[bot.lo].take(bot.v0)) { full.push(bot.lo); }
        } else {
            outs[-bot.lo - 1] = bot.v0;
        }
        if (bot.hi >= 0) {
            if (bots[bot.hi].take(bot.v1)) { full.push(bot.hi); }
        } else {
            outs[-bot.hi - 1] = bot.v1;
        }
        bot.clear();
    }
    
    for (auto i = 0u; i < outs.size(); ++i) {
        std::cout << "output " << i << " = " << outs[i] << std::endl;
    }
    
    return 0;
}
