#include <iostream>
#include <regex>
#include <string>

std::size_t expand(std::string::const_iterator c, std::size_t len) {
    static const std::regex re{"\\((\\d+)x(\\d+)\\)"};
    std::smatch m;
    std::size_t n = 0;
    auto cend = c + len;
    while (c != cend) {
        if (*c == '(') {
            std::regex_search(c, cend, m, re);
            c += m.length();
            auto datalength  = static_cast<std::size_t>(std::stoi(m[1]));
            auto repetitions = static_cast<std::size_t>(std::stoi(m[2]));
            n += repetitions * expand(c, datalength);
            c += datalength;
        } else {
            ++n;
            ++c;
        }
    }
    return n;
}

int main() {
    std::string line; std::getline(std::cin, line);
    std::cout << "Count: " << expand(line.cbegin(), line.size()) << std::endl;
    return 0;
}
