#include <iostream>
#include <string>

int main(int /*argc*/, char** argv) {
    std::string s1, s2; 
    std::getline(std::cin, s1);
    const int rows = std::stoi(argv[1]);
    const int cols = static_cast<int>(s1.size());
    
    int safe = 0;
    for (const auto& c: s1) { safe += (c == '.'); }
    
    for (int row = 1; row < rows; ++row) {
        s2 = (s1[1] == '^') ? '^' : '.';
        for (int i = 1; i < cols-1; ++i) {
            s2 += (s1[i-1] != s1[i+1]) ? '^' : '.';
        }
        s2 += (s1[cols-2] == '^') ? '^' : '.';
        
        for (const auto& c: s2) { safe += (c == '.'); }
        std::swap(s1, s2);
    }
    std::cout << safe << std::endl;
    
    return 0;
}
