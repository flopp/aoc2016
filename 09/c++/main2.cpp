#include <iostream>
#include <regex>
#include <string>

std::size_t expand(std::string::const_iterator c, std::size_t len) {
    static const std::regex re{"\\((\\d+)x(\\d+)\\)"};
    std::smatch m;
    std::size_t n = 0;
    auto cend0 = c + len;
    auto cend1 = c + (len - 1);
    while (c != cend0) {
        if (*c == '(') {
            std::regex_search(c, cend1, m, re);
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
    return count;
}

int main() {
    std::string line; std::getline(std::cin, line);
    std::cout << "Count: " << expand(line.cbegin(), line.size()) << std::endl;
    return 0;
}
