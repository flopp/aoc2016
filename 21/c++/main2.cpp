#include <cassert>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


struct Op {
    enum T {SWAP_POS, SWAP_LETTER, REVERSE, ROTATE, ROTATE_LETTER, MOVE};
    T t;
    int p1;
    int p2;
};

std::vector<Op> parseOps(std::istream& is) {
    std::vector<Op> ops;

    static const std::regex re_swap_position("swap position (\\d+) with position (\\d+)");
    static const std::regex re_swap_letter("swap letter (.) with letter (.)");
    static const std::regex re_reverse("reverse positions (\\d+) through (\\d+)");
    static const std::regex re_rotate_left("rotate left (\\d+) steps?");
    static const std::regex re_rotate_right("rotate right (\\d+) steps?");
    static const std::regex re_move("move position (\\d+) to position (\\d+)");
    static const std::regex re_rotate_letter("rotate based on position of letter (.)");
    std::smatch m;

    std::string line;
    while (std::getline(is, line)) {
        if (std::regex_match(line, m, re_swap_position)) {
            ops.push_back({Op::SWAP_POS, std::stoi(m[1]), std::stoi(m[2])});
        } else if (std::regex_match(line, m, re_swap_letter)) {
            ops.push_back({Op::SWAP_LETTER, m.str(1)[0], m.str(2)[0]});
        } else if (std::regex_match(line, m, re_reverse)) {
            ops.push_back({Op::REVERSE, std::stoi(m[1]), std::stoi(m[2])});
        } else if (std::regex_match(line, m, re_rotate_left)) {
            ops.push_back({Op::ROTATE, -std::stoi(m[1]), 0});
        } else if (std::regex_match(line, m, re_rotate_right)) {
            ops.push_back({Op::ROTATE, std::stoi(m[1]), 0});
        } else if (std::regex_match(line, m, re_rotate_letter)) {
            ops.push_back({Op::ROTATE_LETTER, m.str(1)[0], 0});
        } else if (std::regex_match(line, m, re_move)) {
            ops.push_back({Op::MOVE, std::stoi(m[1]), std::stoi(m[2])});
        } else {
            std::cout << "bad rule: " << line << std::endl;
            break;
        }
    }
    return ops;
}

void rotate(std::string& s, int amount) {
    std::string r = s;
    for (int i = 0; i < s.size(); ++i) {
        r[(i+amount+s.size()) % s.size()] = s[i];
    }
    std::swap(s, r);
}

std::string scramble(std::string password, const std::vector<Op>& ops) {
    for (const auto& op: ops) {
        switch (op.t) {
            case Op::SWAP_POS:
                std::swap(password[op.p1], password[op.p2]);
                break;
            case Op::SWAP_LETTER:
                std::swap(password[password.find(op.p1)], password[password.find(op.p2)]);
                break;
            case Op::REVERSE:
                std::reverse(password.begin() + op.p1, password.begin() + op.p2 + 1);
                break;
            case Op::ROTATE:
                rotate(password, op.p1);
                break;
            case Op::ROTATE_LETTER:
                {
                    auto pos = password.find(op.p1);
                    assert(pos != std::string::npos);
                    rotate(password, pos + 1 + ((pos >= 4) ? 1 : 0));
                }
                break;
            case Op::MOVE:
                {
                    char c = password[op.p1];
                    password.erase(password.begin() + op.p1);
                    password.insert(password.begin() + op.p2, c);
                }
                break;
        }
    }
    return password;
}

int main(int /*argc*/, char** argv) {
    const auto ops = parseOps(std::cin);

    std::string password{argv[1]};
    const std::string& scrambled{argv[2]};

    do {
        if (scramble(password, ops) == scrambled) {
            std::cout << password << std::endl;
            break;
        }
    } while (std::next_permutation(password.begin(), password.end()));
    
    return 0;
}
