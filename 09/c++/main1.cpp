#include <iostream>
#include <regex>
#include <string>

int main() {
    const std::regex re{"\\((\\d+)x(\\d+)\\)"};
    std::smatch m;
    std::string s; std::getline(std::cin, s);
    std::size_t n = 0;
    auto cend = s.cbegin() + (s.size() - 1);
    for (auto c = s.cbegin(); c != s.cend(); /**/) {
        if (*c == '(') {
            std::regex_search(c, cend, m, re);
            c += m.length();
            auto datalength  = static_cast<std::size_t>(std::stoi(m[1]));
            auto repetitions = static_cast<std::size_t>(std::stoi(m[2]));
            n += repetitions * datalength;
            c += datalength;
        } else {
            ++n;
            ++c;
        }
    }
     
    std::cout << "Count: " << n << std::endl;
    return 0;
}
