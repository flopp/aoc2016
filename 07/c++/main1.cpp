#include <iostream>
#include <string>

int main() {
    int count = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        bool hyper = false;
        bool abba = false;
        for (const char* p = line.c_str(); p[3] != '\0'; ++p) {
            if (*p == '[')      { hyper = true; }
            else if (*p == ']') { hyper = false; }
            else if (p[0] == p[3] && p[0] != p[1] && p[1] == p[2]) {
                if (hyper)      { abba = false; break; }
                else            { abba = true; }
            }
        }
        count += abba;
    }
    std::cout << count << std::endl;
    
    return 0;
}
