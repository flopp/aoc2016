#include <deque>
#include <iostream>
#include <string>
#include "md5.h"

struct State {
    State() = default;
    State(int xx, int yy, const std::string& pp) : x{xx}, y{yy}, path{pp} {}

    int x{0}, y{0};
    std::string path;

    bool isTarget() const { return x == 3 && y == 3; }
    void pushNext(const std::string& passcode, std::deque<State>& states) const {
        static MD5 md5;
        char* hash = md5.digestString(const_cast<char*>((passcode + path).c_str()));

        if (hash[0] >= 'b' && y > 0) {
            states.push_back(State(x, y - 1, path + 'U'));
        }
        if (hash[1] >= 'b' && y < 3) {
            states.push_back(State(x, y + 1, path + 'D'));
        }
        if (hash[2] >= 'b' && x > 0) {
            states.push_back(State(x - 1, y, path + 'L'));
        }
        if (hash[3] >= 'b' && x < 3) {
            states.push_back(State(x + 1, y, path + 'R'));
        }
    }
};

int main(int /*argc*/, char** argv) {
    const std::string passcode = argv[1];

    std::deque<State> states;
    states.push_back(State());
    std::size_t maxLength = 0;

    while (!states.empty()) {
        const State s = states.front(); states.pop_front();
        if (s.isTarget()) {
            if (s.path.size() > maxLength) {
                maxLength = s.path.size();
            }
        } else {
            s.pushNext(passcode, states);
        }
    }

    std::cout << maxLength << std::endl;
    return 0;
}
