#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

typedef uint64_t T;
T state_size;

void _set_f(T& s, T i, T f) { 
    s &= ~(3ull << (2*i));
    s |= f << (2*i);
}
void set_elevator(T& s, T f)        { _set_f(s, 0, f); }
void set_memory(T& s, T el, T f)    { _set_f(s, 1 + 2 * el, f); }
void set_generator(T& s, T el, T f) { _set_f(s, 2 + 2 * el, f); }
    
bool is_target_state(const T& s) {
    auto p = s;
    p >>= 2ull;
    for (auto i = 0ull; i < state_size; ++i) {
        if ((p & 15) != 15) { return false; }
        p >>= 4ull;
    }
    return true;
}

bool is_valid_state(const T& s) {
    T m = 0u;
    T g = 0u;
    auto p = s;
    p >>= 2ull;
    for (auto i = 0u; i < state_size; ++i) {
        m |= ((p & 3) != ((p >> 2) & 3)) << (p & 3);
        p >>= 2ul;
        g |= 1u << (p & 3);
        p >>= 2ul;
    }
    return (m & g) == 0;
}

void get_movable_elements(const T& s, std::vector<T>& elements) {
    auto p = s;
    auto floor = p & 3;
    p >>= 2ul;
    for (auto i = 0u; i < 2 * state_size; ++i) {
        if ((p & 3) == floor) { elements.push_back(i); }
        p >>= 2ul;
    }
}

void compute_next_states(const T& s, std::vector<bool>& visited, std::vector<T>& states) {
    static std::vector<T> elements;
    elements.clear();
    get_movable_elements(s, elements);
        
    auto elevator = s & 3;
    if (elevator > 0) {
        for (auto i = 0u; i < elements.size(); ++i) {
            for (auto j = i; j < elements.size(); ++j) {
                T next = s;
                set_elevator(next, elevator-1);
                _set_f(next, 1 + elements[i], elevator-1);
                if (i != j) _set_f(next, 1 + elements[j], elevator-1);
                if (is_valid_state(next) && !visited[next]) {
                    visited[next] = true;
                    states.push_back(next);
                }
            }
        }
    }
    if (elevator < 3) {
        for (auto i = 0u; i < elements.size(); ++i) {
            for (auto j = i; j < elements.size(); ++j) {
                T next = s;
                set_elevator(next, elevator+1);
                _set_f(next, 1 + elements[i], elevator+1);
                if (i != j) _set_f(next, 1 + elements[j], elevator+1);
                if (is_valid_state(next) && !visited[next]) {
                    visited[next] = true;
                    states.push_back(next);
                }
            }
        }
    }
}

int main() {
    state_size = 0;
    T init = 0;
    
    std::regex re("a (\\w+)( generator|-compatible)");
    std::smatch m;
    
    std::map<std::string, T> elements;
    for (int floor = 0; floor < 4; ++floor) {
        std::string line;
        std::getline(std::cin, line);
        
        while (regex_search(line, m, re)) {
            if (elements.find(m[1]) == elements.end()) {
                elements[m[1]] = state_size;
                ++state_size;
            }
            if (m[2] == "-compatible") {
                set_memory(init, elements[m[1]], floor);
            } else {
                set_generator(init, elements[m[1]], floor);
            }
            line = m.suffix();
        }
    }
    
    assert(state_size < 15);
    std::vector<bool> visited(1u << (4*state_size+2), false);
    visited[init] = true;
    
    std::vector<T> open, next;
    open.push_back(init);
    
    int steps = 0;
    while (true) {        
        next.clear();
        for (const auto& s: open) {
            if (is_target_state(s)) {
                std::cout << "target reached after " << steps << " steps" << std::endl;
                return 0;
            }
            compute_next_states(s, visited, next);
        }
        
        if (next.empty()) {
            break;
        } else {
            std::swap(open, next);
            ++steps;
        }
    }
    
    return 0;
}
