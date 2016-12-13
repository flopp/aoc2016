#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef std::pair<unsigned int, unsigned int> P;

bool is_space(const P& p, unsigned int f) {
    unsigned int v = p.first*p.first + 3*p.first + 2*p.first*p.second + p.second + p.second*p.second + f;
    bool space = true;
    
    while (v) {
        space = !space;
        v = v & (v - 1);
    }
    
    return space;
}


int main() {
    unsigned int favorite_number;
    unsigned int tx, ty;
    std::cin >> favorite_number >> tx >> ty;
        
    std::map<P, unsigned int> dist;
    std::deque<P> open_list;
    
    dist[{1, 1}] = 0;
    open_list.push_back({1, 1});
    
    while (!dist.empty()) {
        const auto p = open_list.front();
        open_list.pop_front();
        const auto d = dist[p];
        
        if (p.first == tx && p.second == ty) {
            std::cout << d << std::endl;
            break;
        }
        
        if (p.first > 0) {
            const P n{p.first-1, p.second};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        if (p.second > 0) {
            const P n{p.first, p.second-1};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        {
            const P n{p.first+1, p.second};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
        {
            const P n{p.first, p.second+1};
            if (is_space(n, favorite_number) && dist.find(n) == dist.end()) {
                dist[n] = d + 1;
                open_list.push_back(n);
            }
        }
    }
    
    return 0;
}
