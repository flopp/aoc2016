#include <iostream>
#include <regex>
#include <string>

int main() {
    const std::regex re{"\\((\\d+)x(\\d+)\\)"};
    std::smatch m;
    
    std::string line; std::getline(std::cin, line);
    int count = 0;
    auto cend = line.cbegin() + (line.size() - 1);
    for (auto c = line.cbegin(); c != line.cend(); /**/) {
        if (*c == '(') {
            std::regex_search(c, cend, m, re);
            c += m.length();
            c += std::stoi(m[1]);
            count += std::stoi(m[1]) * std::stoi(m[2]);
        } else {
            ++c;
            ++count;
        }
    }
     
    std::cout << "Count: " << count << std::endl;
    return 0;
}
