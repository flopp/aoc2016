#include <deque>
#include <iostream>
#include <map>
#include <string>

struct P {
    unsigned int x, y;
    
    bool operator<(const P& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};


bool is_space(const P& p, unsigned int f) {
    unsigned int v = p.x*p.x + 3*p.x + 2*p.x*p.y + p.y + p.y*p.y + f;
    bool space = true;
    
    // determine parity of v
    while (v) {
        space = !space;
        v = v & (v - 1);
    }
    
    return space;
}


int main() {
    unsigned int favorite_number;
    std::cin >> favorite_number;
        
    std::map<P, unsigned int> dist;
    std::deque<P> open_list;
    
    dist[{1, 1}] = 0;
    open_list.push_back({1, 1});
    
    while (!dist.empty()) {
        const auto p = open_list.front();
        open_list.pop_front();
        const auto d = dist[p];
        
        if (d >= 50) {
            break;
        }
        
        if (p.x > 0) {
            const P n{p.x-1, p.y};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        if (p.y > 0) {
            const P n{p.x, p.y-1};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        {
            const P n{p.x+1, p.y};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        {
            const P n{p.x, p.y+1};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
    }
    
    std::cout << dist.size() << std::endl;
    
    return 0;
}
