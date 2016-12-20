#include <iostream>
#include <list>
#include <regex>
#include <string>

typedef long long T;
struct Range {
    T min, max;
};

void print(const std::list<Range>& b) {
    for (const auto& r: b) {
        std::cout << "(" << r.min << " " << r.max << ") ";
    }
    std::cout << std::endl;
}

int main(int /*argc*/, char** argv) {
    const std::regex re("(\\d+)-(\\d+)");
    std::smatch m;

    std::list<Range> blacklist;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::regex_match(line, m, re);
        const Range r{std::stoll(m[1]), std::stoll(m[2])};
        if (blacklist.empty()) {
            blacklist.push_back(r);
            continue;
        }

        auto it = blacklist.begin();
        while (it != blacklist.end() && it->max + 1 < r.min) {
            ++it;
        }
        if (it == blacklist.end()) {
            blacklist.push_back(r);
            continue;
        } else if (r.max + 1 < it->min) {
            blacklist.insert(it, r);
            continue;
        }

        it->min = std::min(it->min, r.min);
        it->max = std::max(it->max, r.max);
        auto it2 = it;
        ++it2;
        while (it2 != blacklist.end()) {
            if (it2->min <= it->max + 1) {
                it->max = std::max(it->max, it2->max);
                it2 = blacklist.erase(it2);
            } else {
                break;
            }
        }
    }

    std::cout
        << "first allowed: "
        << ((blacklist.front().min > 0) ? (blacklist.front().min - 1) : (blacklist.front().max + 1))
        << std::endl;

    T count = std::stoll(argv[1]) + 1;
    for (const auto& r: blacklist) {
        count -= (1 + r.max - r.min);
    }
    std::cout << "#allowed: " << count << std::endl;

    return 0;
}
